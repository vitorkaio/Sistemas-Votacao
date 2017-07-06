#include "auxiliares.h"

// ***************************** Pega o tamanho m�ximo das tabelas *****************************
int validaTamanhoTabelas(char *str, int *presidentes, int *senadores, int *eleitores) {

	char aux[20], numero[20];
	int contador, n, x;
	strcpy(aux, str);

	// Verifica se chegou ao final.
	if (aux[0] == '\n')
		return 0;

	// Pega o primeiro elemento.
	for (contador = 0; aux[contador] != ' ' && aux[contador] != '\n'; contador++)
		numero[contador] = aux[contador];

	n = atoi(numero);
	if (n == 0)
		return 0;

	*presidentes = n;
	memset(numero, 0, sizeof(numero));

	// Verifica se chegou ao final.
	if (aux[contador] == '\n')
		return 0;

	contador++;

	// Pega o segundo elemento.
	for (x = 0; aux[contador] != ' ' && aux[contador] != '\n'; contador++, x++)
		numero[x] = aux[contador];

	n = atoi(numero);
	if (n == 0)
		return 0;

	*senadores = n;
	memset(numero, 0, sizeof(numero));

	// Verifica se chegou ao final.
	if (aux[contador] == '\n')
		return 0;

	contador++;

	// Pega o terceiro elemento.
	for (x = 0; aux[contador] != ' ' && aux[contador] != '\n'; contador++, x++)
		numero[x] = aux[contador];

	n = atoi(numero);
	if (n == 0)
		return 0;

	*eleitores = n;

	return 1;

}

// ***************************** Valida a entrada de dados *************************************
/* Valida a string vinda do arquivo e a quebra:

   opcao -> op na chamada.
   cla -> Classe na chamada.
   str -> string contendo as entradas.
   t -> titulo na chamada.
   n -> numero na chamada.
   ran -> rank na chamada.

*/
int leValidaString(char *str, char *opcao, int *cla, char *t, int *n, int *ran) {

	char entrada[50], titulo[MAX + 2], numero[MAX + 2], r[MAX];
	int numeroCandidato, contador, i, j, classeNum, rank;
	char op, classe[2];

	strcpy(entrada, str);
	op = entrada[0];

	// Verifica se � a posi��o 3, se sim sai do programa.
	if (entrada[0] == '3') {

		*opcao = '3';
		return 1;

	}

	// Obriga a ter um espa�o vazio entre a op��o e o resto.
	if (entrada[1] != ' ')
		return 0;

	// Pega os campos relacionados ao voto.
	if (op == '0') {

		classe[1] = '\0';
		classe[0] = entrada[2];

		if (classe[0] != '0' && classe[0] != '1')
			return 0;

		classeNum = atoi(classe);

		// Obriga um campo vazio na posicai 3.
		if (entrada[3] != ' ')
			return 0;

		// Pega toda a substring relacionada ao titulo da string entrada.
		for (contador = 4, i = 0; entrada[contador] != '\n' && entrada[contador] != ' '; contador++, i++)
			titulo[i] = entrada[contador];

		// Coloca o quebra de linha e o terminador nulo no final da string.
		titulo[i] = '\0';

		// Verifica se o titulo tem mais de 8 digitos, se sim retorna 0.
		if (strlen(titulo) > 8)
			return 0;

		// Verifica se existe alguma coisa escrita ap�s o titulo.
		if (entrada[contador] == '\n')
			return 0;

		// Pega toda a substring relacionada ao n�mero da string entrada.
		for (j = contador + 1, i = 0; entrada[j] != '\n' && entrada[j] != ' '; j++, i++)
			numero[i] = entrada[j];

		// Coloca o quebra de linha e o terminador nulo no final da string.
		numero[i] = '\0';

		// Verifica se o numero tem mais de 8 digitos, se sim retorna 0.
		if (strlen(numero) > 8)
			return 0;

		// Verifica se existe alguma coisa depois do numero, se sim , retorna zero.
		if (entrada[j] == ' ')
			return 0;

		// Converte a string em um numero.
		numeroCandidato = atoi(numero);

		if (numeroCandidato == 0)
			return 0;

		*opcao = op;
		*cla = classeNum;
		strcpy(t, titulo);
		*n = numeroCandidato;

		return 1;

	}

	else if (op == '1') {

		// Pega toda a substring relacionada ao titulo da string entrada.
		for (contador = 2, i = 0; entrada[contador] != '\n' && entrada[contador] != ' ' && entrada[contador] != '\r'; contador++, i++)
			titulo[i] = entrada[contador];

		// Verifica se existe alguma coisa depois do numero, se sim , retorna zero.
		if (entrada[contador] == ' ')
			return 0;

		// Coloca o quebra de linha e o terminador nulo no final da string.
		titulo[i] = '\0';

		// Verifica se o titulo tem mais de 8 digitos, se sim retorna 0.
		if (strlen(titulo) > 8)
			return 0;

		*opcao = op;
		strcpy(t, titulo);

		return 1;

	}

	else if (op == '2') {

		r[0] = '0';

		classe[0] = '0';
		classe[1] = entrada[2];

		if (classe[1] != '0' && classe[1] != '1')
			return 0;

		classeNum = atoi(classe);

		for (contador = 4, i = 1; entrada[contador] != '\n' && entrada[contador] != ' '; contador++, i++)
			r[i] = entrada[contador];

		r[i] = '\0';

		if (entrada[contador] == ' ')
			return 0;

		// Verifica se existe espa�o entre a op��o e a classe
		if (entrada[1] != ' ')
			return 0;

		// Verifica se existe espa�o entre a classe e o ranking.
		if (entrada[3] != ' ')
			return 0;

		rank = atoi(r);

		if (rank == 0)
			return 0;

		*opcao = op;
		*cla = classeNum;
		*ran = rank;

		return 1;

	}

	return 0;

}


