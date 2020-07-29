#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

//-----------------------------------------------------------------------------
// Jeffrey Yao
// jeyao
// pa2
// 101, 4/23/19
// List.c
// A List ADT written in C
//-----------------------------------------------------------------------------



typedef struct NodeObj{	
		int data;
		struct NodeObj* next;
		struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{ // Constructor, creates a new empty list.
	int	numElements;
	Node front;
	Node back;
	Node cursor;
	int	index;
} ListObj;

Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
} 

void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

List newList(void){
	List L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->numElements = 0;
	L->index = -1;
	return(L);
}

void freeList(List* pL){
    if(pL != NULL && *pL != NULL) { 
        while(length(*pL) > 0){
      	deleteFront(*pL);
    }
    free(*pL);
    *pL = NULL;
   }
}

//access functions

int length(List L){ // Returns the number of elements in this List.
	return L->numElements;
} 

int index(List L){  // If cursor is defined, returns the index of the cursor element, otherwise returns -1.
	if(L->cursor != NULL){
		return L->index;
	}else{
		return -1;
	}
} 

int front(List L){ // Returns front element. Pre: length()>0
	if(length(L) > 0){
		return L->front->data;
	}else{
		return -1;
	}
} 
	
int back(List L){ // Returns back element. Pre: length()>0
	if(length(L) > 0){	
		return L->back->data;
	}else{
		return -1;
	}
} 

int get(List L){ // Returns cursor element. Pre: length()>0, index()>=0
	if(length(L) > 0 && index(L) >= 0){
		return L->cursor->data;
	}else{
		return -1;
	}
} 

	
int equals(List X, List Y){ // Returns true if and only if this List and L are the same integer sequence. The states of the cursors in the two Lists are not used in determining equality.
	if(X->numElements != Y->numElements){
		return 0;
	}
	Node A = X->front;
	Node B = Y->front;
	int isequal = 0;
	if(X->numElements == 0 && Y->numElements == 0){
		isequal = 1;
	}else{
		while(A != NULL){
			if(A->data == B->data){
				isequal = 1;
			}else{
				isequal = 0;
			}
			A = A->next;
			B = B->next;
		}
	}
	return isequal;
} 

// Manipulation procedures
	
void clear(List L){ // Resets this List to its original empty state.
	//for(int i = 0; i < numElements; i++){
	//	freeNode(&)
	//}//free every node
	L->front = NULL;
	L->back = NULL;
	L->numElements = 0;
	L->cursor = NULL;
	L->index = -1;
}
	
void moveFront(List L){ // If List is non-empty, places the cursor under the front element, otherwise does nothing.
	if(length(L) > 0){
		L->cursor = L->front;
		L->index = 0;
	}
}
	
void moveBack(List L) { // If List is non-empty, places the cursor under the back element, otherwise does nothing.
	if(length(L) > 0){
		L->cursor = L->back;
		L->index = length(L)-1;
	}
}
		
void movePrev(List L) { // If cursor is defined and not at front, moves cursor one step toward front of this List, if cursor is defined and at front, cursor becomes undefined, if cursor is undefined does nothing.
	if(L->cursor != NULL && L->cursor != L->front){
		L->cursor = L->cursor->prev;
		L->index--;
	}else if(L->cursor != NULL && L->cursor == L->front){
		L->cursor = NULL;
		L->index = -1;
	}else if(L->cursor == NULL){
		return;
	}
}
		
void moveNext(List L){ // If cursor is defined and not at back, moves cursor one step toward back of this List, if cursor is defined and at back, cursor becomes undefined, if cursor is undefined does nothing.
	if(L->cursor != NULL && L->cursor != L->back){
		L->cursor = L->cursor->next;
		L->index++;
	}else if(L->cursor != NULL && L->cursor == L->back){
		L->cursor = NULL;
		L->index = -1;
	}if(L->cursor == NULL){
		return;
	}
} 
	// condition to check whether cursor exists
	// if it exists, increment index
	// else does nothing
		
void prepend(List L, int data){ // Insert new element into this List. If List is non-empty, insertion takes place before front element.
	Node N = newNode(data);
	if(length(L) > 0){
       	N->next = L->front;
       	N->prev = NULL;
       	L->front->prev = N;
      	L->front = N;
       	L->numElements++;
       	if(L->cursor != NULL){
       		L->index++;
       	}
   	}else if(length(L) == 0){
       	L->front = N;
       	L->back = N;
       	L->numElements++;
        	//index++;
   	}
} 
	
