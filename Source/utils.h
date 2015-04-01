/******************************************************************************
 *
 * File Name: utils.h
 * NAME
 *     ultis.h - Miscelaneous Fuctions
 *
 *****************************************************************************/

#ifndef __UTILS_H__
#define __UTILS_H__

#include "puzzle.h"

 typedef struct cordenadas {
     int x;
     int y;
 }coord;

void    CheckArg (int );
void    free_memory_puzzle(puzzle** mat);
FILE*   CheckFile (char*,char*);
FILE*   CreateFileOut (char*);
coord   nextCoord(coord, puzzle**);
int     Less(int a,int b);
int     CalculaSoma(int,int);
int*   verifica_soma_coordenada(puzzle**, coord);
int*    limit_combinacoes(int*, int*);
int*    dif_comb(int*, int);
int*    combinacoes(int, int);

extern int l,c;


#endif
