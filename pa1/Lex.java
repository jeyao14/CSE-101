import java.io.*;
import java.util.Scanner;

public class Lex{

	public static void main(String[] args) throws IOException{
		if(args.length != 2){
			System.err.println("Usage: Lex <input> <output>");
			System.exit(1);
		}

		Scanner in = null;
      	PrintWriter out = null;
      	String line = null;
      	
      	int lineNumber = 0;
      
	    in = new Scanner(new File(args[0]));
	    out = new PrintWriter(new FileWriter(args[1]));

	    while(in.hasNextLine()){
	        lineNumber++;
	        in.nextLine();
	    }
	    in.close();
	    in = new Scanner(new File(args[0]));
	    String[] input = new String[lineNumber];

	    for(int i = 0; i < lineNumber; i++){
	    	input[i] = in.nextLine();
	    }

	    in.close();

	    List L = new List();
	    L = indexSort(input, L);

	    L.moveFront();
		for(int i = 0; i < lineNumber;  i++){
			out.println(input[L.get()]);
			L.moveNext();
		}
	    out.close();
	}

	public static List indexSort(String[] input, List output){
		output.append(0);
		//System.out.println(output.get()+ " " + output.length()+" "+output.index());
	    for(int j = 1; j < input.length; j++){
	    	output.moveFront();
	    	while(output.index() >= 0){
	    		//System.out.println(output.get()+ " " + output.length()+" "+output.index());
	    		if(input[j].compareTo(input[output.get()]) < 0){
	    			output.insertBefore(j);
	    			break;
	    			//System.out.println(output.length());
	    		}
	    		//System.out.println("moved " + output.index());
	    		output.moveNext();
	    	}
	    	if(output.index() < 0){
	    		output.append(j);
	    	}
	    }
	    return output;
	}	
}