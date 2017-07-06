#ifndef LISTA_ENCADEADA_H_INCLUDED
#define LISTA_ENCADEADA_H_INCLUDED

#include "cedula.h"

typedef struct nodo *tnodo;

typedef struct nodo {
  cedula cedula;
  tnodo prox;

} tipo_nodo;

typedef struct{

   tnodo primeiro, ultimo;
   int tamanho;

} tipo_lista;

typedef tipo_lista *lista;

lista cria_lista();

// Insere uma cedula na lista.
int insere_lista(lista, cedula);

// Remove uma cedula da lista.
int remove_lista(lista, char*, cedula*);

// Pesquisa quantos cédulas um candidato recebeu.
int pesquisa_lista(lista, int, cedula*);

// Pesquisa se uma candidato já votou. Passa a lista, cedula nova.
int pesquisaVotoEleitores_lista(lista, cedula);

// Encerra a lista.
void termina_lista(lista);



#endif // LISTA_ENCADEADA_H_INCLUDED
