
class Matrix{

	private class Entry{
		double data;
		int column;

		Entry(double data, int column){
			this.data = data;
			this.column = column;
		}

		public boolean equals(Object x){ // overrides Object's equals() method
			boolean equals = false;
			Entry that;
			if(x instanceof Entry){
				that = (Entry) x;
				equals = (this.data == that.data);
			}
			return equals;
		} 

		public String toString(){
			return ("(" + column + ", " + data + ")");
		}
	}

	private int size;
	private int NNZ;
	private List[] row;

	Matrix(int n){ // Makes a new n x n zero Matrix. pre: n>=1
		size = n;
		NNZ = 0;
		row = new List[size +1];
		for(int i = 0; i < size + 1; i++){
			row[i] = new List();
		}
	} 

	// Access functions
	int getSize(){ // Returns n, the number of rows and columns of this Matrix
		return size;
	} 

	int getNNZ(){ // Returns the number of non-zero entries in this Matrix
		return NNZ;
	} 


	// Manipulation procedures

	void makeZero(){ // sets this Matrix to the zero state
		for(int i = 0; i < getSize() + 1; i++){
			row[i].clear();
		}
		NNZ = 0;
	}

	Matrix copy(){ // returns a new Matrix having the same entries as this Matrix
		/*int copysize = this.getSize();
		Matrix M = new Matrix(copysize);
		for(int i = 0; i < copysize +1; i++){
			M.row[i] = row[i].copy();
		}
		M.NNZ = NNZ;
		return M;*/
		Matrix M = new Matrix(getSize());
		for(int i = 1; i < this.getSize()+1; i++){
			for(row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()){
				Entry copied = (Entry) row[i].get();
				M.changeEntry(i, copied.column, copied.data);
			}
		}
		return M;
	}

	public boolean equals(Object x){
		boolean isequals = false;
		if(x instanceof Matrix){
			Matrix M = (Matrix) x;
			if(M.getSize() != this.getSize()){
				return false;
			}else if(M.getNNZ() != this.getNNZ()){
				return false;
			}else{
				for(int i = 0; i < this.getSize()+1; i++){
					if(row[i].equals(M.row[i])){
						isequals = true;
					}
				}
			}
		}
		return isequals;
	}	
	
	// changes ith row, jth column of this Matrix to x
	 // pre: 1<=i<=getSize(), 1<=j<=getSize()

	void changeEntry(int i, int j, double x){
		if(1 > i && i > getSize()){
			throw new RuntimeException("Error: calling changeEntry() on invalid row");
		}
		if(1 > j && j > getSize()){
			throw new RuntimeException("Error: calling changeEntry() on invalid column");
		}


		Entry newEntry = new Entry(x, j);
		boolean inserted = false;
		if(x == 0){ //if x is zero
			if(row[i].length() > 0){
				for(row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()){
					Entry oldEntry = (Entry) row[i].get();
					if(oldEntry.column == j && (int) oldEntry.data != 0){ //if old entry is non-zero
						row[i].delete();
						NNZ--;
						break;
					}else if(oldEntry.column == j && (int) oldEntry.data == 0){ //if old entry is zero
						break;
					}
				}
			}
		}else{ // if x is non-zero
			if(row[i].length() > 0){ //if row is not empty
					for(row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()){
						Entry oldEntry = (Entry) row[i].get();
						//Entry nextEntry = (Entry) row[i+1].get();
						if(oldEntry.column == newEntry.column){ // if entry to be replaced exists
							((Entry) row[i].get()).data = newEntry.data;
							inserted = true;
							//row[i].delete();
						/*}else if(oldEntry.column < newEntry.column){ //if entry do be replaced doesn't exist
							row[i].insertAfter(newEntry);
							NNZ++;
							inserted = true;
							Entry backEntry = (Entry) row[i].back();
							if(backEntry.column < newEntry.column){ //if new entry will be last in list
								row[i].append(newEntry);
								NNZ++;
								//break;
							}else if(backEntry.column > newEntry.column){ //if new entry is not last in list
								row[i].insertAfter(newEntry);
								NNZ++;
								//break;
							} */
						}else if(oldEntry.column > newEntry.column){
							row[i].insertBefore(newEntry);
							NNZ++;
							inserted = true;
							//break;
						}
						if(inserted == true){
							break;
						}
					}
					if(inserted == false){
						row[i].append(newEntry);
						NNZ++;
					}
					/*for(row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()){
						Entry oldEntry = (Entry) row[i].get();
						Entry backEntry = (Entry) row[i].back();
						if(oldEntry.column > newEntry.column){
							row[i].insertBefore(newEntry);
							break;
						}
						if(backEntry.column < newEntry.column && oldEntry.column < newEntry.column){
							row[i].append(newEntry);
							break;
						}
					}*/
			}else{ //if row is empty
				row[i].prepend(newEntry);
				NNZ++;
			}
		}
	}
	 

	Matrix scalarMult(double x){ // returns a new Matrix that is the scalar product of this Matrix with x
		Matrix M = new Matrix(this.getSize());
		Entry product;
		for(int i = 0; i < this.getSize()+1; i++){
			for(row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()){
				product = (Entry) row[i].get();
				M.changeEntry(i, product.column, product.data * x);
			}
		}
		return M;
	}
	 
	 // returns a new Matrix that is the sum of this Matrix with M
	 // pre: getSize()==M.getSize()

