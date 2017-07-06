#ifndef HASHABERTO_H_INCLUDE
#define HASHABERTO_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>

typedef struct {

	int numero; // Número do candidato.
	int votos; // Quantidade de votos.

} tipoCampos;

typedef struct{

    tipoCampos *itens;
    int quantidade;
    int tamanho;

}tabelaHashAberto;

typedef tabelaHashAberto *hashAberto;

// Cria uma tabela de M posições.
hashAberto criaHashAberto(int M);

// Gera o indice.
int hashIndice(hashAberto t, int numero);

// Insere elementos na tabela, se existir acresenceta votos.
int insereHashAberto(hashAberto t, int numero);

// Retorna a quantidades de votos que um candidato possui.
int quantidadeDeVotos(hashAberto t, int numero);

// Retira um voto, se o número de voto chegar a zero: retira o elemento da tabela.
int removeHashAberto(hashAberto t, int numero);

// Pesquisa um numero na tabela.
int Pesquisa(hashAberto T, int numero);

// Retorna a quantidade de votos no sistema.
int quantidadeDeVotosNoSistema(hashAberto t, hashAberto t2);

// Imprime Hash Aberto
void imprimeHashAberto(hashAberto t);


// Termina o Hash Aberto.
void terminaHashAberto(hashAberto t);

#endif