void append(List L, int data){  // Insert new element into this List. If List is non-empty, insertion takes place after back element.
	Node N = newNode(data);
	if(length(L) > 0){
       	N->prev = L->back;
       	N->next = NULL;
       	L->back->next = N;
       	L->back = N;
       	L->numElements++;
   	}else if(length(L) == 0){
       	L->back = N;
       	L->front = N;
       	L->numElements++;
         	// this is wrong~
         	//index++;
   	}
}
		
void insertBefore(List L, int data){ // Insert new element before cursor. Pre: length()>0, index()>=0
	// throw error instead of return
	if(length(L) <= 0){
		printf("Error: List is empty");
		exit(1);
	}else if(index(L) < 0){
		printf("Error: List is empty");
		exit(1);
	}

	if(index(L) == 0){
		prepend(L, data);
	}else{
		Node N = newNode(data);
		N->next = L->cursor;
		N->prev = L->cursor->prev;
		L->cursor->prev->next = N;
		L->cursor->prev = N;
		L->numElements++;
		L->index++;
	}
} 
		
void insertAfter(List L, int data){ // Inserts new element after cursor. Pre: length()>0, index()>=0
	// throw error~
	if(length(L) <= 0){
		printf("Error: List is empty");
		exit(1);
	}else if(index(L) < 0){
		printf("Error: List is empty");
		exit(1);
	}

	if(length(L) == 0){
		append(L, data);
	}else{
		Node N = newNode(data);
		N->next = L->cursor->next;
		N->prev = L->cursor;
		L->cursor->next = N;
		L->cursor->next->prev = N;
		L->numElements++;
		if(L->back == L->cursor){
			L->back = L->cursor->next;
			L->back->prev = L->cursor;
		}
	}
} 

void deleteFront(List L){ // Deletes the front element. Pre: length()>0
	Node N = NULL;
	N = L->front;
	if(length(L) < 0){
		return;
	}else if(length(L) == 1){
		clear(L);
		return;
	}
	if(length(L) > 0){
		L->front = L->front->next;
		L->front->prev = NULL;
		L->numElements--;
		L->index--;
	}
	freeNode(&N);
} 
	
void deleteBack(List L){ // Deletes the back element. Pre: length()>0
	Node N = NULL;
	N = L->back;
	if(length(L) < 0){
		return;
	}else if(length(L) == 1){
		clear(L);
		return;
	}
	if(length(L) > 0){
		if(L->cursor == L->back){
			L->cursor = NULL;
		}
		L->back = L->back->prev;
		L->back->next = NULL;
		L->numElements--;
	}
	freeNode(&N);
}

void delete(List L){// Deletes cursor element, making cursor undefined. Pre: length()>0, index()>=0
	if(length(L) < 0){
		return;
	}
	// you should have two conditions
	// call deletefront and return if index/cursor at 0/front
	// call deleteback and return if index/cursor at length-1/back
	if(index(L) == 0){
		deleteFront(L);
		L->index = -1;
		return;
	}else if(index(L) == L->numElements - 1){
		deleteBack(L);
		L->index = -1;
		return;
	}
	else{
		Node N = NULL;
		N = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		freeNode(&N);
		L->cursor = NULL;
		L->index = -1;
	}
	/*
	else if(length() > 0 && index() >= 0){
		if(cursor != null){
			cursor.prev.next = cursor.next;
			cursor.next.prev = cursor.prev;
			// you might need this?
			cursor = null;
		}
	}
	*/
	L->numElements--;	
} 

// Other methods

void printList(FILE* out, List L){ // prints the L to the file pointed to by out, formatted as a space-separated string.
	Node N = L->front;
	while( N != NULL){
		fprintf(out, "%d ", N->data);
		N = N->next;
	}
}

List copyList(List L){  // Returns a new List representing the same integer sequence as this List. The cursor in the new list is undefined, regardless of the state of the cursor in this List. This List is unchanged.
	List C = newList();
	Node copy = L->front;
	while(copy != NULL){
		append(C, copy->data);
		copy = copy->next;
	}
	return C;
}
