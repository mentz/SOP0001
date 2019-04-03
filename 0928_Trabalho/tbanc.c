#include "tbanc.h"
#include "utils.h"

// Inserção de conta na lista de contas
void insere_conta(pConta *primeira_conta, Conta nova_conta)
{
	// Esse procedimento não é threadsafe mas não precisa usar semáforos
	// ou mutexes pois ocorre antes da criação de qualquer thread.
	pConta pcaux = *primeira_conta;
	pConta p_nova_conta = malloc(sizeof(Conta));

	while (pcaux != NULL && pcaux->next != NULL)
		pcaux = pcaux->next;
	
	// Inicializando valores do novo nó de conta.
	p_nova_conta->conta = nova_conta.conta;
	p_nova_conta->saldo = nova_conta.saldo;
	pthread_mutex_init(&(p_nova_conta->mutex), NULL);
	p_nova_conta->next  = NULL;

	// Se a lista estiver vazia, cria o primeiro nó.
	if (pcaux == NULL)
		*primeira_conta = p_nova_conta;
	// Se não, atualiza ponteiro next do último nó.
	else
		pcaux->next = p_nova_conta;
}

// Busca a instância da conta para efetuar transações.
pConta busca_conta(pConta lista_contas, uint conta)
{
	pConta pcaux = lista_contas;
	while (pcaux != NULL)
	{
		if (pcaux->conta == conta)
			break;
		pcaux = pcaux->next;
	}

	return pcaux;
}

// Destrói a lista de contas para finalizar o programa.
void destruir_contas(pConta *contas)
{
	pConta pcaux;
	
	while ((*contas) != NULL)
	{
		pcaux = (*contas)->next;
		(*contas)->conta = 0;
		(*contas)->saldo = 0;
		pthread_mutex_destroy(&((*contas)->mutex));
		(*contas)->next = NULL;
		free(*contas);
		(*contas) = pcaux;
	}
}

// Inserção de transação na fila de transações
void insere_transacao(pTransacao *p_transacao, Transacao nova_transacao)
{
	pTransacao ptaux = *p_transacao;
	while (ptaux != NULL && ptaux->next != NULL)
		ptaux = ptaux->next;

	pTransacao p_nova_transacao = malloc(sizeof(Transacao));

	// Inicializando valores do novo nó de transação.
	p_nova_transacao->conta_origem 	= nova_transacao.conta_origem;
	p_nova_transacao->conta_destino = nova_transacao.conta_destino;
	p_nova_transacao->montante		= nova_transacao.montante;
	p_nova_transacao->next  		= NULL;

	// Se a lista estiver vazia, cria o primeiro nó.
	if (ptaux == NULL)
		*p_transacao = p_nova_transacao;
	// Se não, atualiza ponteiro next do último nó.
	else
		ptaux->next = p_nova_transacao;
}

// Consome transação e retorna 
Transacao consome_transacao(pTransacao *prox_transacao)
{
	pTransacao ptaux = *prox_transacao;

	Transacao ret;
	ret.conta_origem 	= ptaux->conta_origem;
	ret.conta_destino 	= ptaux->conta_destino;
	ret.montante 		= ptaux->montante;
	ret.next 			= NULL;

	// Libera espaço da transação atual e avança uma transação.
	free(*prox_transacao);
	*prox_transacao = ptaux->next;

	return ret;
}

// Imprime saldos
void imprime_saldos(pConta contas)
{
	int c = 1;
	pConta pcaux = contas;
	while (pcaux != NULL)
	{
		printf("conta %d: num=%u, saldo=%0.2f\n", c++, pcaux->conta, pcaux->saldo);
		pcaux = pcaux->next;
	}
}

// Imprime estatísticas
void imprime_estatisticas(long processos, long fracassos)
{
	printf("Transações:\n");
	printf("\tProcessadas   = %ld\n", processos);
	printf("\tBem-sucedidas = %ld\n", processos - fracassos);
}