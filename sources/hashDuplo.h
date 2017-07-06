#ifndef HASHDUPLO_H_INCLUDED
#define HASHDUPLO_H_INCLUDED

#include "cedula.h"

typedef struct{

    cedula *itens;
    int M, tamanho;

}hashDuplo;

typedef hashDuplo *tabelaHashDuplo;

/**
    Cria uma tabela hash com resolu��o de colis�es por hash duplo.
    @param int tamanho: O tamanho total da tabela hash.
    @return Um ponteiro para uma regi�o de mem�ria que representa a estrutura da tabela "hashDuplo".
    "NULL" caso contr�rio.

*/
tabelaHashDuplo criaTabelaHashDuplo(int tamanho);

/**
    Calcula uma posi��o v�lida para o "hashArvore" atrav�s do t�tulo de eleitor.
    @param tabelaHashArvore tabela: Ponteiro para a tabela hash v�lida.
    @param char s: t�tulo de eleitor que ter� seu hash calculado.
    @return Uma posi��o v�lida(inteiro positivo) para a tabela hash.
*/
int hashDuploIndiceEleitores(tabelaHashDuplo tabela, char *s);
int hashDuploIndiceEleitores2(tabelaHashDuplo tabela, char *s);

/**
    Insere uma c�dula na tabela hash duplo.
    @param tabelaHashDuplo t: Tabela em que ser� inclu�da o novo elemento.
    @param cedula ced: A c�dula de vota��o do eleitor.
    @return 1 se a inser��o ocorreu com sucesso, 0 caso contr�rio.

*/
int insereTabelaHashDuplo(tabelaHashDuplo t, cedula ced);


/**
    Remove uma c�dula na tabela hash duplo.
    @param tabelaHashDuplo t: Tabela em que ser� removido o elemento.
    @param char *titulo: Do Eleitor que ser� removido.
    @param cedula ced: A c�dula de vota��o do eleitor.
    @return 1 se a inser��o ocorreu com sucesso, 0 caso contr�rio.
*/
int removeTabelaHashDuplo(tabelaHashDuplo t, char *titulo, cedula *e);


/**
    Verifica se um elemento est� na tabela hash, caso esteja retorna o indice, caso contr�rio
    retorna -1.
    @param tabelaHashDuplo t: Tabela em que ser� pesquisado o elemento.
    @param char *titulo: Do Eleitor que ser� removido.
    @return indice caso o titulo exista -1 caso contr�rio.

*/
int pesquisaTabelaHashDuplo(tabelaHashDuplo t, char *titulo);


/**
    Imprime a tabela hash duplo.
    @param tabelaHashDuplo t: Tabela que ser� printada.

*/
void imprimeHashDuplo(tabelaHashDuplo t);


/**
    Termina a tabela hash duplo.
    @param tabelaHashDuplo t: Tabela que ser� finalizada.
*/
void terminaHashDuplo(tabelaHashDuplo t);

#endif // HASHDUPLO_H_INCLUDED
