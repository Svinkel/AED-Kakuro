#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "puzzle.h"
#include "utils.h"
#include "list.h"

int fail=0;

/******************************************************************************
 * createTree()
 *
 * Arguments: mat - matriz com o jogo
 *            crd - coordenada para a próxima célula vazia
 *            lista - lista com os valores inseridos na arvore
 *            q - primeiro e ultimo elemento da arvore
 *
 * Returns: Arvore
 *
 * Description: Dado um vector com o valor da soma superior e inferior, numero
 *            celulas e a coluna/linha em que esta, é verificado se o valor
 *            da combinação que se quer inserir na arvore é valido (CheckInsert)
 *              Se o valor for valido é chamada a funçao que cria um novo filho
 *            à arvore ja criada
 *              Dada a soma superior e inferior, o programa intersecta as duas
 *              combinaçoes e retorna a combinaçao em comum
 *
 *****************************************************************************/

tree* createTree(coord crd, list* lista,puzzle **mat,queue *q) {;
  tree *nova=NULL;
  int i,insertflag=0;
  static int final=0;
  int *comb;
  int *vecSoma;

    if(crd.x==-1) {
        final=1;
        return NULL;
    }

    nova=(tree*) malloc(sizeof(tree));
    if (nova==NULL) {
        printf("ERRO: Memoria não disponivel.\n");
        exit(-3);
    }
    nova->crd=crd;

    /* Vector com a soma superior, inferior bem como o numero de quadrados */
    vecSoma = verifica_soma_coordenada(mat, crd);

    /* Inicialização do vector point [] */
    for(i=0;i<9;i++) nova->point[i]=NULL;

    comb=mat[crd.y][crd.x].valor;

    for(i=0;  (comb[i] != 0 && final==0); i++) {
    /* Se for -1 tava-se de número eliminado */
        if(comb[i] != -1){
    /* Adiciona a combinação a ser testa na lista */
            lista=addElement(lista,(item*)nova,comb[i],q);
    /* Se esta condiçao se verificar é possivel inserir na arvore */
            if ( checkInsert(comb[i], crd,mat,q,lista, vecSoma)==1 ) {
                nova->point[i]=createTree(nextCoord(crd,mat), lista, mat,q);
                 if (nova->point[i]!=NULL) insertflag=1;
            }else{
    /* Caso contrário coloca o filho a NULL */
                nova->point[i]= NULL;
            }
    /* Caso nao tenha sido possivel inserir o elemento adicionado à lista é removido */
            if (final==0) lista=removeLastElement(lista,q);
        }
    }
    free(vecSoma);
    /* Se a lista for NULL é porque todos os elementos foram removidos logo nenhum verificava
      as condiçoes do puzzle*/
    if(lista==NULL) printf("Sem solução\n");
    /* Retorna a arvore com a soluçao do puzzle */
    if (insertflag==1 || final==1) return nova;
    else {
        free(nova);
        return NULL;
    }
}

/******************************************************************************
 * checkInsert()
 *
 * Arguments: n - combinação a ser testada
 *            c - coordenada para a próxima célula vazia
 *            mat - matriz com o puzzle
 *            lista - lista com os valores inseridos na arvore
 *            q - primeiro e ultimo elemento da arvore
 *            vecSoma - vector com as somas e o numero de quadrados
 *
 * Returns: 1 se verdadeiro, -1 se falso
 *
 * Description: Dada uma combinação esta funçao testa se é possivel continuar
 *              a inserir na arvore com base nos numeros que ja foram preenchidos
 *
 *****************************************************************************/

int checkInsert(int n, coord c, puzzle **mat,queue *q,list *lista,int* vecSoma){
    int somaX,somaY,sqX,sqY;
    list *aux;
    coord listcrd;

    if (q->last==NULL ){
        return 1;
    }else{
        aux= (list*) lista;
    }

    somaX=somaY=sqX=sqY=0;

    while ( aux!=q->last ) {
        listcrd=((tree*)aux->node)->crd;
        /* Verifica se estao na mesma coluna */
        if ( listcrd.x==c.x && (vecSoma[2]+vecSoma[1])>=listcrd.y && listcrd.y>=vecSoma[2]) {
        /* Se o valor na lista é igual ao que a funçao recebe significa que se está a tentar
           testar com um valor que ja se encontra no puzzle */
            if (aux->n == n) {
                return (-1);
            } else {
        /* Soma o valor que se esta a testar com os que estão na lista */
                somaY+=aux->n;
                sqY++;
            }
        }
        /* Verifica se estao na mesma linha*/
        if ( listcrd.y==c.y && (vecSoma[5]+vecSoma[4])>=listcrd.x && listcrd.x>=vecSoma[5]) {
        /* Se o valor na lista é igual ao que a funçao recebe significa que se está a tentar
           testar com um valor que ja se encontra no puzzle */
            if (aux->n == n) {
                return (-1);
            } else {
         /* Soma o valor que se esta a testar com os que estão na lista */
                somaX+=aux->n;
                sqX++;
            }
        }
        aux=aux->next;
    }

    if(vecSoma[4]==sqX+1) {
    /* Se so fazer preeencher um quadrado e a soma dos elementos testados for diferente da
        indicada no puzzle retorna -1 */
        if(vecSoma[3]!=somaX+n) {
            return (-1);
        }
    } else {

        if(vecSoma[3]<somaX+n) {
            return (-1);
        }
    }


    if(vecSoma[1]==sqY+1) {
    /* Se so fazer preeencher um quadrado e a soma dos elementos testados for diferente da
        indicada no puzzle retorna -1 */
        if(vecSoma[0]!=somaY+n) {
            return (-1);
        }
    } else {
        if(vecSoma[0]<somaY+n) {
            return (-1);
        }
    }
    /* Numero testado é possivel */
    return 1;
}

/******************************************************************************
 * imprime_puzzle()
 *
 * Arguments: lista - lista com a soluçao do puzzle
 *            fp - ponteiro para o ficheiro de output
 * Returns:
 *
 * Description: Imprime a solução analisando a arvore. Acede às coordenadas que
 *              estao na arvore e imprime o valor final consoante as coordenadas
 *
 *****************************************************************************/

tree* imprime_puzzle(list *lista, FILE* fp){

    int i,j;
    list* fr;
    list* aux=lista;


    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            if(aux!=NULL){
                if((((tree*)aux->node)->crd.x)==j && (((tree*)aux->node)->crd.y)==i){
                    printf(" %d ",aux->n);
                    fprintf(fp,"%d",aux->n);
                    fr=aux;
                    aux=aux->next;
                    free(fr->node);
                    free(fr);
                }else{
                    printf("---");
                    fprintf(fp,"-");
                }
            } else {
                printf("---");
                fprintf(fp,"-");
            }
            printf("||");
            if(j<c-1) fprintf(fp,":");
        }
        printf("\n");
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n");
    return NULL;
}
