 /*****************************************************************************
 *
 * File Name: puzzle.c
 *	      (c) 2012 AED
 * Author:    João Baúto && Ricardo Vieira
 * Revision:  2012
 *
 * NAME
 *     puzzle
 *
 * DESCRIÇÃO
 *  - Cria a matriz com o jogo;
 *  - Lê informação do ficheiro de entrada para a matriz;
 *  - Sabendo as somas, preenche a matriz com as combinações possiveis
 *    e calcula o numero de quadrados disponiveis;
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "puzzle.h"

/******************************************************************************
 * cria_puzzle()
 *
 * Arguments: caminho - nome do ficheiro de entrada
              fpout - duplo ponteiro para o ficheiro de saída
 * Returns:   matriz com o jogo
 *
 * Description: Verifica o ficheiro de entrada;
 *              Cria o ficheiro de saida;
 *              Aloca memoria com o tamanho do jogo;
 *              Le informação do ficheiro e coloca dentro da matriz;
 *              Sabendo as somas, preenche a matriz com as combinações possiveis
 *              e calcula o numero de quadrados disponiveis;
 *
 *****************************************************************************/

puzzle** cria_puzzle (char* caminho, FILE** fpout) {
  char buffer[BUFFSIZE];
  FILE *fp=NULL;
  extern int l,c;
  int i=0;
  puzzle **p=NULL;

    fp=CheckFile(caminho,"r");
    (*fpout)=CreateFileOut(caminho);

    fgets(buffer,1000,fp);
    fprintf((FILE*)*fpout,"%s",buffer);
    l=atoi(buffer);

    fgets(buffer,1000,fp);
    fprintf((FILE*)*fpout,"%s",buffer);
    c=atoi(buffer);

    p=aloca_puzzle(l,c);
    fgets(buffer,1000,fp);
    fprintf((FILE*)*fpout,"%s",buffer);

    for(i=0; i<l; i++) {
        fgets(buffer,1000,fp);
        fprintf((FILE*)*fpout,"%s",buffer);
        p=preenche_puzzle(buffer,p,i);
        printf("\n");
    }
    fprintf((FILE*)*fpout,"\n");
    p=preenche_puzzle_combinacoes(p,l,c);
    p=intersect_comb(p);


    fclose(fp);
    return p;
}

/******************************************************************************
 * aloca_puzzle()
 *
 * Arguments: l - numero de linhas
              c - numero de colunas
 * Returns:   matriz com o jogo
 *
 * Description: Aloca memoria com o tamanho l por c;
 *
 *****************************************************************************/

puzzle** aloca_puzzle (int l, int c) {
  puzzle **p=NULL;
  int i;

    p=(puzzle**) calloc(l,sizeof(puzzle*));
    if (p==NULL) {
        printf("ERRO: Memoria não disponivel.\n");
        exit(-3);
    }

    for (i=0; i<l; i++){
        p[i]=(puzzle*) calloc(c,sizeof(puzzle));
        if (p[i]==NULL) {
            printf("ERRO: Memoria não disponivel.\n");
            exit(-3);
        }
        p[i]->valor=NULL;
        p[i]->tipo=0;
    }
    return p;
}

/******************************************************************************
 * preenche_puzzle()
 *
 * Arguments: linha - linha lido do ficheiro de entrada;
              mat - matriz com o jogo;
              contador -  indicador de que linha esta a ler;
 * Returns:   matriz com o jogo
 *
 * Description: Le uma linha do ficheiro de entrada;
 *              Se o caracter lido for "0" ou "0\n"
 *
 *****************************************************************************/

