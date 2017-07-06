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
    @return Um ponteiro para uma regi�o de mem�ria que representa a estrutura da tabela "hashArvore".
    "NULL" caso contr�rio.

*/
tabelaHashArvore criaTabelaHashArvore(int tamanho);

/**
    Calcula uma posi��o v�lida para o "hashArvore" atrav�s do n�mero do candidato.
    @param tabelaHashArvore tabela: Ponteiro para a tabela hash v�lida.
    @param int numeroCandidato: N�mero do candidato que ter� seu hash calculado.
    @return Uma posi��o v�lida(inteiro positivo) para a tabela hash.
*/
int hashIndiceCandidato(tabelaHashArvore tabela, int numeroCandidato);

/**
    Calcula uma posi��o v�lida para o "hashArvore" atrav�s do t�tulo de eleitor.
    @param tabelaHashArvore tabela: Ponteiro para a tabela hash v�lida.
    @param char s: t�tulo de eleitor que ter� seu hash calculado.
    @return Uma posi��o v�lida(inteiro positivo) para a tabela hash.
*/
int hashIndiceEleitores(tabelaHashArvore tabela, char *s);

/**
    Insere uma c�dula na tabela hash com colis�es por �rvore bin�ria de pesquisa.
    @param tabelaHashArvore t: Tabela em que ser� inclu�da o novo elemento.
    @param cedula ced: A c�dula de vota��o do eleitor.
    @return 1 se a inser��o ocorreu com sucesso, 0 caso contr�rio.

*/
int insereTabelaHashArvore(tabelaHashArvore t, cedula ced);


/**
    Remove uma c�dula na tabela hash com colis�es por �rvore bin�ria de pesquisa.
    @param tabelaHashArvore t: Tabela em que ser� removido o elemento.
    @param char *titulo: Do Eleitor que ser� removido.
    @param cedula ced: A c�dula de vota��o do eleitor.
    @return 1 se a inser��o ocorreu com sucesso, 0 caso contr�rio.
*/
int removeTabelaEleitorHashArvore(tabelaHashArvore t, char *titulo, cedula *e);

// Insere uma c�dula na tabela de eleitores.
/*int insereTabelaEleitoresHashLista(tabelaHashLista t, tipoCedula);

// Verifica se um eleitor j� votou em alguma candidato.
int pesquisaRepeticaoDeVoto(tabelaHashLista t, tipoCedula cedula);


// Pesquisa a quantidade de cedulas um candidato recebeu. Passa a tabela e o n�mero do candidato.
int pesquisaTabelaHashLista(tabelaHashLista t, int numeroCandidato, tipoCedula *copia);

// Remove uma c�dula da tabela. Passa a tabela, o titulo e o n�mero do candidato que deseja excluir e a cedula para armazenar.
int removeTabelaHashLista(tabelaHashLista t, char *titulo, int numeroCandidato, tipoCedula *copia);

// Finaliza a tabela.
void terminaTabelaHashLista(tabelaHashLista t);*/

void imprimeHashArvore(tabelaHashArvore t);

void terminaHashArvore(tabelaHashArvore t);

#endif // HASHARVORE_H_INCLUDED
