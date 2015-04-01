#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "puzzle.h"
#include "tree.h"

int l,c;

int main (int argc, char *argv[]) {
  puzzle**  mat;
  FILE*     fpout;
  tree*     t=NULL;
  coord     crd;
  queue     q;
    crd.x=crd.y=0;
    q.first=q.last=NULL;

    CheckArg(argc);
    /*-----------------------------------------*/printf("\t \t \t %s \n", argv[1]);
    mat = cria_puzzle(argv[1],&fpout);
    /*-----------------------------------------*/printf("\n");
    t = createTree(nextCoord(crd,mat),NULL, mat, (queue*)&q );

    if (q.first!=NULL) imprime_puzzle(q.first,fpout);
    free_memory_puzzle(mat);

    if (fpout!=NULL) fclose(fpout);
    return 0;
}
