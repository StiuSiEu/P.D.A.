import java.util.Random;

public class ProducerConsumerTest {
	public static void main(String[] args) {
		CubbyHole c = new CubbyHole();
		Producer p1 = new Producer(c, 1);
		Consumer c1 = new Consumer(c, 1);
		p1.start();
		c1.start();
	}
}

class CubbyHole {
	private int contents;
	private boolean available = false;

	public synchronized int get() {
		while (available == false) {
			try {
				wait();
			} catch (InterruptedException e) {
			}
		}
		available = false;
		notifyAll();
		return contents;
	}

	public synchronized void put(int value) {
		while (available == true) {
			try {
				wait();
			} catch (InterruptedException e) {
			}
		}
		contents = value;
		available = true;
		notifyAll();
	}
}

class Consumer extends Thread {
	private CubbyHole cubbyhole;
	private int number;

	public Consumer(CubbyHole c, int number) {
		cubbyhole = c;
		this.number = number;
	}

	public void run() {
		Lapte obj = new Lapte();
		obj.addProducts();
		int value = 0;
		for (int i = 0; i < 10; i++) {
			value = cubbyhole.get();
			System.out.println("Consumer no." + i + " consumed: " + obj.lapte.get(value));
		}
	}
}

class Producer extends Thread {
	private CubbyHole cubbyhole;
	private int number;

	public Producer(CubbyHole c, int number) {
		cubbyhole = c;
		this.number = number;
	}

	public void run() {
		Random rand =  new Random();
		int randomNumber;
		Lapte obj = new Lapte();
		obj.addProducts();
		
		for (int i = 0; i < 10; i++) {
			randomNumber = rand.nextInt(4);
			cubbyhole.put(randomNumber);
			System.out.println("Producer no." + i + " prodduced: " + obj.lapte.get(randomNumber));
			try {
				sleep((int) (Math.random() * 100));
			} catch (InterruptedException e) {
			}
		}
	}
}