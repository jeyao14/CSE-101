import java.io.*;
import java.util.Scanner;

public class Sparse{

	public static void main(String[] args) throws IOException{
		if(args.length != 2){
			System.err.println("Usage: Sparse <input> <output>");
			System.exit(1);
		}

		Scanner in =  new Scanner(new File(args[0]));
      	PrintWriter out = new PrintWriter(new FileWriter(args[1]));
		int size = in.nextInt();
		Matrix A = new Matrix(size+1);
		Matrix B = new Matrix(size+1);
      	int aNNZ = in.nextInt();
      	//System.out.println(aNNZ);
      	int bNNZ = in.nextInt();
      	//System.out.println(bNNZ);
      	int row, column;
      	double data;

      	//in.nextLine();

	    //while(in.hasNext()){
      	for(int i = 0; i < aNNZ; i++){
	    	row = in.nextInt();
	    	column = in.nextInt();
	    	data = in.nextDouble();
	    	//System.out.println(row + " " + column + " " + data);
	    	A.changeEntry(row, column, data);
	    	//System.out.println(A);
	        //in.nextLine();
	    }

	    //while(in.hasNext()){
	    for(int i = 0; i < bNNZ; i++){
	    	row = in.nextInt();
	    	column = in.nextInt();
	    	data = in.nextDouble();
	    	//System.out.println(row + " " + column + " " + data);
	    	B.changeEntry(row, column, data);
	    	//System.out.println(B);
	        //in.nextLine();
	    }

	    /*System.out.println(A);
	    System.out.println(B);
	    System.out.println(A.equals(B));*/

	    out.println("A has " + aNNZ + " non-zero entries:");
	    out.println(A + "\n");

	    out.println("B has " + bNNZ + " non-zero entries:");
	    out.println(B + "\n");

	    //1.5 * A
	    out.println("(1.5)*A = ");
	    out.println(A.scalarMult(1.5) + "\n");

	    //A+B
	    out.println("A+B = ");
	    out.println(A.add(B) + "\n");

	    //A+A
	    out.println("A+A = ");
	    out.println(A.add(A) + "\n");

	    //out.println(A.equals(B));

	    //B-A
	    out.println("B-A = ");
	    out.println(B.sub(A) + "\n");

	    //A-A
	    out.println("A-A = ");
	    out.println(A.sub(A) + "\n");

	    //Transpose(A)

	    out.println("Transpose(A) = ");
	    out.println(A.transpose() + "\n");

	    //A*B
	    out.println("A*B = ");
	    out.println(A.mult(B) + "\n");

	    //B*B
	    out.println("B*B = ");
	    out.println(B.mult(B) + "\n");

	    in.close();
	    out.close();
	}
}
