//-----------------------------------------------------------------------------
// Jeffrey Yao
// jeyao
// pa4
// 101, 5/29/19
// Graph.h
// Header file for the Graph ADT
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"

#define UNDEF -1
#define NIL 0

/*** Constructors-Destructors ***/
typedef struct GraphObj* Graph;

Graph newGraph(int n);

void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void DFS(Graph G, List s);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);

Graph copyGraph(Graph G);

Graph transpose(Graph G);


#endif