#ifndef HASHDUPLO_H_INCLUDED
#define HASHDUPLO_H_INCLUDED

#include "cedula.h"

typedef struct{

    cedula *itens;
    int M, tamanho;

}hashDuplo;

typedef hashDuplo *tabelaHashDuplo;

/**
    Cria uma tabela hash com resolução de colisões por hash duplo.
    @param int tamanho: O tamanho total da tabela hash.
    @return Um ponteiro para uma região de memória que representa a estrutura da tabela "hashDuplo".
    "NULL" caso contrário.

*/
tabelaHashDuplo criaTabelaHashDuplo(int tamanho);

/**
    Calcula uma posição válida para o "hashArvore" através do título de eleitor.
    @param tabelaHashArvore tabela: Ponteiro para a tabela hash válida.
    @param char s: título de eleitor que terá seu hash calculado.
    @return Uma posição válida(inteiro positivo) para a tabela hash.
*/
int hashDuploIndiceEleitores(tabelaHashDuplo tabela, char *s);
int hashDuploIndiceEleitores2(tabelaHashDuplo tabela, char *s);

/**
    Insere uma cédula na tabela hash duplo.
    @param tabelaHashDuplo t: Tabela em que será incluída o novo elemento.
    @param cedula ced: A cédula de votação do eleitor.
    @return 1 se a inserção ocorreu com sucesso, 0 caso contrário.

*/
int insereTabelaHashDuplo(tabelaHashDuplo t, cedula ced);


/**
    Remove uma cédula na tabela hash duplo.
    @param tabelaHashDuplo t: Tabela em que será removido o elemento.
    @param char *titulo: Do Eleitor que será removido.
    @param cedula ced: A cédula de votação do eleitor.
    @return 1 se a inserção ocorreu com sucesso, 0 caso contrário.
*/
int removeTabelaHashDuplo(tabelaHashDuplo t, char *titulo, cedula *e);


/**
    Verifica se um elemento está na tabela hash, caso esteja retorna o indice, caso contrário
    retorna -1.
    @param tabelaHashDuplo t: Tabela em que será pesquisado o elemento.
    @param char *titulo: Do Eleitor que será removido.
    @return indice caso o titulo exista -1 caso contrário.

*/
int pesquisaTabelaHashDuplo(tabelaHashDuplo t, char *titulo);


/**
    Imprime a tabela hash duplo.
    @param tabelaHashDuplo t: Tabela que será printada.

*/
void imprimeHashDuplo(tabelaHashDuplo t);


/**
    Termina a tabela hash duplo.
    @param tabelaHashDuplo t: Tabela que será finalizada.
*/
void terminaHashDuplo(tabelaHashDuplo t);

#endif // HASHDUPLO_H_INCLUDED
