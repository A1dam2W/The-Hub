package PA3;

import java.io.*;

import java.util.*;
import java.util.concurrent.*;

import com.google.gson.Gson;
import com.google.gson.JsonParseException;

import PA3.Schedule.Task;

public class PA3 {
		
	static Schedule schedule = new Schedule();
	static List<Trade> trades = new ArrayList<Trade>();
	static Stock stock = new Stock();
	static List<Task> tasks = new ArrayList<Task>();
     /**
      * Read Stock Json File inputed by user using GSON
     * @throws FileNotFoundException 
      */
    private static void readStockFile() {
    	String filename = "";
    	String temp = "";
    	Scanner userinput = new Scanner(System.in);
    	while(true) {
			System.out.println("What is the name of the file containing the company information?");
			filename = userinput.nextLine().strip();
			try {
			if(!filename.endsWith(".json")) {//found the .csv file instead
				throw new IllegalArgumentException();
			}
			File file = new File(filename);
			Scanner sc = new Scanner(file);
			while(sc.hasNext()) {
				temp += sc.nextLine();
			}//load the JSON file into a string object
	    	Gson gson = new Gson();
	    	stock = gson.fromJson(temp, Stock.class);
	    	for(int i = 0; i < stock.getData().size(); i++) {
	    		if(stock.getDataByIndex(i).getStockBrokers() < 1) {
	    			throw new IllegalStateException();
	    		}
	    	}
	    	break;
	    	} catch (FileNotFoundException e) {
	            System.out.println("json File not found, please enter a valid file!");
	        } catch (IllegalArgumentException e) {
	            System.out.println("Please enter a .json file!");
	        } catch (JsonParseException e) {
	        	System.out.println("invalid .json file!");
	        } catch (IllegalStateException e) {
	            System.out.println("Number of stockbrokers less than one, please enter valid number of stockbrokers!");
	        }
		}
//    	System.out.println(stock.getDataByIndex(0).getStockBrokers()); 
    }

    /**
     * Read Stock Trades CSV File inputed by user
     * @throws FileNotFoundException 
     */
	private static void readScheduleFile(){
    	String filename = "";   	
    	Scanner userinput = new Scanner(System.in);
    	while(true) {
			System.out.println("What is the name of the file containing the schedule information?");
			filename = userinput.nextLine().strip();
			try {
			if(!filename.endsWith(".csv")) { //found the json file instead
				throw new RuntimeException();
			}
	    	File file = new File(filename);
			Scanner sc = new Scanner(file);
			while(sc.hasNextLine()) {
				String toBeParse = sc.nextLine();
				String [] parsed = toBeParse.split(",");
				int temp_second = Integer.parseInt(parsed[0].replaceAll("\\D", ""));
				String temp_ticker = parsed[1];
				int temp_stockstraded = Integer.parseInt(parsed[2].replaceAll("\\D", ""));
				if(parsed[2].contains("-")) {
					temp_stockstraded = -1 * temp_stockstraded;
				}
				Task temp_task = new Task(temp_second,temp_ticker,temp_stockstraded);
				tasks.add(temp_task);
	//			System.out.println(temp_stockstraded);
			}
			schedule = new Schedule(tasks);	
			break;
			} catch (RuntimeException e) {
	            System.out.println("Please enter a .csv file!");
	        } catch (FileNotFoundException e) {
	            System.out.println("csv File not found, please enter a valid file!");
	        }
		}
		
    }
	
    private static void bubbleSort_time(List<Trade> trade, int n) {
    	if(n == 1) {
    		return;
    	}
    	for(int i = 0; i < n-1; i++) {
    		int len = trade.get(i).getStartTime();
    		int len_next = trade.get(i+1).getStartTime();
    		if(len > len_next) {
    			Collections.swap(trade, i, i+1);
    		}
    	}
    	bubbleSort_time(trade, n-1);
    }

    /**
     *Set up Semaphore for Stock Brokers
     */

    private static void initializeSemaphor() {
    	Set<String> tickers = new HashSet<String>();
    	Set<Semaphore> semaphores = new HashSet<Semaphore>();
    	Map<Semaphore, String> map = new HashMap<Semaphore, String>();
    	tickers.add("garbage");
    	for(int i = 0; i < schedule.getData().size(); i++) {
    		for(int j = 0; j < stock.getData().size(); j++)
    		if(schedule.getDataByIndex(i).getTicker().contentEquals(stock.getDataByIndex(j).getTicker())){
    			if(!tickers.contains(schedule.getDataByIndex(i).getTicker())){
    				tickers.add(schedule.getDataByIndex(i).getTicker());
	    			Semaphore semaphore = new Semaphore(stock.getDataByIndex(j).getStockBrokers());
//	    			System.out.println(semaphore);
	    			map.put(semaphore, schedule.getDataByIndex(i).getTicker());
	//    			System.out.println(schedule.getDataByIndex(i).getTicker());
	//    			System.out.println(stock.getDataByIndex(j).getTicker());
	    			Trade temp_trade = new Trade(semaphore, stock.getDataByIndex(j), schedule.getDataByIndex(i));
	    			trades.add(temp_trade);
	    			//TODO different semaphores
    			}
    			else {
//    				for(Trade trade: trades) {
//    					if(trade.getTask().getTicker().contentEquals(schedule.getDataByIndex(i).getTicker())) {
//    						
//    					}
//    				}
    		        for (Map.Entry<Semaphore, String> me :
    		             map.entrySet()) {
    		        	if(me.getValue().contentEquals(schedule.getDataByIndex(i).getTicker())) {
    		        		Trade temp_trade = new Trade(me.getKey(), stock.getDataByIndex(j), schedule.getDataByIndex(i));
    		        		trades.add(temp_trade);
    		        	}
//    		            System.out.print(me.getKey() + ":");
//    		            System.out.println(me.getValue());
    		        }
    				
    			}
    		}
    	}
    	bubbleSort_time(trades, trades.size());
    }
    
    private static int getCurrTime() {
        int start_second = Integer.parseInt(Utility.getZeroTimestamp().substring(6, 8));
        int start_minute = Integer.parseInt(Utility.getZeroTimestamp().substring(3, 5));
        int start_hour = Integer.parseInt(Utility.getZeroTimestamp().substring(0, 2));
        int timeInSecs = start_second + start_minute * 60 + start_hour * 3600;
        return timeInSecs;
    }
    	
    private static void executeTrades() {
        ExecutorService executor = Executors.newCachedThreadPool();
        for (int i = 0; i < trades.size(); i++) {
            int time = trades.get(i).getStartTime();
            while (!(getCurrTime() == time)) {

            }
            executor.execute(trades.get(i));
        }   
        executor.shutdown();
//        while (!executor.isShutdown()) {
        while (!executor.isTerminated()) {
            Thread.yield();
        }           
    }

    public static void main(String[] args) throws InterruptedException, FileNotFoundException {
    	PA3.readStockFile();
    	PA3.readScheduleFile();
    	System.out.println("Starting execution of program...");
    	PA3.initializeSemaphor();
    	PA3.executeTrades();
    	System.out.println("All trades completed!");
    }
}
