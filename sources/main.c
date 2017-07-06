#include "arvoreAvl.h"
#include "arvoreBinaria.h"
#include "hashArvore.h"
#include "hashDuplo.h"
#include "hashAberto.h"
#include "apuracao.h"
#include "auxiliares.h"

int main() {

    tabelaHashArvore hashArvore;
	tabelaHashDuplo hashDuplo;
	hashAberto hashAbertoPresidente = NULL, hashAbertoSenador = NULL;
	avl arvoreAvl, aux;

	arvoreAvl = aux = NULL;

	FILE *arq;
	char *nome = "entrada2.txt";
	char in[MAX_STRING], op, estrutura, titulo[MAX_STRING];

	int numeroPresidente = 0, numeroSenadores = 0, numeroEleitores = 0;
	int classe, numero, rank, votou, *vet;
	cedula ced, *cel;

	// ************************** Abre o arquivo para leitura ************************
	arq = fopen(nome, "r");

	// Se falhar ao abrir o arquivo, aborta o programa.
	if (!arq) {

		printf("\n ********** ERRO AO ABRIR O ARQUIVO **********\n\n");
		return 0;

	}

	// ************************** Lendo as linhas do arquivo *************************

	// Verificando o modo, se é simulado ou competitivo.
	if (fgets(in, sizeof(in), arq) != NULL) {

		if (in[0] == '0' || in[0] == '1') {

			if (in[0] == '1'){
				modoCampeonato(&arq);
				fclose(arq);
				return 1;
			}

			else if(in[0] == '0'){

				// ********** Pegando o tipo de estrutura ***************
                // 1 tabela hash duplo
                // 2 tabela hash com arvore binaria
                // 3 Arvore avl
				if (fgets(in, sizeof(in), arq) != NULL) {

					estrutura = in[0];

					// Pegando o tamanho das tabelas e o número de eleitores.
					if (validaTamanhoTabelas(fgets(in, sizeof(in), arq), &numeroPresidente, &numeroSenadores,
						&numeroEleitores) != 1) {

						printf("\nErro ao pegar os tamanhos da tabela: %s\n", in);
						return 1;

					}

					// ************************************* Hash duplo *************************************************
					if (estrutura == '1') {

						hashDuplo = criaTabelaHashDuplo(numeroEleitores * 3);
						hashAbertoPresidente = criaHashAberto(numeroEleitores * 3);
						hashAbertoSenador = criaHashAberto(numeroEleitores * 3);

						if (hashDuplo == NULL || hashAbertoPresidente == NULL || hashAbertoSenador == NULL) {
							printf("\n\n Erro ao alocar hash duplo \n\n");
							return 1;
						}

						do {

							if ((fgets(in, sizeof(in), arq)) != NULL) {

								// Se retorna zero houve erro na string passada.
								if (leValidaString(in, &op, &classe, titulo, &numero, &rank) == 0) {

									printf("\n ********** ERRO DE ENTRADA **********\n\n");

									// Resetando os dados.
									op = -1;
									classe = -1;
									strcpy(titulo, " ");
									numero = -1;
									rank = -1;
									return 1;

								}

								if (op == '0') {

									// Verifica se é a inserção de presidente ou senador.
									if (classe == 0) {
										ced.presidente = numero;
										ced.senador = 0;
										strcpy(ced.titulo, titulo);

										if (insereTabelaHashDuplo(hashDuplo, ced) != 1)
											printf("\n %c %d %s %d voto nao computado\n", op, classe, titulo, numero);

										// Insere na tabela hash aberta do presidente
										else {
											if (insereHashAberto(hashAbertoPresidente, numero) == 1)
												printf("\n %c %d %s %d \n Voto computado, Candidato %d tem %d voto(s)\n",
													op, classe, titulo, numero,
													ced.presidente, quantidadeDeVotos(hashAbertoPresidente,
														numero));
											else {
												printf("\n\n Erro ao inserir: hash aberto \n\n");
												//system("pause");
											}
										}

										ced.presidente = 0;
										ced.senador = 0;
										strcpy(ced.titulo, "");


									}

									// Insere o senador.
									else if (classe == 1) {
										ced.presidente = 0;
										ced.senador = numero;
										strcpy(ced.titulo, titulo);

										if (insereTabelaHashDuplo(hashDuplo, ced) != 1)
											printf("\n %c %d %s %d voto nao computado\n", op, classe, titulo, numero);

										// Insere na tabela hash aberta do senador
										else {
											if (insereHashAberto(hashAbertoSenador, numero) == 1)
												printf("\n %c %d %s %d \n Voto computado, Candidato %d tem %d voto(s)\n",
													op, classe, titulo, numero,
													ced.senador, quantidadeDeVotos(hashAbertoSenador,
														numero));
											else {
												printf("\n\n Erro ao inserir: hash aberto \n\n");
												//system("pause");
											}

										}

										ced.presidente = 0;
										ced.senador = 0;
										strcpy(ced.titulo, "");

									}


								}

								// Se a opção for 1, então remova os votos do eleitor.
								else if (op == '1') {

									if (removeTabelaHashDuplo(hashDuplo, titulo, &ced) == 1) {

										removeHashAberto(hashAbertoPresidente, ced.presidente);
										removeHashAberto(hashAbertoSenador, ced.senador);

										printf("\n\n %s meliante removido, %d votos(s) validos no sistema \n\n",
											ced.titulo, quantidadeDeVotosNoSistema(hashAbertoPresidente, hashAbertoSenador));
									}
									else
										printf("\n\n %s meliante nao removido, %d votos(s) validos no sistema \n\n",
											ced.titulo, quantidadeDeVotosNoSistema(hashAbertoPresidente, hashAbertoSenador));

								}

								// Apura os votos
								else if (op == '2') {

									if (classe == 0)
										apuraVotos(hashAbertoPresidente, rank, &vet);

									else
										apuraVotos(hashAbertoSenador, rank, &vet);

									vet = NULL;

								}


							}

						} while (op != '3');

						finalizaVotacao(hashAbertoPresidente, hashAbertoSenador, "Hash Duplo");
						terminaHashDuplo(hashDuplo);

					}

					// ************************************* Hash arvore *************************************************
					if (estrutura == '2') {

						hashArvore = criaTabelaHashArvore(numeroEleitores * 3);
						hashAbertoPresidente = criaHashAberto(numeroEleitores * 3);
						hashAbertoSenador = criaHashAberto(numeroEleitores * 3);

						if (hashArvore == NULL) {
							printf("\n\n Erro ao alocar hash arvore \n\n");
							return 1;
						}

						do {

							if ((fgets(in, sizeof(in), arq)) != NULL) {

								// Se retorna zero houve erro na string passada.
								if (leValidaString(in, &op, &classe, titulo, &numero, &rank) == 0) {

									printf("\n ********** ERRO DE ENTRADA **********\n\n");

									// Resetando os dados.
									op = -1;
									classe = -1;
									strcpy(titulo, " ");
									numero = -1;
									rank = -1;
									return 1;

								}

								if (op == '0') {

									// Verifica se é a inserção de presidente ou senador.
									if (classe == 0) {
										ced.presidente = numero;
										ced.senador = 0;
										strcpy(ced.titulo, titulo);

										if (insereTabelaHashArvore(hashArvore, ced) != 1)
											printf("\n %c %d %s %d voto nao computado\n", op, classe, titulo, numero);

										// Insere na tabela hash aberta do presidente
										else {
											if (insereHashAberto(hashAbertoPresidente, numero) == 1)
												printf("\n %c %d %s %d \n Voto computado, Candidato %d tem %d voto(s)\n",
													op, classe, titulo, numero,
													ced.presidente, quantidadeDeVotos(hashAbertoPresidente,
														numero));
											else {
												printf("\n\n Erro ao inserir: hash aberto \n\n");
												//system("pause");
											}
										}

										ced.presidente = 0;
										ced.senador = 0;
										strcpy(ced.titulo, "");


									}

									// Insere o senador.
									else if (classe == 1) {
										ced.presidente = 0;
										ced.senador = numero;
										strcpy(ced.titulo, titulo);

										if (insereTabelaHashArvore(hashArvore, ced) != 1)
											printf("\n %c %d %s %d voto nao computado\n", op, classe, titulo, numero);

										// Insere na tabela hash aberta do presidente
										else {
											if (insereHashAberto(hashAbertoSenador, numero) == 1)
												printf("\n %c %d %s %d \n Voto computado, Candidato %d tem %d voto(s)\n",
													op, classe, titulo, numero,
													ced.senador, quantidadeDeVotos(hashAbertoSenador,
														numero));
											else {
												printf("\n\n Erro ao inserir: hash aberto \n\n");
												//system("pause");
											}
										}

										ced.presidente = 0;
										ced.senador = 0;
										strcpy(ced.titulo, "");

									}

								}

								// Se a opção for 1, então remova os votos do eleitor.
								else if (op == '1') {

									if (removeTabelaEleitorHashArvore(hashArvore, titulo, &ced) == 1) {
										removeHashAberto(hashAbertoPresidente, ced.presidente);
										removeHashAberto(hashAbertoSenador, ced.senador);

										printf("\n\n %s meliante removido, %d votos(s) validos no sistema \n\n",
											ced.titulo, quantidadeDeVotosNoSistema(hashAbertoPresidente, hashAbertoSenador));
									}
									else
										printf("\n\n %s meliante nao removido, %d votos(s) validos no sistema \n\n",
											ced.titulo, quantidadeDeVotosNoSistema(hashAbertoPresidente, hashAbertoSenador));

								}

								// Apura os votos
								else if (op == '2') {

									if (classe == 0)
										apuraVotos(hashAbertoPresidente, rank, &vet);

									else
										apuraVotos(hashAbertoSenador, rank, &vet);

									vet = NULL;

								}


							}

						} while (op != '3');

						finalizaVotacao(hashAbertoPresidente, hashAbertoSenador, "Hash Arvore");
						//terminaHashArvore(hashArvore);


					}

					// ************************************* Avore AVL *************************************************
					if (estrutura == '3') {

						hashAbertoPresidente = criaHashAberto(numeroEleitores + numeroPresidente);
						hashAbertoSenador = criaHashAberto(numeroEleitores + numeroSenadores);

						do {

							if ((fgets(in, sizeof(in), arq)) != NULL) {

								// Se retorna zero houve erro na string passada.
								if (leValidaString(in, &op, &classe, titulo, &numero, &rank) == 0) {

									printf("\n ********** ERRO DE ENTRADA **********\n\n");

									// Resetando os dados.
									op = -1;
									classe = -1;
									strcpy(titulo, " ");
									numero = -1;
									rank = -1;
									return 1;

								}

								if (op == '0') {

									// Verifica se é a inserção de presidente ou senador.
									if (classe == 0) {
										ced.presidente = numero;
										ced.senador = 0;
										strcpy(ced.titulo, titulo);

										votou = 1;
										votou = inserirAvl(&arvoreAvl, &aux, ced, &votou);
										if (votou != 1)
											printf("\n %c %d %s %d voto nao computado\n", op, classe, titulo, numero);

										// Insere na tabela hash aberta do presidente
										else {
											insereHashAberto(hashAbertoPresidente, numero);
											printf("\n %c %d %s %d \n Voto computado, Candidato %d tem %d voto(s)\n",
												op, classe, titulo, numero,
												ced.presidente, quantidadeDeVotos(hashAbertoPresidente,
													numero));
										}

										ced.presidente = 0;
										ced.senador = 0;
										strcpy(ced.titulo, "");


									}

									// Insere o senador.
									else if (classe == 1) {
										ced.presidente = 0;
										ced.senador = numero;
										strcpy(ced.titulo, titulo);

										votou = 1;
										votou = inserirAvl(&arvoreAvl, &aux, ced, &votou);
										if (votou != 1)
											printf("\n %c %d %s %d voto nao computado\n", op, classe, titulo, numero);

										// Insere na tabela hash aberta do presidente
										else {
											insereHashAberto(hashAbertoSenador, numero);
											printf("\n %c %d %s %d \n Voto computado, Candidato %d tem %d voto(s)\n",
												op, classe, titulo, numero,
												ced.senador, quantidadeDeVotos(hashAbertoSenador,
													numero));
										}

										ced.presidente = 0;
										ced.senador = 0;
										strcpy(ced.titulo, "");

									}

								}

								// Se a opção for 1, então remova os votos do eleitor.
								else if (op == '1') {

									cel = pesquisaElemento(arvoreAvl, titulo);
									if (cel != NULL) {
										removeHashAberto(hashAbertoPresidente, cel->presidente);
										removeHashAberto(hashAbertoSenador, cel->senador);

										avlRemove(&arvoreAvl, titulo);


										printf("\n\n %s meliante removido, %d votos(s) validos no sistema \n\n",
											ced.titulo, quantidadeDeVotosNoSistema(hashAbertoPresidente, hashAbertoSenador));
									}
									else
										printf("\n\n %s meliante nao removido, %d votos(s) validos no sistema \n\n",
											ced.titulo, quantidadeDeVotosNoSistema(hashAbertoPresidente, hashAbertoSenador));

								}

								// Apura os votos
								else if (op == '2') {

									if (classe == 0)
										apuraVotos(hashAbertoPresidente, rank, &vet);

									else
										apuraVotos(hashAbertoSenador, rank, &vet);

									vet = NULL;

								}
							}

						} while (op != '3');

						finalizaVotacao(hashAbertoPresidente, hashAbertoSenador, "Arvore avl");
						destruir(&arvoreAvl);

					}



				}

				else {
					printf("\nErro ao pegar o tipo da estrutura: %s\n", in);
					return 1;
				}


			}

            else {
                printf("\nErro no modo: %s\n", in);
                return 1;
            }


        }

        else {
                printf("\nErro no modo: %s\n", in);
                return 1;
            }

    }

	else
        printf("\nErro\n");


	fclose(arq);

	terminaHashAberto(hashAbertoPresidente);
	terminaHashAberto(hashAbertoSenador);
	return 1;
}
