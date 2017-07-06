#include "lista_encadeada.h"

lista cria_lista(){

	lista l = (lista)malloc(sizeof(tipo_lista));

	if (l){

		l->primeiro = NULL;
		l->ultimo = NULL;
		l->tamanho = 0;

	}

	return l;
}

int insere_lista(lista l, cedula inf){

	tnodo p;
	p = l->primeiro;

	while (p){

        // Verifica se esse eleitor já votou antes, caso, sim, não deixa
        if(strcmp(inf.titulo, p->cedula.titulo) == 0){

            // Verifica se não votou pra presidente.
            if(p->cedula.presidente == 0 && inf.presidente != 0){
                p->cedula.presidente = inf.presidente;
                return 1;
            }

            // Verifica se não votou para senador.
            else if(p->cedula.senador == 0 && inf.senador != 0){
                p->cedula.senador = inf.senador;
                return 1;
            }

            else
                break;

        }

		p = p->prox;

	}
	if (!p){
		p = (tnodo)malloc(sizeof(tipo_nodo));
		p->cedula = inf;
		p->prox = NULL;
		if (!l->primeiro)
			l->primeiro = p;
		else
			l->ultimo->prox = p;
		l->ultimo = p;
		l->tamanho++;
		return 1;
	}
	return 0;

}
int remove_lista(lista l, char *string, cedula *e){
	tnodo p = NULL, ant = NULL;
	p = l->primeiro;

	while (p){
		if (!strcmp(string, p->cedula.titulo))
			break;
		else{
			ant = p;
			p = p->prox;
		}
	}
	if (p){
		if (l->primeiro == p)
			l->primeiro = p->prox;
		else
		if (l->ultimo == p){
			l->ultimo = ant;
			ant->prox = NULL;
		}
		else
			ant->prox = p->prox;

		*e = p->cedula;
		free(p);
		l->tamanho--;
		return 1;
	}
	return 0;
}

// Pesquisa quantos cédulas um candidato recebeu.
int pesquisa_lista(lista l, int numeroCandidato, cedula *e){
	tnodo p;
	int contador = 0;
	p = l->primeiro;

	if (!p)
		return 0;

	while (p){
		if (numeroCandidato == p->cedula.presidente){
			contador++;
			*e = p->cedula;
			p = p->prox;
		}
		else
			p = p->prox;

	}

	return contador;
}

// Pesquisa se uma candidato já votou. Passa a lista, cedula nova.
/*int pesquisaVotoEleitores_lista(lista l, cedula cedula){

tnodo p;
	p = l->primeiro;
	while (p){
		if (!strcmp(cedula.titulo, p->cedula.titulo) && (cedula.classeCandidadato == p->cedula.classeCandidadato))
			return 0;
		else
			p = p->prox;

	}

	return 1;
}*/

void termina_lista(lista l){
	tnodo p;
	p = l->primeiro;
	while (p){
		p = l->primeiro;
		l->primeiro = p->prox;
		free(p);
	}
	l->tamanho = 0;
}
