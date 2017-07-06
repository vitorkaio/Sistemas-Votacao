#include "hashLista.h"

// Cria a tabela hash.
tabelaHashLista criaTabelaHashLista(int tamanho){

	int m = tamanho; /**************/
	//m = 201;
	int contador = 0;

	// Alocando uma tabela de m posições.
	tipoTabela *table = (tipoTabela *)malloc(sizeof(tipoTabela));

	if (table != NULL){

		// Aloca um vetor de ponteiros para uma lista.
		table->itens = (lista)malloc(m * sizeof(tipo_lista));

		if (table->itens != NULL){

			for (contador = 0; contador < m; contador++){

				//table->itens[contador] = (lista)malloc(sizeof(tipo_lista));
				table->itens[contador].primeiro = NULL;
				table->itens[contador].ultimo = NULL;
				table->itens[contador].tamanho = 0;

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

/* ********************************* Calcula o indice na tabela ********************************* */

// Calcula o indice para a tabela através do número do eleitor.
int hashListaIndiceCandidato(tabelaHashLista tabela, int numeroCandidato){

	 // Retorna o indice da tabela.
	 return numeroCandidato % tabela->M;

}// Fim hash

/* ********************************* Calcula indice para tabela de eleitores ********************************* */

// Calcula um indice para a tabela de eleitores.
int hashListaIndiceEleitores(tabelaHashLista tabela, char *s){

     int i;
     int total = 0;

     // Soma o código ascii dos caracteres e depois divide pelo módulo para calcular um indice.
     for (i=0; s[i]!='\0'; i++)
        total += s[i];

    return total % tabela->M;

}// Fim do hash

/* ********************************* Insere Tabela Hash Lista ********************************* */

// Insere uma cédula na tabela.
int insereTabelaHashLista(tabelaHashLista t, cedula cedula){

	// Recebe o indice da a tabela.
	int indice = hashListaIndiceEleitores(t, cedula.titulo);

	// Insere uma cédula na lista.
	if (insere_lista(&t->itens[indice], cedula))
		return 1;

	return 0;

}// Fim insereTabelaHashLista

/* ********************************* Insere Tabela de Eleitores Hash Lista ********************************* */

// Insere uma cédula na tabela de eleitores.
int insereTabelaEleitoresHashLista(tabelaHashLista t, cedula cedula){

    // Recebe o indice da a tabela.
	int indice = hashListaIndiceEleitores(t, cedula.titulo);

	// Insere uma cédula na lista.
	if (insere_lista(&t->itens[indice], cedula))
		return 1;

	return 0;

}// Fim insereTabelaEleitoresHashLista.

/* ********************************* Remove Tabela Hash Lista ********************************* */

// Remove uma cédula da tabela. Passa a tabela, o titulo e o número do candidato que deseja excluir e a cedula para armazenar.
int removeTabelaHashLista(tabelaHashLista t, char *titulo, int numeroCandidato, cedula *copia){

	// Recebe o indice da a tabela.
	int indice = hashListaIndiceEleitores(t, titulo);

	if (remove_lista(&t->itens[indice], titulo, copia))
		return 1;

	return 0;

}// Fim removeTabelaHashLista.

/* ********************************* Pesquisa Tabela Hash Lista ********************************* */

// Pesquisa a quantidade de cedulas um candidato recebeu. Passa a tabela e o número do candidato.
/*int pesquisaTabelaHashLista(tabelaHashLista t, int numeroCandidato, cedula *copia){

	// Recebe o indice da a tabela.
	int indice = hashIndiceCandidato(t, numeroCandidato);
	int contador = pesquisa_lista(&t->itens[indice], numeroCandidato, copia);

	if (contador == 0)
		return 0;

	return contador;

}// Fim pesquisaTabelaHashLista.*/

/* ********************************* Pesquisa Repetição de voto ********************************* */

// Verifica se um eleitor já votou em alguma candidato.
/*int pesquisaRepeticaoDeVoto(tabelaHashLista t, cedula cedula){

    // Recebe o indice da a tabela.
	int indice = hashIndiceEleitores(t, cedula.titulo);
	int verifica;

	// Se verifica receber 1, está cedula pode ser computada normalmente.
	verifica = pesquisaVotoEleitores_lista(&t->itens[indice], cedula);

	if(verifica == 1)
        return 1;

    return 0;

}// Fim pesquisaRepeticaoDeVoto.*/

/* ********************************* Remove Eleitor ********************************* */

// Remove votos de um eleitor.
int removeTabelaEleitorHashLista(tabelaHashLista t, char *titulo, cedula *e){

   int indice = hashListaIndiceEleitores(t, titulo);

	if (remove_lista(&t->itens[indice], titulo, e))
		return 1;

	return 0;


}

/* ********************************* Termina Tabela Hash Lista ********************************* */

// Finaliza a tabela.
void terminaTabelaHashLista(tabelaHashLista t){

	int i;

	for (i = 0; i < t->M; i++)
        if(t->itens[i].primeiro != NULL)
		termina_lista(&t->itens[i]);

	free(t->itens);
	free(t);

}// Fim terminaTabelaHashLista.
