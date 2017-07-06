#ifndef ARVOREAVL_H_INCLUDED
#define ARVOREAVL_H_INCLUDED

#include "cedula.h"

typedef struct avl{

    cedula info;
    int bal;
    struct  avl *pai;
    struct  avl *esq;
    struct  avl *dir;

}arvoreAvl;

typedef arvoreAvl *avl;

// Calcula o tamanho da arvore.
int avl_height (avl);

// Faz a rotação para a esquerda.
avl rotacaoLL(avl);

// Faz a rotação para a direita.
avl rotacaoRR (avl);

// Remove um elemento da arvore avl.
void avlRemove (avl *, char *);

// Insere um elemento na arvore avl
int inserirAvl(avl *, avl *, cedula, int*);

// Imprime a arvore.
void imprimeAvl(avl);

// Termina a arvore avl.
void destruir(avl *);

// Pesquisa um elemento na árvore. Retorna 1 se achou e 0 caso contrario.
cedula *pesquisaElemento(avl, char *);


#endif // ARVOREAVL_H_INCLUDED
