#include "arvoreAvl.h"

int avl_height (avl node){

    /*retorna a altura da arvore*/

    int esq, dir;

    if ( node == NULL )
        return -1;

    esq = avl_height ( node->esq );
    dir = avl_height ( node->dir );

    if ( esq > dir )
        return esq + 1;
    else
        return dir + 1;

}

avl rotacaoLL(avl p){

    avl q;

    q = p->esq;
    //----------------> Realiza a rotação
    p->esq = q->dir;

    if ( q->dir != NULL )
        q->dir->pai = p;

    q->dir = p;
    q->pai = p->pai;

    if ( p->pai != NULL ){

        if ( p->pai->esq == p )
            p->pai->esq = q;

        else
            p->pai->dir = q;

    }

    p->pai = q;

    //----------------> Rebalanceia
    q->bal = avl_height ( q->esq ) - avl_height ( q->dir );
    p->bal = avl_height ( p->esq ) - avl_height ( p->dir );

    return q;

}


avl rotacaoRR (avl p){

    avl q;

    q = p->dir;
    //----------------> Realiza a rotação
    p->dir = q->esq;

    if ( q->esq != NULL )
        q->esq->pai = p;

    q->esq = p;
    q->pai = p->pai;

    if ( p->pai != NULL ){

        if ( p->pai->esq == p )
            p->pai->esq = q;

        else
            p->pai->dir = q;
    }

    p->pai = q;

    //----------------> Rebalanceia
    q->bal = avl_height ( q->esq ) - avl_height ( q->dir );
    p->bal = avl_height ( p->esq ) - avl_height ( p->dir );

    return q;

}


void avlRemove(avl *node, char *info){

    char aux[15];
    avl P;

    /*se se o elemento nao esta na arvore sai da funçao*/
    if (*node == NULL)
        return ;

    if (strcmp(info, (*node)->info.titulo) < 0){

        /*se remove da esquerda é como inserir na direita*/
        avlRemove( &((*node)->esq), info);
        (*node)->bal = avl_height ( (*node)->esq ) - avl_height ( (*node)->dir );

        if((*node)->bal==-2){

            if( (*node)->dir->bal!=1){
                (*node)= rotacaoRR ( (*node) );
            }

            else if(  (*node)->dir->bal==1){

                (*node)->dir=rotacaoLL ( (*node)->dir);
                (*node)= rotacaoRR ( (*node) );

            }
        }

    }

    else{

        if (strcmp(info, (*node)->info.titulo) > 0) {

            /*se remove da direita é como inserir na esquerda*/
            avlRemove( &((*node)->dir), info );
            (*node)->bal = avl_height ( (*node)->esq ) - avl_height ( (*node)->dir );

            if((*node)->bal==2){

                if( (*node)->esq->bal!=-1){
                    (*node)= rotacaoLL ( (*node) );
                }

                else if( (*node)->esq->bal==-1){

                    (*node)->esq =rotacaoRR ( (*node)->esq );
                    (*node)=  rotacaoLL ( (*node) );

                }
            }

        }

        else{

            /*se achou a informaçao na folha ela remove*/
            if (strcmp(info, (*node)->info.titulo) == 0) {

                if (((*node)->esq == NULL) && ((*node)->dir == NULL)){

                    free (*node);
                    *node = NULL;

                }

                else{

                    /*se tive so filho direito ou lado direito mais alto troca com menor valor a direita ate chegar a folha  remover do lado mais alto é muito importante */
                    if ( ((*node)->esq==NULL&&(*node)->dir!=NULL)||(*node)->bal==-1){

                        P=(*node)->dir;
                        while(P->esq!=NULL)
                            P=P->esq;

                        strcpy(aux, P->info.titulo);
                        avlRemove( &((*node)), P->info.titulo );
                        strcpy((*node)->info.titulo, aux);

                    }

                    else{

                        /*se tiver so filho esquerdo ou os 2 filhos troca com menor valor a esquerda ate chegar a folha */
                        P=(*node)->esq;
                        while(P->dir!=NULL)
                            P=P->dir;

                       // printf("\n\n-->%s\n\n", info);
                        strcpy(aux, P->info.titulo);
                        avlRemove( &((*node)), P->info.titulo );
                        strcpy((*node)->info.titulo, aux);

                    }

                }
            }
        }
    }
}


