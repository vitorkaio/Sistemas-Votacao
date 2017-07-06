#ifndef APURACAO_H_INCLUDED
#define APURACAO_H_INCLUDED

#include "hashAberto.h"

// Essa função recebe a tabela, processa os dados e aloca um vetor dinamico para computar os votos. Retorna o tamanho da tabela.
int apuraVotos(hashAberto t, int ranks, int **vet);

// Gera um arquivo com o ranking dos mais votados.
void finalizaVotacao(hashAberto prefeito, hashAberto vereador, char *estrutura);


#endif // FUNCAOAPURACAO_H_INCLUDED
