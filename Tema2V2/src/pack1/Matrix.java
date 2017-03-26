package pack1;

import java.util.Random;

public class Matrix {
	public int row,col,size;
	public int[][] M;
	Random r=new Random();
	
	Matrix(int a, int b)
	{
		this.row=a;
		this.col=b;
		this.size=a*b;
		M=new int[row][col];
		
	}
	
	public void generateMatrix()
	{
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				this.M[i][j]=r.nextInt(10);
			}
				
		}
	}
	public void generateEmptyMatrix()
	{
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				this.M[i][j]=0;
			}
				
		}
	}
	
	public int getRow() {
		return row;
	}
	public int getCol() {
		return col;
	}
	public int getSize() {
		return size;
	}
	
	public int getElement(int line, int row)
	{
		return M[line][row];
	}
	
	public void setElement(int line, int row,int value)
	{
		M[line][row]=value;
	}
	
	public void disp()
	{
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<col;j++)
			{
				System.out.print(M[i][j]+" ");
			}
				System.out.println();
		}
	}
	
}
