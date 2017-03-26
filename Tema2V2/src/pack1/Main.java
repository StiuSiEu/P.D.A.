package pack1;

public class Main {
	
  
	public static void main(String[] args) {
	int threadcount = 0;   
	int row;
    int col;
    
    Matrix A=new Matrix(2,3);
    A.generateMatrix();	
    Matrix B=new Matrix(3,2);
    B.generateMatrix();	
    int NUM_OF_THREADS = A.getRow()*B.getCol();
    Thread[] thrd = new Thread[NUM_OF_THREADS];
    
    Matrix C=new Matrix(A.getRow(),B.getCol());
    C.generateEmptyMatrix();
    
    try
    {
	    for(row = 0 ; row < A.getRow(); row++)
	    {
	         for (col = 0 ; col < B.getCol(); col++ )
	         {
	                 // creating thread for multiplications
	              thrd[threadcount] = new Thread(new Multiply(row, col, A, B, C));
	              thrd[threadcount].run(); //thread start
	             
	              threadcount++;
	         }
	        
	         
	    }
	    
	    for(int i=0;i<NUM_OF_THREADS;i++)
	    {
	    	thrd[i].join(); 
	    	
	    }
    }
    catch (InterruptedException ie){}
    
    A.disp();
    System.out.println("\nX\n");
    B.disp();
    System.out.println("\n=\n");
    System.out.println("C Matrix : ");
    C.disp();
	
		
	}

}
