package PA3;

import java.util.concurrent.*;

import PA3.Schedule.Task;

public class Trade extends Thread {
	private Semaphore semaphore;
	private Schedule schedule;
	private Stock stock;
	private Datum datum;
	private Task task;
	public Trade(Semaphore semaphore, Datum datum, Task task) {
		this.semaphore = semaphore;
		this.task = task;
		this.datum = datum;
    }
	
	public Task getTask() {
		return this.task;
	}
	
	public int getStartTime() {
		return this.task.getInitiate();
	}
	
	/**
	 * Trading function using locks
	 */
	public void run() {
		try {
			semaphore.acquire();
			if(task.getStocksTraded() > 0) {
				System.out.println("[" + Utility.getZeroTimestamp() + "]" + "Starting purchase of " 
			+ Math.abs(task.getStocksTraded()) + " stocks of " + task.getTicker());
			} else {
				System.out.println("[" + Utility.getZeroTimestamp() + "]" + "Starting sale of " 
			+ Math.abs(task.getStocksTraded()) + " stocks of " + task.getTicker());
			}
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			if(task.getStocksTraded() > 0) {
				System.out.println("[" + Utility.getZeroTimestamp() + "]" + "Finished purchase of " 
			+ Math.abs(task.getStocksTraded()) + " stocks of " + task.getTicker());
			} else {
				System.out.println("[" + Utility.getZeroTimestamp() + "]" + "Finished sale of " 
			+ Math.abs(task.getStocksTraded()) + " stocks of " + task.getTicker());
			}
			semaphore.release();
		}

	}
}
