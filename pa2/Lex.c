#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 180

//-----------------------------------------------------------------------------
//	Jeffrey Yao
//	jeyao
//	pa2
//	101, 4/23/19
//	Lex.c
//	Program that sorts a series of strings alphabetically, written in C
//-----------------------------------------------------------------------------

//int main(void){
//		printf("kill me");
//}

int main(int argc, char *argv[]){
		//printf("it runs");
		if(argc != 3){
			printf("Usage: Lex <input> <output>\n");
			exit(1);
		}

		FILE *in, *out;
      	char line[MAX_LEN];
      	
      	int lineNumber = 0;
      	//printf("it runs");
      
	    in = fopen(argv[1], "r");
	    out = fopen(argv[2], "w");

	    //printf("files open");
        if( in==NULL ){
	        printf("Unable to open file %s for reading\n", argv[1]);
      		exit(1);
   		}
   		if( out==NULL ){
      		printf("Unable to open file %s for writing\n", argv[2]);
      		exit(1);
   		}

	    while(fgets(line, MAX_LEN, (FILE*) in) != NULL){
	        lineNumber++;
	        //printf("number count");
	    }
	    
	   	
	    
	    //char input[lineNumber];
	    char** input = malloc(lineNumber*sizeof(char*));
	    int counter = 0;
	    // allocates the block to the string
	    for(int i = 0; i < lineNumber; i++){
	 	   input[i] = malloc(MAX_LEN*sizeof(char*));
	 	   //printf("space allocates\n");
		}
		rewind(in);
	    while(fgets(line, MAX_LEN, in) != NULL){
	        strcpy(input[counter], line);
	        //printf("copy works \n");
	        counter++;
	    }

	    List L = newList();
	    //printf("list works\n");
	    append(L, 0);
	    //printf("append works\n");
		//System.out.println(output.get()+ " " + output.length()+" "+output.index());
    	for(int j = 1; j < lineNumber; j++){
    		//printf("size check\n");
	    	moveFront(L);
	    	//printf("move front works\n");
	    	while(index(L) >= 0){
	    		//System.out.println(output.get()+ " " + output.length()+" "+output.index());
	    		//printf("indexing\n");
	    		if(strcmp(input[j], input[get(L)]) < 0){
	    			insertBefore(L, j);
	    			//printf("insert works\n");
	    			break;
	    			//System.out.println(output.length());
	    		}
	    		//System.out.println("moved " + output.index());
	    		moveNext(L);
	    	}
	    	if(index(L) < 0){
	    		append(L, j);
	    	}
	    }

	    moveFront(L);

		for(int i = 0; i < lineNumber;  i++){
			//fprintf(out, "%s", input[get(L)]);
			if(index(L) >= 0){
				fputs(input[get(L)], out);
				//printf("print to file\n");
			}
			moveNext(L);
		}
		clear(L);
		freeList(&L);
		//printf("free list\n");

	    for(int i = 0; i < lineNumber; i++){
	    	free(input[i]);
	    //	printf("free node\n");
	    }
	    free(input);

	    fclose(in);
	    fclose(out);
	    return(0);
}


