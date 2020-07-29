#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"


/*** Constructors-Destructors ***/
typedef struct GraphObj{
	List* adj;
	int* dis;
	int* par;
	int* fin;
	char* colour;
	int order, size, time;
} GraphObj;

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->dis = malloc((n+1)*sizeof(int));
	G->par = malloc((n+1)*sizeof(int));
	G->adj = malloc((n+1)*sizeof(List));
	G->colour = malloc((n+1)*sizeof(char));
	G->fin = malloc((n+1)*sizeof(int));
	G->adj[0] = NULL;
	G->order = n;
	G->size = 0;
	//G->time = 0;
	for(int i = 1; i <= n; i++){
		G->adj[i] = newList();
		G->dis[i] = UNDEF;
		G->fin[i] = UNDEF;
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
		free((*pG)->fin);
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
int getParent(Graph G, int u){
	if(!(1 <= u) && !(u <= getOrder(G))){
		printf("Error: getParent() called on invalid vertex");
		exit(1);
	}
	return G->par[u];
}
int getDiscover(Graph G, int u){
	if(!(1 <= u) && !(u <= getOrder(G))){
		printf("Error: getDiscover() called on invalid vertex");
		exit(1);
	}
	return G->dis[u];
}
int getFinish(Graph G, int u){
	if(!(1 <= u) && !(u <= getOrder(G))){
		printf("Error: getFinish() called on invalid vertex");
		exit(1);
	}
	return G->fin[u];
}



/*** Manipulation procedures ***/

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
		for(moveFront(L); index(L) >= 0; moveNext(L)){//while the index of the cursor is not invalid
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

void visit(Graph G, List S, int u, int *time){
	//1. 𝑑[𝑥] = (+ + time) // discover 𝑥
	//2. color[𝑥] = gray
	//3. for all 𝑦 ∈ adj[𝑥]
	//4. 	if color[𝑦] == white
	//5. 		𝑝[𝑦] = 𝑥
	//6. 		Visit(𝑦)
	//7. color[𝑥] = black
	//8. 𝑓[𝑥] = (+ + time) // finish �
	G->time++;
	G->dis[u] = ++(*time);
	printf("%d %d %d %d\n", u, G->dis[u], getDiscover(G, u), *time);
	//printf("%d\n", getDiscover(G, u));
	G->colour[u] = 'g';
	//List Q = G->adj[u];
	//printf("running function");
	for(moveFront(G->adj[u]); index(G->adj[u]) >= 0; moveNext(G->adj[u])){
		int x = get(G->adj[u]);
		if(G->colour[x] == 'w'){
			G->par[x] = u;
			visit(G, S, x, time);
		}
	}
	G->colour[u] = 'b';
	//G->time++;
	G->fin[u] = ++(*time);
	prepend(S, u);
}


void DFS(Graph G, List S){
	if(length(S) != getOrder(G)){
		printf("Error: DFS() called on invalid adjacent matrix\n");
		exit(1);
	}
	//1. for all 𝑥 ∈ 𝑉(𝐺)
	//2. 	color[𝑥] = white
	//3. 	𝑝[𝑥] = nil
	//4. time = 0
	//5. for all 𝑥 ∈ 𝑉(𝐺)
	//6. 	if color[𝑥] == white
	//7. 	Visit(𝑥)
	int templength = length(S);
	for(int i = 1; i <= getOrder(G); i++){
		G->colour[i] = 'w';
		//printf("%c\n", G->colour[i]);
		G->par[i] = NIL;
		G->dis[i] = UNDEF;
		G->fin[i] = UNDEF;
	}
	int time = 0;
	//printf("%d %d\n", front(S), back(S));
	for(moveFront(S); index(S) >= 0; moveNext(S)){
		if(G->colour[get(S)] == 'w'){
			//printf("going into visit");
			visit(G, S, get(S), &time);
		}
	}
	while(templength != length(S)){
			deleteBack(S);
	}
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	for(int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
}

Graph copyGraph(Graph G){
	if(G == NULL){
		printf("Error: copyGraph() called on empty Graph");
		exit(1);
	}
	Graph C = newGraph(getOrder(G));
	C->size = getSize(G);
	for(int i = 1; i <= getOrder(G); i++){
		freeList(&(C->adj[i]));
		C->adj[i] = copyList(G->adj[i]);
	}
	return C;
}

Graph transpose(Graph G){
	if(G == NULL){
		printf("Error: transpose() called on empty Graph");
		exit(1);
	}
	Graph X = newGraph(getOrder(G));
	for(int i = 1; i < getOrder(G); i++){
		if(length(G->adj[i]) >= 0){
			for(moveFront(G->adj[i]); index(G->adj[i]) >= 0; moveNext(G->adj[i])){
				addArc(X, get(G->adj[i]), i);
			}
		}
	}
	return X;
		/*
		for(int i = 1; i < this.getSize()+1; i++){
	 		for(row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()){
	 			Entry change = (Entry) row[i].get();
	 			M.changeEntry(change.column, i, change.data);
	 		}
	 	}
	 	return M;	
	 	*/
}