package pack1;

import java.util.List;
import java.util.concurrent.Semaphore;


public class Consumer extends Thread {

	Semaphore semaphoreProducer;
	Semaphore semaphoreConsumer;
	int nr;
	List<Integer> list;
		
	public Consumer(Semaphore semaphoreConsumer,Semaphore semaphoreProducer,List<Integer> list,int nr)
	{ 
		this.semaphoreConsumer=semaphoreConsumer;
		this.semaphoreProducer=semaphoreProducer;
		this.list=list;
		this.nr=nr;
	}
	@Override
	public void run() {
		for(int i=1;i<=nr;i++)
		{
			try
			{
				semaphoreConsumer.acquire();
				System.out.println("Consumed : "+ list.get(list.size() - 1));
				list.remove(list.size() - 1);
				semaphoreProducer.release();
				Thread.sleep(1000);
				
			}
			catch(InterruptedException e)
			{
				e.printStackTrace();
			}
		}
	}

}