// ***************************** Modo Campeonato *************************************
void modoCampeonato(FILE **arq) {

	tabelaHashLista hashLista = NULL;
	hashAberto hashAbertoPresidente = NULL, hashAbertoSenador = NULL;

	char in[MAX_STRING], op, titulo[MAX_STRING];

	int numeroPresidente = 0, numeroSenadores = 0, numeroEleitores = 0;
	int classe, numero, rank, *vet;
	cedula ced;

	if (fgets(in, sizeof(in), *arq) != NULL) {

		// Pegando o tamanho das tabelas e o número de eleitores.
		if (validaTamanhoTabelas(fgets(in, sizeof(in), *arq), &numeroPresidente, &numeroSenadores,
			&numeroEleitores) != 1) {
			printf("\nErro ao pegar os tamanhos da tabela: %s\n", in);
			return;

		}

		else {

			hashLista = criaTabelaHashLista(numeroEleitores * 3);
			hashAbertoPresidente = criaHashAberto(numeroEleitores * 3);
			hashAbertoSenador = criaHashAberto(numeroEleitores * 3);

			if (hashLista == NULL || hashAbertoPresidente == NULL || hashAbertoSenador == NULL) {
				printf("\n\n Erro ao alocar hash duplo \n\n");
				return;
			}

			do {

				if ((fgets(in, sizeof(in), *arq)) != NULL) {

					// Se retorna zero houve erro na string passada.
					if (leValidaString(in, &op, &classe, titulo, &numero, &rank) == 0) {

						printf("\n ********** ERRO DE ENTRADA **********\n\n");

						// Resetando os dados.
						op = -1;
						classe = -1;
						strcpy(titulo, " ");
						numero = -1;
						rank = -1;
						return;

					}

					if (op == '0') {

						// Verifica se � a inser��o de presidente ou senador.
						if (classe == 0) {
							ced.presidente = numero;
							ced.senador = 0;
							strcpy(ced.titulo, titulo);

							if (insereTabelaEleitoresHashLista(hashLista, ced) != 1)
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

							if (insereTabelaEleitoresHashLista(hashLista, ced) != 1)
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

					// Se a op��o for 1, ent�o remova os votos do eleitor.
					else if (op == '1') {

						if (removeTabelaEleitorHashLista(hashLista, titulo, &ced) == 1) {

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

		}


	}

	else {
            printf("\nErro ao pegar o tipo da estrutura: %s\n", in);
            return ;
        }


	finalizaVotacao(hashAbertoPresidente, hashAbertoSenador, "Hash Lista");
	//terminaTabelaHashLista(hashLista);
	terminaHashAberto(hashAbertoPresidente);
	terminaHashAberto(hashAbertoSenador);

}
