#ifndef HASHARVORE_H_INCLUDED
#define HASHARVORE_H_INCLUDED

#include "arvoreBinaria.h"

typedef struct{

    tree itens;
    int M, tamanho;

}hashArvore;

typedef hashArvore *tabelaHashArvore;

/**
    Cria uma tabela hash com ponteiro para um array do tipo "arvore".
    @param int tamanho: O tamanho total da tabela hash.
    @return Um ponteiro para uma região de memória que representa a estrutura da tabela "hashArvore".
    "NULL" caso contrário.

*/
tabelaHashArvore criaTabelaHashArvore(int tamanho);

/**
    Calcula uma posição válida para o "hashArvore" através do número do candidato.
    @param tabelaHashArvore tabela: Ponteiro para a tabela hash válida.
    @param int numeroCandidato: Número do candidato que terá seu hash calculado.
    @return Uma posição válida(inteiro positivo) para a tabela hash.
*/
int hashIndiceCandidato(tabelaHashArvore tabela, int numeroCandidato);

/**
    Calcula uma posição válida para o "hashArvore" através do título de eleitor.
    @param tabelaHashArvore tabela: Ponteiro para a tabela hash válida.
    @param char s: título de eleitor que terá seu hash calculado.
    @return Uma posição válida(inteiro positivo) para a tabela hash.
*/
int hashIndiceEleitores(tabelaHashArvore tabela, char *s);

/**
    Insere uma cédula na tabela hash com colisões por árvore binária de pesquisa.
    @param tabelaHashArvore t: Tabela em que será incluída o novo elemento.
    @param cedula ced: A cédula de votação do eleitor.
    @return 1 se a inserção ocorreu com sucesso, 0 caso contrário.

*/
int insereTabelaHashArvore(tabelaHashArvore t, cedula ced);


/**
    Remove uma cédula na tabela hash com colisões por árvore binária de pesquisa.
    @param tabelaHashArvore t: Tabela em que será removido o elemento.
    @param char *titulo: Do Eleitor que será removido.
    @param cedula ced: A cédula de votação do eleitor.
    @return 1 se a inserção ocorreu com sucesso, 0 caso contrário.
*/
int removeTabelaEleitorHashArvore(tabelaHashArvore t, char *titulo, cedula *e);

// Insere uma cédula na tabela de eleitores.
/*int insereTabelaEleitoresHashLista(tabelaHashLista t, tipoCedula);

// Verifica se um eleitor já votou em alguma candidato.
int pesquisaRepeticaoDeVoto(tabelaHashLista t, tipoCedula cedula);


// Pesquisa a quantidade de cedulas um candidato recebeu. Passa a tabela e o número do candidato.
int pesquisaTabelaHashLista(tabelaHashLista t, int numeroCandidato, tipoCedula *copia);

// Remove uma cédula da tabela. Passa a tabela, o titulo e o número do candidato que deseja excluir e a cedula para armazenar.
int removeTabelaHashLista(tabelaHashLista t, char *titulo, int numeroCandidato, tipoCedula *copia);

// Finaliza a tabela.
void terminaTabelaHashLista(tabelaHashLista t);*/

void imprimeHashArvore(tabelaHashArvore t);

void terminaHashArvore(tabelaHashArvore t);

#endif // HASHARVORE_H_INCLUDED
