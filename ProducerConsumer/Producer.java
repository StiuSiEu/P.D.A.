package pack1;


import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;

public class Producer extends Thread {
	
	Semaphore semaphoreProducer;
	Semaphore semaphoreConsumer;
	int nr;
	int min=0;
	int max=99;
	List<Integer> list;
	public Producer(Semaphore semaphoreProducer,Semaphore semaphoreConsumer,List<Integer> list,int nr)
	{
		  this.semaphoreProducer=semaphoreProducer;
          this.semaphoreConsumer=semaphoreConsumer;
          this.list=list;
          this.nr=nr;
	}
	
	@Override
	public void run() {
		for(int i=1;i<=nr;i++)
		{
			try
			{
				semaphoreProducer.acquire();
				int randomNum = ThreadLocalRandom.current().nextInt(min, max + 1);
				System.out.println("Produced : "+randomNum);
				list.add(randomNum);
				semaphoreConsumer.release();
				Thread.sleep(1500);
			}
			catch(InterruptedException e)
			{
				e.printStackTrace();
			}
		}
		
	}

}