int inserirAvl(avl *pRaiz, avl *PAI, cedula inf, int *votou){

    if(*pRaiz == NULL){

        *pRaiz = (avl)malloc(sizeof(arvoreAvl));
        (*pRaiz)->esq = NULL;
        (*pRaiz)->dir = NULL;
        (*pRaiz)->info = inf;
        (*pRaiz)->pai=(*PAI);
        (*pRaiz)->bal=0;

    }


    else{
//printf("\n\n -> title: %s || No: %s\n\n", inf.titulo, (*pRaiz)->info.titulo);
        if(strcmp(inf.titulo, (*pRaiz)->info.titulo) < 0){

            *votou = inserirAvl(& (*pRaiz)->esq,&(*pRaiz), inf, votou);
            (*pRaiz)->bal=avl_height ( (*pRaiz)->esq ) - avl_height ( (*pRaiz)->dir );

            if( (*pRaiz)->bal==2){

                if(  (*pRaiz)->esq->bal==1)
                    (*pRaiz)= rotacaoLL ( (*pRaiz) );

                else if(  (*pRaiz)->esq->bal==-1){

                    (*pRaiz)->esq =rotacaoRR ( (*pRaiz)->esq );
                    (*pRaiz)=  rotacaoLL ( (*pRaiz) );

                }
            }

        }

        else if(strcmp(inf.titulo, (*pRaiz)->info.titulo) > 0){

                *votou = inserirAvl(& (*pRaiz)->dir,&(*pRaiz), inf, votou);
                (*pRaiz)->bal=avl_height ( (*pRaiz)->esq ) - avl_height ( (*pRaiz)->dir );

                if( (*pRaiz)->bal==-2){

                    if(  (*pRaiz)->dir->bal==-1)
                        (*pRaiz)= rotacaoRR ( (*pRaiz) );

                    else if(  (*pRaiz)->dir->bal==1){

                        (*pRaiz)->dir=rotacaoLL ( (*pRaiz)->dir);
                        (*pRaiz)= rotacaoRR ( (*pRaiz) );

                    }
                }
        }

        // Verifica se esse eleitor já votou antes, caso, sim, não deixa
        else if(strcmp(inf.titulo, (*pRaiz)->info.titulo) == 0){


            // Verifica se não votou pra presidente.
            if((*pRaiz)->info.presidente == 0 && inf.presidente != 0)
                (*pRaiz)->info.presidente = inf.presidente;


            // Verifica se não votou para senador.
            else if((*pRaiz)->info.senador == 0 && inf.senador != 0)
                (*pRaiz)->info.senador = inf.senador;


            else
                *votou = 0;



        }

        else
            *votou = 0;

    }

    //printf("\n\n ------->%d \n\n", *votou);
    if(*votou == 0)
        return 0;

    return 1;
}


void imprimeAvl(avl r){

    if (r != NULL) {
        imprimeAvl(r->esq);
        printf("%s(%d)", r->info.titulo, r->bal);
        imprimeAvl(r->dir);
    }

}

void destruir(avl *Tree){

    if ((*Tree)!=NULL){

        destruir(&(*Tree)->dir);

        destruir(&(*Tree)->esq);
        free((*Tree));
        (*Tree)=NULL;
    }
}


cedula *pesquisaElemento(avl r, char *titulo){

     cedula *achou;

     if (r == NULL)
        return NULL;

     if (strcmp(r->info.titulo, titulo) == 0)
            return &r->info;

     achou = pesquisaElemento(r->esq, titulo);

     if (achou == NULL)
         achou = pesquisaElemento(r->dir, titulo);

     return achou;
}

