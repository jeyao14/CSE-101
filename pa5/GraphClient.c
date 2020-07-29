//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
         Graph A = newGraph(100);
         List L = newList();
         addArc(A, 64, 4);
        addArc(A, 64, 3);
        addArc(A, 42, 2);
        addArc(A, 2, 64);
        addArc(A, 4, 2);
        addArc(A, 3, 42);
        for (int i = 1; i <= 100; i++) {
          prepend(L, i);
        }
        printf("first dfs\n");
        //printf("%d %d\n", length(L), getOrder(A));
        //printList(stdout, L);
        DFS(A, L);
        if (getDiscover(A, 100) != 1) printf("fail 1\n");
        if (getDiscover(A, 64) != 73) printf("fail 2\n");
        if (getDiscover(A, 4) != 80) printf("fail 3\n");
        printf("second dfs\n");
        //printf("%d %d\n", length(L), getOrder(A));
        //printList(stdout, L);
        DFS(A, L);
        
        if (getDiscover(A, 4) != 126) printf("fail 4\n");
        if (getDiscover(A, 63) != 117) printf("fail 5\n");
        printf("%d\n", getDiscover(A, 4));
        printf("%d\n", getDiscover(A, 63));
        printf("third dfs\n");
        DFS(A, L);
        
        if (getDiscover(A, 65) != 71) printf("fail 6\n");
        if (getDiscover(A, 1) != 199) printf("fail 7\n");
        return 0;

   /*int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");
   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);*/
}


