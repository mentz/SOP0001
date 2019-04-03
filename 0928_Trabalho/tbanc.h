#ifndef TBANC_H
#define TBANC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

typedef unsigned int uint; // Facilitar escrita.

// Estrutura de contas
typedef struct conta {
	uint 	conta;
	double 	saldo;
	pthread_mutex_t mutex;
	struct conta *next;
} Conta, *pConta;

// Estrutura de transações
typedef struct transacao {
	uint 	conta_origem;
	uint	conta_destino;
	double	montante;
	struct transacao *next;
} Transacao, *pTransacao;

// Inserção de conta na lista de contas
void insere_conta(pConta *primeira_conta, Conta nova_conta);

// Busca a instância da conta para efetuar transações.
pConta busca_conta(pConta lista_contas, uint conta);

// Destrói a lista de contas para finalizar o programa.
void destruir_contas(pConta *contas);

// Inserção de transação na fila de transações.
void insere_transacao(pTransacao *p_transacao, Transacao nova_transacao);

// Consome transação e retorna.
Transacao consome_transacao(pTransacao *prox_transacao);

// Imprime saldos.
void imprime_saldos(pConta primeira_conta);

// Imprime estatísticas.
void imprime_estatisticas(long processos, long fracassos);

#endif