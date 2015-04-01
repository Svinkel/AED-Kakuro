#include <stdlib.h>
#include <stdio.h>

#include "Item.h"
#include "list.h"
#include "tree.h"

/******************************************************************************
 * addElement()
 *
 * Arguments: L - lista
 *            i - nó da arvore
 *            n - combinaçao a ser testada
 *            q - primeiro e ultimo elemento da arvore
 * Returns: lista
 *
 * Description: Cria uma estrutura do tipo list onde coloca a combinação a ser
 *              testada, o nó da arvore onde vai ser colocada e altera o q.last
 *
 *****************************************************************************/

list* addElement(list *L,item i,int n, queue *q) {
    list *novo,*aux;

    novo = (list*) malloc(sizeof(list));
    if (novo==NULL) {
        printf("ERRO: Memoria não disponivel.\n");
        exit(-3);
    }
    novo->node=i;
    novo->n=n;
    novo->next=NULL;

    if (L==NULL) {
        L=novo;
        q->first=(item*)L;
        q->last=NULL;
    }else {
        aux=L;
        while(aux->next!=NULL) {
            aux=aux->next;
        }
        aux->next=novo;
        q->last=novo;
    }

    return L;
}

/******************************************************************************
 * checkInsert()
 *
 * Arguments: lista - lista com os valores inseridos na arvore
 *            q - primeiro e ultimo elemento da arvore
 * Returns: lista
 *
 * Description: Remove da lista o ultimo elemento e actualiza o q.last
 *
 *****************************************************************************/

list*   removeLastElement(list *L, queue *q) {
    list *aux,*auxAnt;

    if (L==NULL) return NULL;
    if (L->next==NULL) {
        free(L);
        q->first=NULL;
        return NULL;
    }else {
        aux=L;
        while(aux->next!=NULL) {
            auxAnt=aux;
            aux=aux->next;
        }
        q->last=auxAnt;
        auxAnt->next=NULL;
        /*free(aux->node);*/
        free(aux);
        return L;
    }

}
