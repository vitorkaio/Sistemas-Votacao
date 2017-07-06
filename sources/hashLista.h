#ifndef HASHLISTA_H_INCLUDE
#define HASHLISTA_H_INCLUDE

#include "lista_encadeada.h"

// Estrutura que define a tabela Hash com lista encadeada.
typedef struct{

	lista itens;
	unsigned int M, tamanho;

}tipoTabela;

typedef tipoTabela *tabelaHashLista;

// Cria a tabela hash.
tabelaHashLista criaTabelaHashLista(int tamanho);

// Calcula o indice para a tabela através do número do eleitor.
int hashListaIndiceCandidato(tabelaHashLista tabela, int numeroCandidato);

// Calcula um indice para a tabela de eleitores.
int hashListaIndiceEleitores(tabelaHashLista tabela, char *s);

// Insere uma cédula na tabela.
int insereTabelaHashLista(tabelaHashLista t, cedula cedula);

// Insere uma cédula na tabela de eleitores.
int insereTabelaEleitoresHashLista(tabelaHashLista t, cedula);

// Verifica se um eleitor já votou em alguma candidato.
int pesquisaRepeticaoDeVoto(tabelaHashLista t, cedula cedula);

// Remove votos de um eleitor.
int removeTabelaEleitorHashLista(tabelaHashLista t, char *titulo, cedula *e);

// Pesquisa a quantidade de cedulas um candidato recebeu. Passa a tabela e o número do candidato.
int pesquisaTabelaHashLista(tabelaHashLista t, int numeroCandidato, cedula *copia);

// Remove uma cédula da tabela. Passa a tabela, o titulo e o número do candidato que deseja excluir e a cedula para armazenar.
int removeTabelaHashLista(tabelaHashLista t, char *titulo, int numeroCandidato, cedula *copia);

// Finaliza a tabela.
void terminaTabelaHashLista(tabelaHashLista t);

#endif
