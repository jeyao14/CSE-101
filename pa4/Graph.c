#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"


/*** Constructors-Destructors ***/
typedef struct GraphObj{
	List* adj;
	int* dis;
	int* par;
	char* colour;
	int order, size, source;
} GraphObj;

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->dis = malloc((n+1)*sizeof(int));
	G->par = malloc((n+1)*sizeof(int));
	G->adj = malloc((n+1)*sizeof(List));
	G->colour = malloc((n+1)*sizeof(char));
	G->adj[0] = NULL;
	G->order = n;
	G->size = 0;
	G->source = NIL;
	for(int i = 1; i <= n; i++){
		G->adj[i] = newList();
		G->dis[i] = INF;
		G->par[i] = NIL;
		G->colour[i] = 'w';
	}
	return (G);
}

void freeGraph(Graph* pG){
	if(pG != NULL && *pG != NULL){
		for(int i = 1; i <= (*pG)->order; i++){
			freeList(&(*pG)->adj[i]);
		}
		free((*pG)->adj);
		free((*pG)->dis);
		free((*pG)->par);
		free((*pG)->colour);
		free(*pG);
		*pG = NULL;
	}
}


/*** Access functions ***/
int getOrder(Graph G){
	return G->order;
}
int getSize(Graph G){
	return G->size;
}
int getSource(Graph G){
	return G->source;
}
int getParent(Graph G, int u){
	if(!(1 <= u) && !(u <= getOrder(G))){
		printf("Error: getParent() called on invalid vertex");
		exit(1);
	}
	return G->par[u];
}
int getDist(Graph G, int u){
	if(!(1 <= u) && !(u <= getOrder(G))){
		printf("Error: getDist() called on invalid vertex");
		exit(1);
	}
	return G->dis[u];
}
void getPath(List L, Graph G, int u){
	if(!(1 <= u) && !(u <= getOrder(G))){
		printf("Error: getPath() called on invalid vertex");
		exit(1);
	}
	if(getSource(G) == NIL){
		printf("Error: getPath() called on invalid source");
		exit(1);
	}
	if(u == getSource(G)){ 
		append(L, u);
	}else if(getParent(G, u) == NIL){ //if 
		append(L, NIL);
	}else{
		getPath(L, G, getParent(G, u));
		append(L, u);
	}
}


/*** Manipulation procedures ***/
void makeNull(Graph G){
	for(int i = 0; i <= getOrder(G); i++){
		clear(G->adj[i]); //gotta empty every adjacent matrix
		G->dis[i] = INF;
		G->par[i] = NIL;
		G->colour[i] = 'w';
	}
}
void addEdge(Graph G, int u, int v){
	if(!(1 <= u) && !(u <= getOrder(G))){
		printf("Error: addEdge() called on invalid vertex: error u");
		exit(1);
	}
	if(!(1 <= v) && !(v <= getOrder(G))){
		printf("Error: addEdge() called on invalid vertex: error v");
		exit(1);
	}
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--; //addarc() is called twice, needs to be called once
}

void addArc(Graph G, int u, int v){
	if(!(1 <= u) && !(u <= getOrder(G))){
		printf("Error: addArc() called on invalid vertex: error u");
		exit(1);
	}
	if(!(1 <= v) && !(v <= getOrder(G))){
		printf("Error: addArc() called on invalid vertex: error v");
		exit(1);
	}
	List L = G->adj[u];
	if(length(L) == 0){ 	//if length is zero
		append(L, v); 	//just slap the vertex into the adjacent matrix
	}else if(length(L) > 0){	//if vertex has edges to other vertices
		moveFront(L);	//move cursor to front
		while(index(L) >= 0){	//while the index of the cursor is not invalid
			if(v < get(L)){		//compare v to the cursor, if v is less than the cursor
				insertBefore(L, v);		//insert v before the cursor
				break;
			}
			moveNext(L);	//else move to the next node
		}
		if(index(L) < 0){
			append(L, v);
		}
	}
	G->size++;
}

void BFS(Graph G, int s){
	for(int i = 1; i <= G->order; i++){
		G->colour[i] = 'w';
		G->dis[i] = INF;
		G->par[i] = NIL;
	}
	G->colour[s] = 'g'; // discover the source 𝑠
	G->dis[s] = 0;
	G->par[s] = NIL;
	G->source = s;
	List L = newList();
	append(L, s);
	while(length(L) > 0){
		int y = front(L);
		List Q = G->adj[y];
		deleteFront(L);
		for(moveFront(Q); index(Q) >= 0; moveNext(Q)){
			int z = get(Q);
			if(G->colour[z] == 'w'){ // 𝑦 is undiscovered
				G->colour[z] = 'g'; // discover 𝑦
				G->dis[z] = G->dis[y] + 1;
				G->par[z] = y;
		 		append(L, z);
		 	}
		}
		G->colour[y] = 'b'; // finish �
	}
	freeList(&L);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	for(int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
}