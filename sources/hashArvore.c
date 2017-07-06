#include "hashArvore.h"

// ************************************** Cria tabela arvore **************************************

// Cria a tabela hash.
tabelaHashArvore criaTabelaHashArvore(int tamanho){

    int m = tamanho;
	int contador = 0;

	// Alocando uma tabela de m posições.
	tabelaHashArvore table = (tabelaHashArvore)malloc(sizeof(hashArvore));

	if (table != NULL){

		// Aloca um vetor de ponteiros para uma lista.
		table->itens = (tree)malloc(m*sizeof(arv));

		if (table->itens != NULL){

			for (contador = 0; contador < m; contador++){

                table->itens[contador].root = NULL;
                table->itens[contador].nos = 0;

			}

		}

		else
			return NULL;

	}

	else
		return NULL;

	table->M = m;
	table->tamanho = 0;

	return table;


}// Fim do criaTabelaHashLista


// ********************************* Calcula o indice na tabela *********************************

// Calcula o indice para a tabela através do número do eleitor.
int hashIndiceCandidato(tabelaHashArvore tabela, int numeroCandidato){

     // Retorna o indice da tabela.
	 return numeroCandidato % tabela->M;
}

// Calcula o indice para a tabela através do titulo do eleitor.
int hashIndiceEleitores(tabelaHashArvore tabela, char *s){

    int i;
    int total = 0;

    // Soma o código ascii dos caracteres e depois divide pelo módulo para calcular um indice.
    for (i=0; s[i]!='\0'; i++)
        total += s[i];

    return total % tabela->M;

}

// ********************************* Insere Tabela Hash Arvore *********************************

// Insere uma cédula na tabela.
int insereTabelaHashArvore(tabelaHashArvore t, cedula ced){

    // Recebe o indice da a tabela.
	int indice = hashIndiceEleitores(t, ced.titulo);

	if (insereTree(&t->itens[indice], ced) == 1){
        t->tamanho++;
        //printf("\n\n ---------------------------> %d \n\n", t->tamanho);
		return 1;
		}

	return 0;

}

// ************************************** Remove da tabela arvore **************************************

int removeTabelaEleitorHashArvore(tabelaHashArvore t, char *titulo, cedula *e){

    // Recebe o indice da tabela.
	int indice = hashIndiceEleitores(t, titulo);
	cedula cel;
    cedula *ced = pesquisaTree(&t->itens[indice], titulo);

    if(ced == NULL)
        return 0;

    strcpy(cel.titulo, ced->titulo);
    cel.presidente = ced->presidente;
    cel.senador = ced->senador;

    *e = cel;

    // Tem que fazer uma verificação aqui.
    if(removeTree(&t->itens[indice], *ced) == 1){
        t->tamanho--;
        return 1;
    }

    return 0;

}

// ************************************** Imprime tabela arvore **************************************

void imprimeHashArvore(tabelaHashArvore t){

    int contador;

    for(contador = 0; contador < t->M; contador++){

        printf("\n\n Pos[%d de %d]->\n", contador, t->M);
        imprimeTree(&t->itens[contador]);

    }

}

// ************************************** Termina tabela arvore **************************************

void terminaHashArvore(tabelaHashArvore t){

    int contador;

    for(contador = 0; contador < t->tamanho; contador++){

        if(t->itens[contador].root != NULL)
            free(&t->itens[contador]);

    }

    free(t->itens);
    free(t);

}
