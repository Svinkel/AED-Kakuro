/******************************************************************************
 *
 * File Name: tree.h
 * NAME
 *     tree.h - List defnition
 *
 *****************************************************************************/

#ifndef __LIST_H__
#define __LIST_H__

#include "Item.h"

typedef struct l{
    item    node;
    int     n;
    struct l *next;
}list;

typedef struct q{
    item    first;
    item    last;
}queue;

list*   addElement(list*,item,int,queue*);
list*   removeLastElement(list*,queue*);

#endif
