import java.util.EmptyStackException;

class List{ 

	private class Node{	
		Object data;
		Node next;
		Node prev;

		Node(Object data){
			this.data = data;
			next = null;
			prev = null;
		} 
	}

	private int numElements;
	private Node front;
	private Node back;
	private Node cursor;
	private int index;
	

	List(){ // Constructor, creates a new empty list.
		numElements = 0;
		front = null;
		back = null;
		cursor = null;
		index = -1;
	}
	int length(){ // Returns the number of elements in this List.
		return numElements;
	} 

	int index(){  // If cursor is defined, returns the index of the cursor element, otherwise returns -1.
		if(cursor != null){
			return index;
		}else{
			return -1;
		}
	} 

	Object front(){ // Returns front element. Pre: length()>0
		if(length() > 0){
			return front.data;
		}else{
			return -1;
		}
	} 
	
	Object back(){ // Returns back element. Pre: length()>0
		if(length() > 0){	
			return back.data;
		}else{
			return -1;
		}
	} 
	
	Object get(){ // Returns cursor element. Pre: length()>0, index()>=0
		if(length() > 0 && index() >= 0){
			return cursor.data;
		}else{
			return -1;
		}
	} 

	
	public boolean equals(List L){ // Returns true if and only if this List and L are the same integer sequence. The states of the cursors in the two Lists are not used in determining equality.
		if(length() != L.length()){
			return false;
		}
		Node A = front;
		Node B = L.front;
		boolean isequal = true;
		while(A != null){
			if(A.data == B.data){
				isequal = true;
			}else{
				isequal = false;
			}
			A = A.next;
			B = B.next;
		}
		return isequal;
	} 

	// Manipulation procedures
	
	void clear(){ // Resets this List to its original empty state.
		front = null;
		back = null;
		numElements = 0;
		cursor = null;
		index = -1;
	}
	
	void moveFront(){ // If List is non-empty, places the cursor under the front element, otherwise does nothing.
		if(length() > 0){
			cursor = front;
			index = 0;
		}
	}
	
	void moveBack() { // If List is non-empty, places the cursor under the back element, otherwise does nothing.
		if(length() > 0){
			cursor = back;
			index = numElements - 1;
		}
	}
		
	void movePrev() { // If cursor is defined and not at front, moves cursor one step toward front of this List, if cursor is defined and at front, cursor becomes undefined, if cursor is undefined does nothing.
		if(cursor != null && cursor != front){
			cursor = cursor.prev;
			index--;
		}else if(cursor != null && cursor == front){
			cursor = null;
			index = -1;
		}else if(cursor == null){
			return;
		}
	}
		
	void moveNext(){ // If cursor is defined and not at back, moves cursor one step toward back of this List, if cursor is defined and at back, cursor becomes undefined, if cursor is undefined does nothing.
		if(cursor != null && cursor != back){
			cursor = cursor.next;
			index++;
		}else if(cursor != null && cursor == back){
			cursor = null;
			index = -1;
		}if(cursor == null){
			return;
		}
	} 
	// condition to check whether cursor exists
	// if it exists, increment index
	// else does nothing
		
	void prepend(Object data){ // Insert new element into this List. If List is non-empty, insertion takes place before front element.
		Node N = new Node(data);
		if(length() > 0){
        	N.next = front;
        	front.prev = N;
        	front = N;
        	numElements++;
        	if(cursor != null){
        		index++;
        	}
      	}else if(length() == 0){
         	front = N;
         	back = N;
         	numElements++;
         	//index++;
    	}
	} 
	
	void append(Object data){  // Insert new element into this List. If List is non-empty, insertion takes place after back element.
		Node N = new Node(data);
		if(length() > 0){
        	N.prev = back;
        	back.next = N;
        	back = N;
        	numElements++;
      	}else if(length() == 0){
         	back = N;
         	front = N;
         	numElements++;
         	// this is wrong~
         	//index++;
    	}
	}
		
	void insertBefore(Object data){ // Insert new element before cursor. Pre: length()>0, index()>=0
		// throw error instead of return
		if(length() <= 0){
			throw new EmptyStackException();
		}else if(index() < 0){
			throw new EmptyStackException();
		}

		if(index() == 0){
			prepend(data);
		}else{
			Node N = new Node(data);
			N.next = cursor;
			N.prev = cursor.prev;
			cursor.prev.next = N;
			cursor.prev = N;
			numElements++;
			index++;
		}
	} 
		
	void insertAfter(Object data){ // Inserts new element after cursor. Pre: length()>0, index()>=0
		// throw error~
		if(length() <= 0){
			throw new EmptyStackException();
		}else if(index() < 0){
			throw new EmptyStackException();
		}

		if(length() == 0){
			append(data);
		}else{
			Node N = new Node(data);
			N.next = cursor.next;
			N.prev = cursor;
			cursor.next = N;
			cursor.next.prev = N;
			numElements++;
			if(back == cursor){
				back = cursor.next;
				back.prev = cursor;
			}
		}
	} 

	void deleteFront(){
		if(length() < 0){
			return;
		}else if(length() == 1){
			clear();
			return;
		}
		if(length() > 0){
			front = front.next;
			front.prev = null;
			numElements--;
			index--;
		}
	} // Deletes the front element. Pre: length()>0
	
	void deleteBack(){ // Deletes the back element. Pre: length()>0
		if(length() < 0){
			return;
		}else if(length() == 1){
			clear();
			return;
		}
		if(length() > 0){
			if(cursor == back){
				cursor = null;
			}
			back = back.prev;
			back.next = null;
			numElements--;
		}
	}
	
	void delete(){// Deletes cursor element, making cursor undefined. Pre: length()>0, index()>=0
		if(length() < 0){
			return;
		}
		// you should have two conditions
		// call deletefront and return if index/cursor at 0/front
		// call deleteback and return if index/cursor at length-1/back
		if(index() == 0){
			deleteFront();
			index = -1;
			return;
		}else if(index() == numElements - 1){
			deleteBack();
			index = -1;
			return;
		}
		else{
			cursor.prev.next = cursor.next;
			cursor.next.prev = cursor.prev;
			cursor = null;
			index = -1;
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
		numElements--;	
	} 

	// Other methods

	public String toString(){ // Overrides Object's toString method. Returns a String representation of this List consisting of a space separated sequence of integers, with front on left.
      	Node N = front;
      	String s = "";
      	while(N != null){
         	s += N.data + " ";
        	N = N.next;
      	}
      	return s;
	} 

	/* List copy(){  // Returns a new List representing the same integer sequence as this List. The cursor in the new list is undefined, regardless of the state of the cursor in this List. This List is unchanged.
		List L = new List();
		Node copy = front;
		while(copy != null){
			L.append(copy.data);
			copy = copy.next;
		}
		return L;
	}*/

}