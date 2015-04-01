/******************************************************************************
 *
 * File Name: puzzle.h
 * NAME
 *     puzzle.h - definition of puzzle.
 *
 *****************************************************************************/
 #define BUFFSIZE 1024

#ifndef __PUZZLE_H__
#define __PUZZLE_H__
#include "utils.h"

typedef enum tipo_celulas { Preta =-1, Soma =1 , Vazio =0 } tipo_celulas;

typedef struct p {
    int* valor;
    tipo_celulas tipo;

} puzzle;

puzzle** cria_puzzle (char*,FILE**);
puzzle** aloca_puzzle (int, int);
puzzle** preenche_puzzle(char *, puzzle** , int );
puzzle** preenche_puzzle_combinacoes(puzzle** , int, int );
puzzle** intersect_comb(puzzle**);

#endif

