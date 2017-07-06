#include "hashAberto.h"

// ********************************* Cria a tabela *********************************

// Cria uma tabela de M posições.
hashAberto criaHashAberto(int M){

	int contador;
	hashAberto t;

	t = (tabelaHashAberto*)malloc(sizeof(tabelaHashAberto));

	if (t){

         t->itens = (tipoCampos*)malloc(M * sizeof(tipoCampos));

          if(t->itens != NULL)

		for (contador = 0; contador < M; contador++){

			t->itens[contador].numero = 0;
			t->itens[contador].votos = 0;

		}

        t->quantidade = 0;
        t->tamanho = M;
		return t;
	}

	return NULL;
}

// ********************************* Calcula o indice na tabela *********************************

// Gera o indice
int hashIndice(hashAberto t, int numero){

	return numero % t->tamanho;

}

/* ********************************* Pesquisa na tabela ********************************* */

int Pesquisa(hashAberto t, int numero){

	int i = hashIndice(t, numero);
    int cont = 0;

    if(numero == 0)
        return 0;

     // Procura a próxima posição livre.
    while (t->itens[i].numero != numero) {

        if (++cont == t->tamanho)
            return -1; // Tabela cheia.

        if (++i >= t->tamanho)
            i = 0; // Tabela circular.
    }

    return i;

}

// ********************************* Insere na tabela *********************************

// Insere elementos na tabela, se existir acrescenta votos.
int insereHashAberto(hashAberto t, int numero){

    int i = hashIndice(t, numero);
    int cont = 0, aux;

    if(numero == 0)
        return 0;


     aux = Pesquisa(t, numero);
     if(aux != -1){

        // Verifica se o item já existe na tabela, caso esteja, o número de votos é incrementado.
        if (t->itens[aux].numero == numero){

            t->itens[aux].votos++;
            t->quantidade++;

            return 1;

        }

     }

    // Procura a próxima posição livre.
    while (t->itens[i].numero != 0) {

        if (++cont == t->tamanho)
            return 0; // Tabela cheia.

        if (++i >= t->tamanho)
            i = 0; // Tabela circular.
    }

 // Achamos uma posição livre.
 t->itens[i].numero = numero;
 t->itens[i].votos++;
 t->quantidade++;

 return 1;

}

// ********************************* Remove da tabela *********************************

// Retira um voto, se o número de voto chegar a zero: retira o elemento da tabela.
int removeHashAberto(hashAberto t, int numero){

    int i = hashIndice(t, numero);
    int aux;

     if(numero == 0)
        return 0;


    aux = Pesquisa(t, numero);
    if(aux != -1){

        // Verifica se o item já existe na tabela, se sim será avaliado se o voto pode ser realizado.
        if (t->itens[i].numero == numero){

            t->itens[i].votos--;
            t->quantidade--;

            // Se chegar a zero quer dizer que não tem mais votos para o candidato em questao.
            if(t->itens[i].votos == 0){
                t->itens[i].numero = 0;
                t->itens[i].votos = 0;
            }

            return 1;

        }


    }

 return 0;

}

// ********************************* Quantidade votos candidato. *********************************

// Retorna a quantidades de votos que um candidato possui.
int quantidadeDeVotos(hashAberto t, int numero){

	int i = hashIndice(t, numero);
    int cont = 0;

    if(numero == 0)
        return 0;


    while(t->itens[i].numero != 0) {

        if (t->itens[i].numero == numero){
           return t->itens[i].votos;
        }

        if (++cont == t->tamanho)
            return 0; // Tabela cheia.

        if (++i == t->tamanho)
            i = 0; // Tabela circular.
    }

 return 0;

}

// ********************************* Quantidade votos sistema *********************************

// Retorna a quantidade de votos no sistema.
int quantidadeDeVotosNoSistema(hashAberto t, hashAberto t2){

    return t->quantidade + t2->quantidade;

}

// ********************************* Imprime hash aberto *********************************

void imprimeHashAberto(hashAberto t){

    int contador = 0;

    for(contador = 0; contador < t->tamanho; contador++)
        printf("\n\n Pos[%d de %d]->\n\n Numero: %d\n votos: %d\n",
               contador, t->tamanho, t->itens[contador].numero, t->itens[contador].votos);

}

// ********************************* Termina hash aberto *********************************
void terminaHashAberto(hashAberto t){

    free(t->itens);
    free(t);

}