	Matrix add(Matrix M){
		if(this.getSize() != M.getSize()){
			throw new RuntimeException("Error: called add() on matrices of different sizes");
		}
		if(M.getNNZ() == 0){
			return copy();
		}
		if(equals(M)){
			return this.scalarMult(2);
		}
		Matrix sum = new Matrix(getSize());
		for(int i = 1; i < getSize()+1; i++){
			row[i].moveFront();
			M.row[i].moveFront();
			while(row[i].index() >= 0 || M.row[i].index() >= 0){ 
				if(row[i].index() >= 0 && M.row[i].index() >= 0){ //if both rows contains values
					Entry a = (Entry) row[i].get();
					Entry b = (Entry) M.row[i].get();
					if(a.column == b.column){ // if both entries are non-zero
						if(a.data + b.data != 0){
							sum.row[i].append(new Entry((a.data + b.data), a.column));
							sum.NNZ++;
						}	
						row[i].moveNext();
						M.row[i].moveNext();
					}else if(a.column < b.column){ //if first entry is non-zero and second is zero
						sum.row[i].append(new Entry(a.data, a.column));
						sum.NNZ++;
						row[i].moveNext();
					}else{ //if second entry is non-zero and first is zero
						sum.row[i].append(new Entry(b.data, b.column));
						sum.NNZ++;
						M.row[i].moveNext();
					}
				}else if(row[i].index() >= 0 && M.row[i].index() == -1){ //if only the first row contains values
					while(row[i].index() >= 0){
						sum.row[i].append((Entry) row[i].get());
						sum.NNZ++;
						row[i].moveNext();
					}
				}else{ //if only the second row contains values
					while(M.row[i].index() >= 0){
						sum.row[i].append((Entry) M.row[i].get());
						sum.NNZ++;
						M.row[i].moveNext();
					}
				}
			}
		}
		return sum;
	}

	
	 // returns a new Matrix that is the difference of this Matrix with M
	 // pre: getSize()==M.getSize()

	Matrix sub(Matrix M){
		if(this.getSize() != M.getSize()){
			throw new RuntimeException("Error: called sub() on matrices of different sizes");
		}
		Matrix diff = new Matrix(this.getSize());
		for(int i = 1; i < getSize()+1; i++){
			row[i].moveFront();
			M.row[i].moveFront();
			while(row[i].index() >= 0 || M.row[i].index() >= 0){ 
				if(row[i].index() >= 0 && M.row[i].index() >= 0){ //if both rows contains values
					Entry a = (Entry) row[i].get();
					Entry b = (Entry) M.row[i].get();
					if(a.column == b.column){ // if both entries are non-zero
						if(a.data - b.data != 0){
							diff.row[i].append(new Entry((a.data - b.data), a.column));
							diff.NNZ++;
						}	
						row[i].moveNext();
						M.row[i].moveNext();
					}else if(a.column < b.column){ //if first entry is non-zero and second is zero
						diff.row[i].append(new Entry(a.data, a.column));
						diff.NNZ++;
						row[i].moveNext();
					}else{ //if second entry is non-zero and first is zero
						diff.row[i].append(new Entry((-1)*b.data, b.column));
						diff.NNZ++;
						M.row[i].moveNext();
					}
				}else if(row[i].index() >= 0 && M.row[i].index() == -1){ //if only the first row contains values
					while(row[i].index() >= 0){
						Entry a = (Entry) row[i].get();
						diff.row[i].append(a);
						diff.NNZ++;
						row[i].moveNext();
					}
				}else{ //if only the second row contains values
					while(M.row[i].index() >= 0){
						Entry a = (Entry) M.row[i].get();
						diff.row[i].append(new Entry((-1)*a.data, a.column));
						diff.NNZ++;
						M.row[i].moveNext();
					}
				}
			}
		}
		return diff;
	}
		

	Matrix transpose(){ // returns a new Matrix that is the transpose of this Matrix
	 	Matrix M = new Matrix(this.getSize());
	 	for(int i = 1; i < this.getSize()+1; i++){
	 		for(row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()){
	 			Entry change = (Entry) row[i].get();
	 			M.changeEntry(change.column, i, change.data);
	 		}
	 	}
	 	return M;	
	}

 	// returns a new Matrix that is the product of this Matrix with M
	 // pre: getSize()==M.getSize()
	Matrix mult(Matrix M){
		if(this.getSize() != M.getSize()){
			throw new RuntimeException("Error: called mult() on matrices of different sizes");
		}
		Matrix product = new Matrix(this.getSize());
		Matrix mtrans = M.transpose();
		double x = 0.0;
		for(int i = 1; i < this.getSize()+1; i++){
			for(int j = 1; j < mtrans.getSize()+1; j++){
				x = dot(this.row[i], mtrans.row[j]);
				product.changeEntry(i, j, x);
			}
		}
		return product;
	}
	
	// Other functions
	public String toString(){ // overrides Object's toString() method
		String s = "";
		for(int i = 0; i < size; i++){
			if(row[i].length() > 0){
				s += String.valueOf(i) + ": " + row[i] + "\n";
			}
		}
		return s;
	} 

	private static double dot(List P, List Q){
		double dotproduct = 0.0;
		if(P.length() == 0 || Q.length() == 0){
			return dotproduct;
		}else{
			for(P.moveFront(); P.index() >= 0; P.moveNext()){
				Entry Pval = (Entry) P.get();
				for(Q.moveFront(); Q.index() >= 0; Q.moveNext()){
					Entry Qval = (Entry) Q.get();
					if(Pval.column == Qval.column){
						dotproduct += (Pval.data * Qval.data);
						break;
					}
				}
			}
		}
		return dotproduct;	
	}
}


