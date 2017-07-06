#include "apuracao.h"

// Essa função recebe a tabela, processa os dados e aloca um vetor dinamico para computar os votos. Retorna o tamanho da tabela.
int apuraVotos(hashAberto t, int ranks, int **vet){

     // aloca um vetor dinamico para calcular os mais votados.
     int *chaves;
     int i, j, aux, quantidade = 0, contador;

     // Verifica a quantidade de candidatos diferentes.
     for(i = 0; i < t->tamanho; i++)
        if(t->itens[i].numero != 0)
           quantidade++;

    if(quantidade == 0){
         printf("\n ********** Apuracao **********\n\n Nao a dados\n\n");
         return 0;
    }

     // Aloca um vetor dinamico.
     chaves = (int*)malloc(quantidade * sizeof(int));

     // Zera todo o vetor dinamico
     for(i = 0; i < quantidade; i++)
        chaves[i] = 0;

     // Recebe todos os indices que possuem candidatos.
     for(i = 0, contador = 0; i < t->tamanho; i++)
        if(t->itens[i].numero != 0){
            chaves[contador] = i;
            contador++;
            }

     // Será armazenado neste vetor os indices os maiores votos.
     for (i = 0; i < quantidade; i++) {

         for (j = 0; j < quantidade; j++) {

             if (t->itens[chaves[i]].votos > t->itens[chaves[j]].votos) {

                 //aqui acontece a troca, do maior cara vaia para a direita e o menor para a esquerda
                 aux = chaves[i];
                 chaves[i] = chaves[j];
                 chaves[j] = aux;

               }

           }

      }

      // Se o tamanho do rank for maior que a quantidade de cadastrados
      if(ranks > quantidade)
        ranks = quantidade;

     printf("\n ********** Apuracao **********\n");
     for(i = 0; i < ranks; i++)
          printf("\n Candidato %d votos %d", t->itens[chaves[i]].numero, t->itens[chaves[i]].votos);

     printf("\n\n ********** **********\n");

     *vet = chaves;
     //free(chaves);
     return quantidade;
}

// Gera um arquivo com o ranking dos mais votados.
void finalizaVotacao(hashAberto presidente, hashAberto senador, char *estrutura){

     int contador, numero, votos, *apuracaoPresidente, *apuracaoSenador;
     // Recebe o arrays com a ordem da votação.
     int quantidadePresidente;
     int quantidadeSenador;

     FILE *arquivo;

     printf("\n\n\n\n\n\n******************** Apuracao final dos votos ********************\n\n\n\t   Presidente");
     quantidadePresidente = apuraVotos(presidente, presidente->tamanho, &apuracaoPresidente);
     printf("\n\n\t    Senador");
     quantidadeSenador = apuraVotos(senador, senador->tamanho, &apuracaoSenador);
     printf("\n\n Estrutura: %s\n Voto(s) no sistema: %d \n\n", estrutura, quantidadeDeVotosNoSistema(presidente, senador));

     arquivo = fopen("saida.txt", "w");

     // Se falhar ao abrir o arquivo, aborta o programa.
	 if (!arquivo){

		printf("\n ********** ERRO AO ABRIR O ARQUIVO **********\n\n");
		return;

	 }

     fprintf(arquivo, "%s", "********** Apuracao final dos votos **********\n\n");

     fprintf(arquivo, "%s %s %d", estrutura, "\nvoto(s) no sistema: ", quantidadeDeVotosNoSistema(presidente, senador));

     fprintf(arquivo, "%s", "\n\n***Presidente:\n");

     for(contador = 0; contador < quantidadePresidente; contador++){

         numero = presidente->itens[apuracaoPresidente[contador]].numero;
         votos = presidente->itens[apuracaoPresidente[contador]].votos;

        // Escrevendo no arquivo o ranking dos prefeitos.
        fprintf(arquivo, "%d %d %s", numero, votos, "voto(s).\n");

     }

     fprintf(arquivo, "%s", "\n***Senador:\n");

     for(contador = 0; contador < quantidadeSenador; contador++){

         numero = senador->itens[apuracaoSenador[contador]].numero;
         votos = senador->itens[apuracaoSenador[contador]].votos;

        // Escrevendo no arquivo o ranking dos prefeitos.
        fprintf(arquivo, "%d %d %s", numero, votos, "voto(s).\n");

     }


     fclose(arquivo);
     free(apuracaoPresidente);
     free(apuracaoSenador);

}
