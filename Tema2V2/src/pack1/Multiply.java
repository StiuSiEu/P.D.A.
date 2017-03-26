package pack1;

public class Multiply extends Thread
{
	private int row;
	private int col;
	private Matrix A;
	private Matrix B;
	private Matrix C;
	
	public Multiply(int row, int col, Matrix A, Matrix B, Matrix C)
	{
		this.row = row;
        this.col = col;
        this.A = A;
        this.B = B;
        this.C = C;
	}
	
	public void run()
	{	
		int value=0;
		 for(int k = 0; k < B.row; k++)
         {
			 value= value+ A.getElement(row,k) * B.getElement(k,col);
         }
		 C.setElement(row,col, value);
	}
}

