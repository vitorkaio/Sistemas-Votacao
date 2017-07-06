#include "hashDuplo.h"

// ************************************** Cria tabela duplo **************************************

tabelaHashDuplo criaTabelaHashDuplo(int tamanho){

    int contador;
	tabelaHashDuplo t;

	t = (tabelaHashDuplo)malloc(sizeof(hashDuplo));

	if (t){

         t->itens = (cedula*)malloc(tamanho * sizeof(cedula));

          if(t->itens != NULL)

		for (contador = 0; contador < tamanho; contador++){

			t->itens[contador].presidente = 0;
			t->itens[contador].senador = 0;
			strcpy(t->itens[contador].titulo, "");

		}

        t->M = tamanho;
        t->tamanho = 0;
		return t;
	}

	return NULL;

}

// ****************************** Calcula o índice *******************************

// Calcula o indice para a tabela através do titulo do eleitor.
int hashDuploIndiceEleitores(tabelaHashDuplo tabela, char *s){

    int i;
    int total = 0;

    // Soma o código ascii dos caracteres e depois divide pelo módulo para calcular um indice.
    for (i=0; s[i]!='\0'; i++)
        total += s[i];

    return total % tabela->M;

}

int hashDuploIndiceEleitores2(tabelaHashDuplo tabela, char *s){

    int k;
    k = strlen(s);
    return (k * 17 + k * 19) % tabela->M;

}


// ****************************** Insere na tabela hash *******************************
int insereTabelaHashDuplo(tabelaHashDuplo t, cedula ced){

    int i = hashDuploIndiceEleitores(t, ced.titulo);
    int k = hashDuploIndiceEleitores2(t, ced.titulo);
    int cont = 0, aux;

    if(k == 0)
        k++;

    // Verifica se o elemento existe na tabela, caso sim add o voto.
    aux = pesquisaTabelaHashDuplo(t, ced.titulo);
    if(aux != -1){

        // Verifica se o item já existe na tabela, se sim será avaliado se o voto pode ser realizado.
        if (strcmp(t->itens[aux].titulo, ced.titulo) == 0){

                // Verifica se não votou pra presidente.
            if(t->itens[aux].presidente == 0 && ced.presidente != 0){
                t->itens[aux].presidente = ced.presidente;
                return 1;
            }

            // Verifica se não votou para senador.
            if(t->itens[aux].senador == 0 && ced.senador != 0){
                t->itens[aux].senador = ced.senador;
                return 1;
            }

            else
                return 0;
        }

    }

    // Procura a próxima posição livre. TEM UM ERRO FUDIDO AQUI.
    while(strlen(t->itens[i].titulo) != 0) {

        if (++cont >= t->M)
            return 0; // Tabela cheia

        i += k % t->M; // Tabela circular

        if(i >= t->M)
            i = 0;
    }

    // achamos uma posição livre.
    t->itens[i] = ced;
    t->tamanho++;
    return 1;

}

// ****************************** Remove na tabela hash *******************************

int removeTabelaHashDuplo(tabelaHashDuplo t, char *titulo, cedula *e){

    int aux;

     // Verifica se o elemento existe na tabela, caso sim remove o voto.
    aux = pesquisaTabelaHashDuplo(t, titulo);
    if(aux != -1){

        // Se o item estiver na tabela, então ele é removido.
        if (strcmp(t->itens[aux].titulo, titulo) == 0){

             *e = t->itens[aux];
             strcpy(t->itens[aux].titulo, "");
             t->itens[aux].presidente = 0;
             t->itens[aux].senador = 0;
             t->tamanho--;
             return 1;

        }

        else
            return 0;

    }

 return 0;

}


// ****************************** Pesquisa a tabela hash *******************************
int pesquisaTabelaHashDuplo(tabelaHashDuplo t, char *titulo){

    int i = hashDuploIndiceEleitores(t, titulo);
    int k = hashDuploIndiceEleitores2(t, titulo);
    int cont = 0;

    if(k == 0)
        k++;

    while(strcmp(t->itens[i].titulo, titulo) != 0){

        if (++cont == t->M)
            return -1; // Tabela cheia.

        i += k % t->M; // Tabela circular.

        if(i >= t->M)
            i = 0;

    }

    return i;

}

// ****************************** Imprime a tabela hash *******************************


void imprimeHashDuplo(tabelaHashDuplo t){

    int contador;

    for(contador = 0; contador < t->M; contador++){

        printf("\n\n Pos[%d de %d]->\n\n Titulo: %s\n Presidente: %d\n Senador: %d",
               contador, t->M, t->itens[contador].titulo, t->itens[contador].presidente,
               t->itens[contador].senador);

    }

}


void terminaHashDuplo(tabelaHashDuplo t){

    free(t->itens);
    free(t);

}
