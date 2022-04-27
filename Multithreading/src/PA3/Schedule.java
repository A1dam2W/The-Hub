package PA3;

import java.util.List;

public class Schedule {

    /** 
     * Stock Trades Schedule 
     * Keep the track of tasks
    */
    public Schedule(List<Task> data) {
        this.data = data;
    }
    
    public Schedule() {
    }

	private List<Task> data = null;

    public List<Task> getData() {
    return data;
    }

    public void setData(List<Task> data) {
    this.data = data;
    }
    public Task getDataByIndex(int num) {
    	return data.get(num);
    }


    /**
     * Inner class to store task object
     */

    public static class Task {
    	private int initiate;
    	private String ticker;
    	private int stocks_traded;
        public Task(int initiate, String ticker, int stocks_traded) {
        	this.initiate = initiate;
        	this.ticker = ticker;
        	this.stocks_traded = stocks_traded;
        }
    	public String getTicker() {
    		return ticker;
    	}
    		
    	public void setTicker(String ticker) {
    		this.ticker = ticker;
    	}
    	
    	public int getInitiate() {
    		return initiate;
    	}
    	public void setInitiate(int initiate) {
    		this.initiate = initiate;
    	}
    	
    	public int getStocksTraded() {
    		return stocks_traded;
    	}
    	public void setStocksTraded(int stocks_traded) {
    		this.stocks_traded = stocks_traded;
    	}
    }
    
}