puzzle** preenche_puzzle(char *linha, puzzle** mat, int contador)
{
    char *pch=NULL;
    int i = 0;

    pch = strtok(linha,":");

    while( pch !=NULL){
    /* Se for 0 ou 0\n a célula em questão é Preta */
        if(strcmp(pch,"0") == 0 || strcmp(pch,"0\n") == 0){
            mat[contador][i].tipo = Preta;
            printf("\tXXX");
        }else{
    /* Se for - ou -\n a célula em questão é Vazia */
            if(strcmp(pch,"-") == 0 || strcmp(pch,"-\n") == 0){
                mat[contador][i].tipo = Vazio;
                printf("\t--");
            }else{
    /* Se nao for nenhum dos casos anteriores trata-se de uma soma */
                 mat[contador][i].valor = (int*) malloc (3*sizeof(int));
                 mat[contador][i].valor[0]=0;
                 mat[contador][i].valor[1]=0;
                 mat[contador][i].valor[2]=0;
    /* valor[0] = soma \\ valor[1] = quadrados da soma sup \\ valor[2] = quadrados da soma inf */
                 *mat[contador][i].valor = atoi(pch);
                 mat[contador][i].tipo = Soma;
                 printf("\t%d", *mat[contador][i].valor);
            }
        }
     i++;
     pch = strtok(NULL,":");
    }
    return mat;
}

/******************************************************************************
 * preenche_puzzle_combinacoes()
 *
 * Arguments: mat - matriz com o jogo
              l - numero de linhas
              c - numero de colunas
 * Returns: matriz com o jogo
 *
 * Description: Preenche a matriz com o valores das somas, superiores e inferiores
 *              o número de celulas por soma;
 *              Dada a soma superior e inferior, o programa intersecta as duas
 *              combinaçoes e retorna a combinaçao em comum
 *
 *****************************************************************************/

puzzle** preenche_puzzle_combinacoes(puzzle** mat, int l, int c){

    int i,j;
    int m,n;
    int soma=0, flag_soma=0, flag_vazio;
    int *vecsoma;
    coord crd;

    /* Este ciclo analisa a matriz verticalmente */

    for(j=0;j<c;j++){
        for(i=0;i<l;i++){
    /* Só entra neste if se a célula for Vazia e se no ciclo anterior entrou no
         if correspondente à existência de uma célula com soma */
            if(flag_soma == 1 && flag_vazio == 0 && mat[i][j].tipo == Vazio){
                mat[m][n].valor[1]++;
                flag_soma = 1;
                flag_vazio = 0;
            }
    /* Se for preta impede a entrada no if correspondente à célula Vazia */
            if(mat[i][j].tipo == Preta){
                flag_soma = 0;
                flag_vazio = 1;
            }
    /* Se entrar neste if possibilita a existência de célula Vazia a seguir */
            if(mat[i][j].tipo == Soma){
                soma = CalculaSoma((mat[i][j].valor[0]), 1);
                flag_soma = 1;
                flag_vazio = 0;
                m=i;
                n=j;
                mat[m][n].valor[1]=0; /* Indicador do nº de quadrados */
            }
        }
    }

    /* Este ciclo analisa a matriz horizontalmente */

    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
    /* Só entra neste if se a célula for Vazia e se no ciclo anterior entrou no
         if correspondente à existência de uma célula com soma */
            if(flag_soma == 1 && flag_vazio == 0 && mat[i][j].tipo == Vazio){
                mat[m][n].valor[2]++;
                flag_soma = 1;
                flag_vazio = 0;
            }
    /* Se for preta impede a entrada no if correspondente à célula Vazia */
            if(mat[i][j].tipo == Preta){
                flag_soma = 0;
                flag_vazio = 1;
            }
    /* Se entrar neste if possibilita a existência de célula Vazia a seguir */
            if(mat[i][j].tipo == Soma){
                soma = CalculaSoma((mat[i][j].valor[0]), 0);
                flag_soma = 1;
                flag_vazio = 0;
                m=i;
                n=j;
                mat[m][n].valor[2]=0; /* Indicador do nº de quadrados */
            }

        }
    }

    /* Este ciclo determina as combinações possiveis para cada células */

    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            if(flag_soma == 1 && flag_vazio == 0 && mat[i][j].tipo == Vazio){
                crd.x = j;
                crd.y = i;
    /* Dada uma coordenada esta função retorna a soma superior, inferior bem como
        o número de quadrados */
                vecsoma = verifica_soma_coordenada(mat,crd);
                if (vecsoma==NULL) {
                    printf("ERRO: Memoria não disponivel.\n");
                    exit(-3);
                }
    /* A função combinaçoes recebe dois numeros, o valor da soma e o número de quadrados
       retornando um vector com as combinaçoes possiveis.
       A função limit_combinaçoes recebe as combinaçoes da soma superior e inferior e
       intersecta ambas, retornando apenas os números que havia em comum */
                mat[i][j].valor = limit_combinacoes(combinacoes(vecsoma[0],vecsoma[1]),combinacoes(vecsoma[3],vecsoma[4]));
                free(vecsoma);
                flag_soma = 1;
                flag_vazio = 0;
            }
            if(mat[i][j].tipo == Preta){
                flag_soma = 0;
                flag_vazio = 1;
            }
            if(mat[i][j].tipo == Soma){
                flag_soma = 1;
                flag_vazio = 0;
            }

        }
    }


    return mat;
}

