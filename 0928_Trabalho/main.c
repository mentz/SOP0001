//#define DEBUG_SET

#include "tbanc.h"
#include "utils.h"

#ifdef DEBUG_SET
#define printd printf
#else
#define printd 
#endif

sem_t *sem_transacao;			// Controla acesso ao consumo de transações - só quando há transações.
pthread_mutex_t mut_transacao;	// Controla acesso à lista de transações para evitar condições de disputa.
int acabou;						// Informa fim de novas transações.
long num_processos;				// Conta transações efetuadas.
long num_fracassos;				// Conta transações fracassadas.

pConta contas = NULL;
pTransacao transacoes = NULL;

// Função das threads.
void* run_transaction(void *args) {
	long thread_num = (long) args;
	Transacao t_aux;
	pConta c_origem, c_destino;
	while (1)
	{
		// INICIO Área crítica - consumo de transação.
		{
			printd("[%ld] -  0 wait sem_transacao\n", thread_num);
			sem_wait(sem_transacao);
			printd("[%ld] -  1 got sem_transacao, check se acabou\n", thread_num);
			
			printd("[%ld] -  2 wait mut_transacao\n", thread_num);
			pthread_mutex_lock(&mut_transacao);
			printd("[%ld] -  3 got mut_transacao\n", thread_num);
			
			// Para se não tiver mais entradas
			if (acabou && transacoes == NULL)
			{
				printd("[%ld] -  4b Acabou entrada\n", thread_num);
				pthread_mutex_unlock(&mut_transacao); // Para outras threads poderem entrar neste if.
				sem_post(sem_transacao); // Sinalizar para outros threads que possam estar esperando.
				break;
			}
			
			num_processos++;

			// Consome transação.
			printd("[%ld] -  4a enter consome_transacao\n", thread_num);
			t_aux = consome_transacao(&transacoes);
			printd("[%ld] -  5 got transacao\n", thread_num);

			pthread_mutex_unlock(&mut_transacao);
			printd("[%ld] -  6 gave mut_transacao\n", thread_num);
		}
		// FIM Área crítica - consumo de transação.

		// Busca a conta de origem.
		c_origem = busca_conta(contas, t_aux.conta_origem);
		printd("[%ld] -  7 got c_origem\n", thread_num);

		// Busca a conta de destino.
		c_destino = busca_conta(contas, t_aux.conta_destino);
		printd("[%ld] -  8 got c_destino\n", thread_num);

		// Se alguma das contas não existe, fracassa também.
		if (c_origem == NULL ||  c_destino == NULL || t_aux.montante < 0.0)
		{
			num_fracassos++;
			printd("[%ld] -  9b Transacao invalida\n");
			continue;
		}
		
		// INICIO Área crítica - Transação.
		{
			// Pede mutex na conta origem
			printd("[%ld] - 9a wait mut_origin - %u\n", thread_num, t_aux.conta_origem);
			pthread_mutex_lock(&(c_origem->mutex));	// Deveria bloquear a conta.
			printd("[%ld] - 10 got mut_origin  - %u\n", thread_num, c_origem->conta);
			
			// Se tiver saldo insuficiente então fracassa.
			if (c_origem->saldo < t_aux.montante)
			{
				num_fracassos++;
				pthread_mutex_unlock(&(c_origem->mutex));
				printd("[%ld] - 11b gave mut_origin - %u - Salso insuficiente\n", thread_num, c_origem->conta);
				continue;
			}

			c_origem->saldo -= t_aux.montante;
			pthread_mutex_unlock(&(c_origem->mutex));
			printd("[%ld] - 11a gave mut_origin - %u\n", thread_num, c_origem->conta);

			// Pede mutex na conta destino.
			printd("[%ld] - 12 wait mut_dest - %u\n", thread_num, c_destino->conta);
			pthread_mutex_lock(&(c_destino->mutex));
			printd("[%ld] - 13 got mut_dest  - %u\n", thread_num, c_destino->conta);
			c_destino->saldo += t_aux.montante;
			pthread_mutex_unlock(&(c_destino->mutex));
			printd("[%ld] - 14 gave mut_dest - %u\n", thread_num, c_destino->conta);
		}
		// FIM Área crítica - Transação.

		// Tudo deu certo.

		// Tire uma folga, você merece!
		rand_sleep(SLEEP_THREAD);
	}

	pthread_exit(0);
}

