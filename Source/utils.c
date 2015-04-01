 /*****************************************************************************
 *
 * File Name: utils.c
 *	      (c) 2012 AED
 * Author:    João Baúto && Ricardo Vieira
 * Revision:  2012
 *
 * NAME
 *     utils
 *
 * DESCRIÇÃO
 *  - Verifica ficheiro de entrada;
 *  - Abre e cria o ficheiro de saida se possivel;
 *  - Calcula o valor das somas, superior e inferior;
 *  - Calcula a próxima coordenada a ser analisada;
 *  - Dada uma coordenada indica a soma superior, soma inferior
 *    e o número de quadrados disponivel para preencher;
 *  - Liberta memória alocada para o puzzle
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "Item.h"

/******************************************************************************
 * CheckArg()
 *
 * Arguments: n - número de parametros quando se corre o programa
 * Returns: (void)
 *
 * Description: Verifica ficheiro de entrada;
 *
 *****************************************************************************/

void CheckArg (int n) {
    if (n<2) {
        printf("ERRO: Nome de ficheiro não inserido.\n");
        printf("Por favor chame o programa com o nome do ficheiro a abrir.\n");
        exit(-1);
    }
    return;
}

/******************************************************************************
 * CheckFile()
 *
 * Arguments: fp - ponteiro para ficheiro
 *            *t - modo de abertura do ficheiro
 * Returns: ponteiro para ficheiro
 *
 * Description: Abre o ficheiro se possivel;
 *
 *****************************************************************************/

FILE* CheckFile (char *fp, char *t) {
    FILE* fpin;

    fpin=fopen(fp,t);
    if (fpin==NULL) {
        if (strcmp(t,"r")==0){
            printf("ERRO: O ficheiro não foi aberto.\n");
        }else{
            printf("ERRO: O ficheiro de saída não pode ser criado.\n");
        }
        exit(-2);
    } else return fpin;
}

/******************************************************************************
 * CheckFileOut()
 *
 * Arguments: fp - ponteiro para ficheiro
 * Returns: ponteiro para ficheiro de saida
 *
 * Description: Abre e cria o ficheiro de saída se possivel;
 *
 *****************************************************************************/

FILE* CreateFileOut (char *fp) {
    char *point;
    point=strrchr(fp,'.');

    if (point!=NULL)(*point)='\0';
    sprintf(fp, "%s%s", fp,".sol");

    return CheckFile(fp,"w");
}

/******************************************************************************
 * CalculaSoma()
 *
 * Arguments: soma - valor lido do ficheiro
              sentido - 1 se soma superior, 0 se inferior
 * Returns: valor da soma
 *
 * Description: Calcula o valor das somas, superior e inferior;
 *
 *****************************************************************************/

int CalculaSoma(int soma, int sentido){

    if(sentido==1){
        return (soma/100);
    }else{
        return (soma%100);
    }
}

/******************************************************************************
 * Less()
 *
 * Arguments: a - numero inteiro
              b - numero inteiro
 * Returns: "a" se a inferior a b, "b" se a superior a b
 *
 * Description: Determina o valor maior ou menor;
 *
 *****************************************************************************/

int Less(int a,int b){

    if(a<b) return a;
    if(a>b) return b;
    if(a==b) return a;

    return -1;
}

/******************************************************************************
 * nextCoord()
 *
 * Arguments: crd - coordenada de um espaço vazio
 *            mat - matriz que contem o jogo
 * Returns: coordenada para o proximo valor a ser analisado
 *
 * Description: Determina o valor maior ou menor;
 *
 *****************************************************************************/

coord nextCoord(coord crd, puzzle** mat){

    extern int l,c;
    int i,j;
    coord c_novo;

    c_novo.y = c_novo.x = -1;
    /* Se chegar aos limites da matriz */
    if (crd.x<c-1) crd.x++;
        else if (crd.y<l-1) {
                crd.y++;
                crd.x=0;
            } else {
                return c_novo;
            }

    for(i=crd.y; i<l; i++){
        for(j=crd.x; j<c; j++){
    /* Se for uma célula vazia guarda as coordenadas */
            if(mat[i][j].tipo == Vazio){
                c_novo.x=j;
                c_novo.y=i;
                return c_novo;
            }
        }
        crd.x=0;
    }
    return c_novo;
}

/******************************************************************************
 * verifica_soma_coordenada()
 *
 * Arguments: crd - coordenada de um espaço vazio
 *            mat - matriz que contem o jogo
 * Returns: vector com a soma superior, inferior, numero de quadrados
 *           e linha/coluna
 *
 * Description: Determina o valor maior ou menor;
 *
 *****************************************************************************/

int * verifica_soma_coordenada(puzzle** mat, coord crd){

    int i,j;
    int * somas_quadrados=NULL;

    somas_quadrados = (int*) malloc(6*sizeof(int));
    if (somas_quadrados==NULL) {
        printf("ERRO: Memoria não disponivel.\n");
        exit(-3);
    }

    for(i=crd.y; (mat[i][crd.x].tipo != Soma) ; i--);
    /* Procura a soma superior */
    somas_quadrados[0] = CalculaSoma(mat[i][crd.x].valor[0],1);
    somas_quadrados[1] = mat[i][crd.x].valor[1];
    somas_quadrados[2] = i;

    for(j=crd.x; (mat[crd.y][j].tipo != Soma) ; j--);
    /* Procura a soma inferior */
    somas_quadrados[3] = CalculaSoma(mat[crd.y][j].valor[0],0);
    somas_quadrados[4] = mat[crd.y][j].valor[2];
    somas_quadrados[5] = j;

    return somas_quadrados;

}

/******************************************************************************
 * free_memory_puzzle()
 *
 * Arguments: mat - matriz que contem o jogo
 * Returns: (void)
 *
 * Description: Liberta memória alocada para o puzzle;
 *
 *****************************************************************************/

void free_memory_puzzle(puzzle** mat){

    int i,j;

    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            if(mat[i][j].tipo!=Preta){
                free(mat[i][j].valor);
            }
        }
        free(mat[i]);
    }
    free(mat);
    return;
}

/******************************************************************************
 * limit_combinacoes()
 *
 * Arguments: a - ponteiro para um vector
              b - ponteiro para um vector
 * Returns: ponteiro para vector
 *
 * Description: Recebe dois vectores e retorna os elementos em comum;
 *
 *****************************************************************************/

int * limit_combinacoes(int *a, int *b){

    int i,j,m=0;
    int *comb=NULL;

    comb = calloc(10,sizeof(int));
    if (comb==NULL) {
        printf("ERRO: Memoria não disponivel.\n");
        exit(-3);
    }
    comb[9]=0;
    for(i=0; a[i]!=0; i++){
        for(j=0; b[j]!=0; j++){
    /* Se os dois elementos forem iguais copia para comb */
            if(a[i] == b[j]){
                comb[m] = a[i];
                m++;
            }
        }
    }
    return comb;

}

/******************************************************************************
 * dif_comb()
 *
 * Arguments: a - ponteiro para um vector
              num - numero de uma combinaçao
 * Returns: ponteiro para vector
 *
 * Description: Recebe um vector e um numero e elimina desse vector o numero
 *              indicado por num.
 *
 *****************************************************************************/

int * dif_comb(int *a, int num){

    int i;

    for(i=0;a[i]!=0;i++){
        if(a[i] == num){
            a[i] = -1;
        }
    }
    return a;
}
