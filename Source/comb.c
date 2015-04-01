#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comb_3_2[]={1,2,0};
int comb_4_2[]={1,3,0};
int comb_16_2[]={7,9,0};
int comb_17_2[]={8,9,0};
int comb_6_3[]={1,2,3,0};
int comb_7_3[]={1,2,4,0};
int comb_23_3[]={6,8,9,0};
int comb_24_3[]={7,8,9,0};
int comb_5_2[]={1,2,3,4,0};
int comb_6_2[]={1,2,4,5,0};
int comb_11_4[]={1,2,3,5,0};
int comb_14_2[]={5,6,8,9,0};
int comb_29_4[]={5,7,8,9,0};
int comb_15_2[]={6,7,8,9,0};
int comb_8_3[]={1,2,3,4,5,0};
int comb_16_5[]={1,2,3,4,6,0};
int comb_34_5[]={4,6,7,8,9,0};
int comb_22_3[]={5,6,7,8,9,0};
int comb_7_2[]={1,2,3,4,5,6,0};
int comb_22_6[]={1,2,3,4,5,7,0};
int comb_8_2[]={1,2,3,5,6,7,0};
int comb_12_2[]={3,4,5,7,8,9,0};
int comb_38_6[]={3,5,6,7,8,9,0};
int comb_13_2[]={4,5,6,7,8,9,0};
int comb_10_3[]={1,2,3,4,5,6,7,0};
int comb_29_7[]={1,2,3,4,5,6,8,0};
int comb_41_7[]={2,4,5,6,7,8,9,0};
int comb_20_3[]={3,4,5,6,7,8,9,0};
int comb_9_2[]={1,2,3,4,5,6,7,8,0};
int comb_37_8[]={1,2,3,4,5,6,7,9,0};
int comb_38_8[]={1,2,3,4,5,6,8,9,0};
int comb_39_8[]={1,2,3,4,5,7,8,9,0};
int comb_41_8[]={1,2,3,5,6,7,8,9,0};
int comb_42_8[]={1,2,4,5,6,7,8,9,0};
int comb_43_8[]={1,3,4,5,6,7,8,9,0};
int comb_10_2[]={1,2,3,4,6,7,8,9,0};
int comb_11_2[]={2,3,4,5,6,7,8,9,0};
int comb_total[]={1,2,3,4,5,6,7,8,9,0};


/******************************************************************************
 * combinaçoes()
 *
 * Arguments: soma - valor da soma
 *            n_celulas - número de celulas vazias
 *
 * Returns: vector com as combinaçoes possiveis
 *
 * Description: Dada uma soma e o correspondente numero de celulas vazias
 *              esta funçao retorna o vector com as combinaçoes possiveis
 *
 *****************************************************************************/


int * combinacoes(int soma, int n_celulas){

 /* Switch consoante o número de células vazias */

    switch(n_celulas){

        case 2:
            if(soma==3) { return comb_3_2;}
            if(soma==4) { return comb_4_2;}
            if(soma==16){ return comb_16_2;}
            if(soma==17){ return comb_17_2;}
            if(soma==5) { return comb_5_2;}
            if(soma==6) { return comb_6_2;}
            if(soma==14){ return comb_14_2;}
            if(soma==15){ return comb_15_2;}
            if(soma==7) { return comb_7_2;}
            if(soma==8) { return comb_8_2;}
            if(soma==12){ return comb_12_2;}
            if(soma==13){ return comb_13_2;}
            if(soma==9) { return comb_9_2;}
            if(soma==10){ return comb_10_2;}
            if(soma==11){ return comb_11_2;}
            break;
        case 3:
            if(soma==6) { return comb_6_3;}
            if(soma==7) { return comb_7_3;}
            if(soma==23){ return comb_23_3;}
            if(soma==24){ return comb_24_3;}
            if(soma==8) { return comb_8_3;}
            if(soma==22){ return comb_22_3;}
            if(soma==9) { return comb_7_2;}
            if(soma==21){ return comb_13_2;}
            if(soma==10){ return comb_10_3;}
            if(soma==20){ return comb_20_3;}
            if(soma==11){ return comb_9_2;}
            if(soma==19){ return comb_11_2;}
            if(soma>=12 && soma<=18) { return comb_total;}
            break;
        case 4:
            if(soma==10) { return comb_5_2;}
            if(soma==11) { return comb_11_4;}
            if(soma==29) { return comb_29_4;}
            if(soma==30) { return comb_15_2;}
            if(soma==12) { return comb_7_2;}
            if(soma==28) { return comb_13_2;}
            if(soma==13) { return comb_10_3;}
            if(soma==27) { return comb_20_3;}
            if(soma==14) { return comb_9_2;}
            if(soma==26) { return comb_11_2;}
            if(soma>=15 && soma<=25) { return comb_total;}
            break;
        case 5:
            if(soma==15) { return comb_8_3;}
            if(soma==16) { return comb_16_5;}
            if(soma==34) { return comb_34_5;}
            if(soma==35) { return comb_22_3;}
            if(soma==17) { return comb_10_3;}
            if(soma==33) { return comb_20_3;}
            if(soma==18) { return comb_9_2;}
            if(soma==32) { return comb_11_2;}
            if(soma>=19 && soma<=31) { return comb_total;}
            break;
        case 6:
            if(soma==21) { return comb_7_2;}
            if(soma==22) { return comb_22_6;}
            if(soma==38) { return comb_38_6;}
            if(soma==39) { return comb_13_2;}
            if(soma==23) { return comb_9_2;}
            if(soma==37) { return comb_11_2;}
            if(soma>=24 && soma<=36) { return comb_total;}
            break;
        case 7:
            if(soma==28) { return comb_10_3;}
            if(soma==29) { return comb_29_7;}
            if(soma==41) { return comb_41_7;}
            if(soma==42) { return comb_20_3;}
            if(soma>=30 && soma<=40) { return comb_total;}
            break;
        case 8:
            if(soma==36) { return comb_9_2;}
            if(soma==37) { return comb_37_8;}
            if(soma==38) { return comb_38_8;}
            if(soma==39) { return comb_39_8;}
            if(soma==40) { return comb_10_2;}
            if(soma==41) { return comb_41_8;}
            if(soma==42) { return comb_42_8;}
            if(soma==43) { return comb_43_8;}
            if(soma==44) { return comb_11_2;}
            break;
        case 9:
            if(soma==45) { return comb_total;}
            break;
    }
    return 0;
}