// Função da main.
int main(int argc, char * argv[]) {
	long time_start = get_time_msec();
	FILE *f_base = NULL, *f_trans = NULL;
	int NUMTHREADS = -1, i;
	pthread_t *threads;

	// INICIO Verificação de argumentos e abertura de arquivos.
	if (argc != 4)
	{
		puts("Uso correto:");
		puts("$ ./tbanc <arqcontas> <arqtrans> <numthreads>");
		puts("\n\t<arqconta>\t\tArquivo de contas conforme descrição do trabalho.");
		puts("\t<arqtrans>\t\tArquivo de transações conforme descrição do trabalho.");
		puts("\t<numthreads>\t\tNúmero de threads executoras de transações.");
		return 1;
	}
	else
	{
		f_base = fopen(argv[1], "r");
		if (f_base == NULL)
		{
			printf("Erro em fopen(\"%s\"). O arquivo existe?\n", argv[1]);
			return 1;
		}

		f_trans = fopen(argv[2], "r");
		if (f_trans == NULL)
		{
			printf("Erro em fopen(\"%s\"). O arquivo existe?\n", argv[2]);
			return 1;
		}

		sscanf(argv[3], "%d", &NUMTHREADS);
		if (NUMTHREADS < 1)
		{
			printf("Erro: número de threads deve ser 1 ou maior.\n");
			return 1;
		}
	}
	// FIM Verificações iniciais.

	// INICIO Ler contas em banco para LDSE de contas.
	Conta c_aux;
	while (!feof(f_base))
	{
		if (fscanf(f_base, "%d %lf", &(c_aux.conta), &(c_aux.saldo)) != 2)
			break;
		insere_conta(&contas, c_aux);
	}
	// FIM Leitura de contas.
	
	// INICIO Impressão de saldos das contas.
	printf("Saldos iniciais:\n");
	imprime_saldos(contas);
	// FIM Impressão de saldos.

	// INICIO Criação de semáforos e mutexes.
	// Semáforos: *sem_transacao;
	// Mutexes: mut_transacao;
	sem_transacao = sem_open("/sem_tbanc_transacao", O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (sem_transacao == SEM_FAILED)
	{
		printf("Erro em sem_open()\n");
		return 1;
	}

	if (pthread_mutex_init(&mut_transacao, NULL) != 0)
	{
		printf("Erro inicializando mut_transacao\n");
		return 1;
	}
	// FIM Criação de semáforos e mutexes.

	// INICIO Criação das threads trabalhadoras.
	acabou = 0;
	threads = malloc(sizeof(pthread_t) * NUMTHREADS);
	int *thr_err = malloc(sizeof(int) * NUMTHREADS);
	if (threads == NULL)
	{
		printf("Erro na alocação de identificadores de threads.\n");
		return 1;
	}
	long d;
	for (i = 0; i < NUMTHREADS; i++)
	{
		d = i;
		thr_err[i] = 0;
		if (pthread_create(&threads[i], NULL, run_transaction, (void*) d) != 0)
		{
			printf("Erro nao fatal: Problema na criacao da thread #%d\n", i);
			thr_err[i] = 1;
		}
	}
	// FIM Criação das threads.

	// INICIO Checar se há ao menos uma thread viva.
	int its_ok = 0;
	for (i = 0; i < NUMTHREADS; i++)
	{
		if (thr_err[i] == 0)
			its_ok = 1;
	}
	if (!its_ok)
	{
		printf("ERRO FATAL: Nenhuma thread foi criada com sucesso.\n");
		goto label_fim;
	}
	// FIM Checar se há ao menos uma thread viva.

	// INICIO Enfileiramento das transações.
	Transacao t_aux;
	while (!feof(f_trans))
	{
		printd("main - Tenta ler nova transacao\n");
		if (fscanf(f_trans, "%u%u%lf", &(t_aux.conta_origem), &(t_aux.conta_destino), &(t_aux.montante)) != 3)
			break;

		// INICIO Área crítica, usa mutex pois ocorre em paralelo com os executores de transações.
		printd("main -  1 espera mut_transacao\n");
		pthread_mutex_lock(&mut_transacao);
		printd("main -  2 pegou  mut_transacao\n");

		insere_transacao(&transacoes, t_aux);
		printd("main -  3 transacao inserida\n");
		pthread_mutex_unlock(&mut_transacao);
		printd("main -  4 liberou mut_transacao\n");
		// FIM Área crítica

		sem_post(sem_transacao);
		rand_sleep(SLEEP_MAIN);
	}

	acabou = 1;
	printd("main -  5 Acabaram as transacoes\n");
	sem_post(sem_transacao);	// Sinaliza para as threads continuarem, mas elas vão verificar
								// que acabou == 1 e irão se suicidar.
	// FIM Enfileiramento das transações.

	// INICIO Espera pela finalização das threads executoras de transações.
	long ret_threads[] = {0};
	for (i = 0; i < NUMTHREADS; i++)
	{
		if (thr_err[i] == 1) continue; // Pular a thread que não foi criada com sucesso.
		pthread_join(threads[i], (void**) &ret_threads);
	}
	// FIM Espera finalização das threads.
	
	// INICIO Imprime estatísticas.
	imprime_estatisticas(num_processos, num_fracassos);
	
	// INICIO Impressão de saldos das contas após todas as operações.
	printf("Saldos finais:\n");
	imprime_saldos(contas);
	// FIM Impressão de saldos.

label_fim:
	
	// INICIO Destruir semáforos e mutexes.
	if (sem_close(sem_transacao) == -1)
	{
		printf("Erro em sem_close()\n");
		return 1;
	}
	if (sem_unlink("/sem_tbanc_transacao") == -1)
	{
		printf("Erro em sem_unlink()\n");
		return 1;
	}
	// FIM Destruir semáforos e mutexes.

	// INICIO Destruir lista de contas.
	destruir_contas(&contas);
	// FIM Destruir lista de contas.

	printf("Tempo total: %0.3lf segundos\n", (get_time_msec() - time_start)/1000.f );

	return 0;
}