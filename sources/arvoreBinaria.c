#include "arvoreBinaria.h"

// ************************************** Cria arvore **************************************

// Cria uma arvore binária de pesquisa.
void criarArvore(arvore *arv){
    *arv = NULL;
}

// ************************************** inserirArvore **************************************

// Cria uma arvore binária de pesquisa.
int inserirArvore(arvore *pRaiz, cedula inf, int *votou){

    if(*pRaiz == NULL){
        *pRaiz = (arvore) malloc(sizeof(arvoreBinaria));
        (*pRaiz)->esquerda = NULL;
        (*pRaiz)->direita = NULL;
        (*pRaiz)->info = inf;
    }else{
        if(strcmp(inf.titulo, (*pRaiz)->info.titulo) < 0)
            inserirArvore(&(*pRaiz)->esquerda, inf, votou);
        if(strcmp(inf.titulo, (*pRaiz)->info.titulo) > 0)
            inserirArvore(&(*pRaiz)->direita, inf, votou);

        // Verifica se esse eleitor já votou antes, caso, sim, não deixa
        if(strcmp(inf.titulo, (*pRaiz)->info.titulo) == 0){

            // Verifica se não votou pra presidente.
            if((*pRaiz)->info.presidente == 0 && inf.presidente != 0)
                (*pRaiz)->info.presidente = inf.presidente;

            // Verifica se não votou para senador.
            else if((*pRaiz)->info.senador == 0 && inf.senador != 0)
                (*pRaiz)->info.senador = inf.senador;

            else
                *votou = 0;

        }
    }

    return 1;
}

// ************************************** MaiorDireita **************************************

// Funções para remover um elemento da arvore.
arvore filhoDireita(arvore *no){

     if((*no)->direita != NULL)
       return filhoDireita(&(*no)->direita);

    else{

        arvore aux = *no;

        // Verifica se esse nó vai perder todos os seus filhos da esquerda
        if((*no)->esquerda != NULL)
          *no = (*no)->esquerda;

       else
          *no = NULL;

       return aux;
    }

}

// ************************************** MenorEsquerda **************************************

// Funções para remover um elemento da arvore.
arvore filhoEsquerda(arvore *no){

     if((*no)->esquerda != NULL)
       return filhoEsquerda(&(*no)->esquerda);

    else{

      arvore aux = *no;

       // Verifica se esse nó vai perder todos os seus filhos da direita.
       if((*no)->direita != NULL)
          *no = (*no)->direita;

       else
          *no = NULL;

       return aux;
    }

}

// ************************************** arvoreRemover **************************************

// Funções para remover um elemento da arvore.
void arvoreRemover(arvore *pRaiz, cedula inf, int *votou){

    if(*pRaiz == NULL){
       printf("Titulo nao existe na arvore!");
       return;
    }

    if(strcmp(inf.titulo, (*pRaiz)->info.titulo) < 0)
       arvoreRemover(&(*pRaiz)->esquerda, inf, votou);

    else
       if(strcmp(inf.titulo, (*pRaiz)->info.titulo) > 0)
          arvoreRemover(&(*pRaiz)->direita, inf, votou);

       // Posição que estamos procurando.
       else{
         arvore pAux = *pRaiz;
          if (((*pRaiz)->esquerda == NULL) && ((*pRaiz)->direita == NULL)){
                free(pAux);
                (*pRaiz) = NULL;
                *votou = 1;
               }

          // Filhos na direita.
          else{
             if ((*pRaiz)->esquerda == NULL){
                (*pRaiz) = (*pRaiz)->direita;
                pAux->direita = NULL;
                free(pAux); pAux = NULL;
                *votou = 1;
                }

            // Filhos na esquerda.
             else{
                if ((*pRaiz)->direita == NULL){
                    (*pRaiz) = (*pRaiz)->esquerda;
                    pAux->esquerda = NULL;
                    free(pAux); pAux = NULL;
                    *votou = 1;
                    }

                else{

                    // Faz o maior filho direito da subarvore esquerda.
                    pAux = filhoDireita(&(*pRaiz)->esquerda);
                    pAux->esquerda = (*pRaiz)->esquerda;
                    pAux->direita = (*pRaiz)->direita;
                    (*pRaiz)->esquerda = (*pRaiz)->direita = NULL;
                    free((*pRaiz));  *pRaiz = pAux;  pAux = NULL;
                    *votou = 1;

                   }
                }
             }
          }
}

// ************************************** imprimeArvore **************************************

void imprimeArvore(arvore pRaiz){

    if(pRaiz != NULL){
        imprimeArvore(pRaiz->esquerda);
        printf("-%s-", pRaiz->info.titulo);
        imprimeArvore(pRaiz->direita);
    }

}

// ************************************** contarNos **************************************

int contarNos(arvore pRaiz){

    if(pRaiz == NULL)
        return 0;
   else{
        printf("\n\n nos: %s\n\n", pRaiz->info.titulo);
        return 1 + contarNos(pRaiz->esquerda) + contarNos(pRaiz->direita);
   }
}

// ************************************** contarFolhas **************************************

int contarFolhas(arvore pRaiz){

    if(pRaiz == NULL)
        return 0;
   if(pRaiz->esquerda == NULL && pRaiz->direita == NULL)
        return 1;
   return contarFolhas(pRaiz->esquerda) + contarFolhas(pRaiz->direita);

}

// ************************************** maior **************************************

// Tamanho da arvore.
int maior(int a, int b){

    if(a > b)
        return a;
    else
        return b;

}


// ************************************** altura **************************************

int altura(arvore pRaiz){

    if((pRaiz == NULL) || (pRaiz->esquerda == NULL && pRaiz->direita == NULL))
       return 0;
   else
       return 1 + maior(altura(pRaiz->esquerda), altura(pRaiz->direita));

}

// ************************************** pesquisaElementoBinaria **************************************

cedula *pesquisaElementoBinaria(arvore r, char *titulo){

     cedula *achou;

     if (r == NULL)
        return NULL;

     if (strcmp(r->info.titulo, titulo) == 0)
            return &r->info;

     achou = pesquisaElementoBinaria(r->esquerda, titulo);

     if (achou == NULL)
         achou = pesquisaElementoBinaria(r->direita, titulo);

     return achou;
}

/* **************************** TREE *****************************/
tree criaTree(){

    tree r;

    r = (tree)malloc(sizeof(arv));

    if(r != NULL){
        r->root = NULL;
        r->nos = 0;
        return r;
    }

    return NULL;

}

// ************************************** insereTree **************************************

int insereTree(tree r, cedula inf){

    int votou = 1;

    inserirArvore(&r->root, inf, &votou);

    if(votou == 1){
        r->nos++;
        return 1;
    }

    return 0;

}

// ************************************** removeTree **************************************

int removeTree(tree r, cedula ced){

    int votou = 0;
    arvoreRemover(&r->root, ced, &votou);

    if(votou == 1){
        r->nos--;
        return 1;
    }

    return 0;

}

// ************************************** pesquisaTree **************************************

cedula *pesquisaTree(tree r, char *titulo){

    cedula *ced;
    ced = pesquisaElementoBinaria(r->root, titulo);

    if(ced == NULL)
        return NULL;

    return ced;
    //printf("\n\n dditen remove: %s\n\n", ced->titulo);
}

// ************************************** imprimeTree **************************************

void imprimeTree(tree r){

    imprimeArvore(r->root);

}
