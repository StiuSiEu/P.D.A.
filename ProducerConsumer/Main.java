package pack1;
import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.Semaphore;



public class Main {
	
	static List<Integer> list= new ArrayList<Integer>();
	static Semaphore producer = new Semaphore(1);
    static Semaphore consumer = new Semaphore(0);
	public static void main(String[] args) {
		int n=8;  
		
	    Producer prod=new Producer(producer,consumer,list,n);
	    Consumer cons=new Consumer(consumer,producer,list,n);
	    
	    prod.start();
	    cons.start();
		
	}

}
