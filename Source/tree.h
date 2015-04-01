/******************************************************************************
 *
 * File Name: tree.h
 * NAME
 *     tree.h - Tree structure Fuctions
 *
 *****************************************************************************/

#ifndef __TREE_H__
#define __TREE_H__

#include "Item.h"
#include "utils.h"
#include "puzzle.h"
#include "list.h"

typedef struct tr {
    coord    crd;
    struct tr  *point[9];
} tree;

tree*   createTree(coord,list*, puzzle**,queue*);
tree*   imprime_puzzle(list*,FILE*);
int     checkInsert(int, coord, puzzle**,queue*,list*,int*);

#endif
