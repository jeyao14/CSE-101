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
	    	addEdge(G, point1, point2);
	    }

	    printGraph(out, G);
	    List L = newList();

	    //print the rest of the crap
	    while(fscanf(in, "%d %d", &point1, &point2)){
	    	if(point1 == 0 && point2 == 0){
	    		break;
	    	}
	    	BFS(G, point1);
	    	getPath(L, G, point2);
    		fprintf(out, "The distance from %d to %d is %d\n", point1, point2, getDist(G, point2));
	    	if(getDist(G, point2) >= 0){
	    		fprintf(out, "A shortest %d-%d path is: ", point1, point2);
	    		printList(out, L);
	    		fprintf(out, "\n");
	    	}else{
	    		fprintf(out, "infinity\n");
	    		fprintf(out, "No %d-%d path exists", point1, point2);
	    		fprintf(out, "\n");
	    	}
	    	clear(L);

	    }
	    freeList(&L);

   		fclose(in);
   		fclose(out);
   		freeGraph(&G);
   		return(0);
		//printGraph()
}