#ifndef AUXILIARES_H_INCLUDED
#define AUXILIARES_H_INCLUDED

#include "cedula.h"
#include "hashAberto.h"
#include "apuracao.h"
#include "hashLista.h"

# define MAX 20
# define MAX_STRING 50

// Pega o tamanho das tabelas.
int validaTamanhoTabelas(char *str, int *presidentes, int *senadores, int *eleitores);

// formata e retorna o tamanho das tabelas.
int leValidaString(char *str, char *opcao, int *cla, char *t, int *n, int *ran);


// Entra no modo campeonato.
void modoCampeonato(FILE **arq);

#endif // AUXILIARES_H_INCLUDED
