#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#define MAX_LEN 160

int main(int argc, char *argv[]){
		if(argc != 3){
			printf("Usage: FindPath <input> <output>\n");
			exit(1);
		}
		FILE *in, *out;
		char line[MAX_LEN];
		int vert = 0;
		int components = 0;

		in = fopen(argv[1], "r");
	    out = fopen(argv[2], "w");

		if( in==NULL ){
	        printf("Unable to open file %s for reading\n", argv[1]);
      		exit(1);
   		}
   		if( out==NULL ){
      		printf("Unable to open file %s for writing\n", argv[2]);
      		exit(1);
   		}

   		fscanf(in, "%d", &vert);
   		Graph G = newGraph(vert);
   		int point1, point2;

   		//get all the edges
   		//printf("before while");
   		while(fscanf(in, "%d %d", &point1, &point2)){
   			//printf("while runs");
	    	if(point1 == 0 && point2 == 0){
	    		break;
	    	}
	    	addArc(G, point1, point2);
	    }

	    fprintf(out, "Adjacency list representation of G:\n");
	    printGraph(out, G);
	    List L = newList();
	    List C = newList();

	    for(int i = 1; i <= getOrder(G); i++){
	    	prepend(L, i);
	    }


	    //print the rest of the crap
	    DFS(G, L);
	    Graph T = transpose(G);
	    DFS(T, L);

	    for(moveFront(L); index(L)>= 0; moveNext(L)){
	    	if(getParent(T, get(L)) == NIL){
	    		components++;
	    	}
	    }

	    fprintf(out, "G contains %d strongly connected components:\n", components);


	    moveFront(L);
	    for(int i = 0; i <= components; i++){
	    	fprintf(out, "Component %d:", i);
	    	while(getParent(T, get(L))!=NIL){
	    		append(C, get(L));
	    		moveNext(L);
	    	}
	    	append(C, back(L));
	    	printList(out, C);
	    	fprintf(out, "\n");
	    	clear(C);
	    }

	    freeList(&L);

   		fclose(in);
   		fclose(out);
   		freeGraph(&G);
   		return(0);
		//printGraph()
}