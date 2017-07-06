#ifndef ARVOREBINARIA_H_INCLUDED
#define ARVOREBINARIA_H_INCLUDED

#include "cedula.h"

typedef struct No{

    cedula info;
    struct No *esquerda;
    struct No *direita;

} arvoreBinaria;

typedef arvoreBinaria *arvore;

typedef struct{

    arvore root;
    int nos;

}arv;

typedef arv *tree;

// Cria uma arvore bin�ria de pesquisa.
void criarArvore(arvore *);

// Insere um elemento na �rvore bin�ria.
int inserirArvore(arvore *, cedula, int*);

// Fun��es para remover um elemento da arvore.
arvore filhoDireita(arvore *);
arvore filhoEsquerda(arvore *);
void arvoreRemover(arvore *, cedula, int*);

// Imprime a arvore.
void imprimeArvore(arvore);

// Conta a quantidade de n�s da arvore.
int contarNos(arvore);

// Conta a quantidade de folhas.
int contarFolhas(arvore);

// Tamanho da arvore.
int maior(int a, int b);
int altura(arvore);

// Pesquisa um elemento na �rvore. Retorna 1 se achou e 0 caso contrario.
cedula *pesquisaElementoBinaria(arvore, char *);

// Cria uma tree.
tree criaTree();

// Insere na Tree
int insereTree(tree, cedula);

// Remove da tree.
int removeTree(tree, cedula);

// Pesquisa tree.
cedula *pesquisaTree(tree, char *);

// Imprime a tree.
void imprimeTree(tree);

#endif // ARVOREBINARIA_H_INCLUDED