/******************************************************************************
 * intersect_comb()
 *
 * Arguments: mat - matriz com o jogo
 * Returns: matriz com o jogo
 *
 * Description: Dada a matriz com o jogo a função procura uma célula vazia em
 *              que o número de combinações corresponde a 1, ou seja, o valor
 *              final. Sabendo este valor, pode retirar das celulas adjacentes
 *              este número das suas combinações.
 *
 *****************************************************************************/


puzzle ** intersect_comb(puzzle** mat){

    int i,j,m,n=0;
    int indice=0;
    int h=1;
    int cont=0;
    int num_remove;
    coord crd;

    crd.y=crd.x=0;

    crd = nextCoord(crd,mat);

    while(1){

        if(crd.y == -1 && crd.x == -1){
            crd.y = crd.x = 0;
        /* Vai retornar a próxima coordenada */
            crd = nextCoord(crd,mat);
        /* Guarda o número de eliminações de combinações */
            cont = h;
            h = 0;
        }

        n = 0;
    /* Dada uma coordenada é verificado se o vector correspondente às combinações
       apenas contêm um número, ou seja, o valor final. Se sim, esse número tem que
       ser retirado as células adjacentes */
        for(m=0; mat[crd.y][crd.x].valor[m] != 0 ; m++){
            if(mat[crd.y][crd.x].valor[m]!= -1 && (mat[crd.y][crd.x].valor[m]!= 0)){
                indice=m;
                n++;
            }
        }

        if(n == 1 ){
            num_remove = mat[crd.y][crd.x].valor[indice];
    /* Elimina o número em todas as células acima até encontrar uma célula diferente de Vazia */
            for(i=crd.y; (mat[i][crd.x].tipo == Vazio) ; i--){
                if(i != crd.y){
                    mat[i][crd.x].valor = dif_comb(mat[i][crd.x].valor,num_remove);
                    h++;
                }
            }
    /* Elimina o número em todas as células do seu lado esquerdo até encontrar uma célula
        diferente de Vazia */
            for(j=crd.x; (mat[crd.y][j].tipo == Vazio) ; j--){
                if(j != crd.x){
                    mat[crd.y][j].valor = dif_comb(mat[crd.y][j].valor,num_remove);
                    h++;
                }
            }
    /* Elimina o número em todas as células abaixo até encontrar uma célula diferente de Vazia */
            for(i=crd.y; (mat[i][crd.x].tipo == Vazio) && i<l ; i++){
                if(i != crd.y){
                    mat[i][crd.x].valor = dif_comb(mat[i][crd.x].valor,num_remove);
                    h++;
                }
                if(i+1 == l) break;
            }
    /* Elimina o número em todas as células do seu lado direito até encontrar uma célula
        diferente de Vazia */
            for(j=crd.x; (mat[crd.y][j].tipo == Vazio) && j<c; j++){
                if(j != crd.x){
                    mat[crd.y][j].valor = dif_comb(mat[crd.y][j].valor,num_remove);
                    h++;
                }
                if(j+1 == c) break;
            }
        }
        /* Se ao analisar a matriz o número de alterações for igual ao número anterior o programa
            é forçado a sair */
            if(h == cont) break;
            crd=nextCoord(crd,mat);
    }



    return mat;
}
