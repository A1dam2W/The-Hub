package PA3;

import java.util.concurrent.Semaphore;

public class Datum {

	private String name;	
	private String ticker;	
	private String startDate;	
	private Integer stockBrokers;
	private String description;	
	private String exchangeCode;
	
	private transient Semaphore semaphore;

	public String getName() {
	return name;
	}
	
	public void setName(String name) {
	this.name = name;
	}
	
	public Semaphore getSemaphore() {
	return semaphore;
	}
	
	public void setSemaphore(Semaphore semaphore) {
	this.semaphore = semaphore;
	}
	
	public String getTicker() {
	return ticker;
	}
	
	public void setTicker(String ticker) {
	this.ticker = ticker;
	}
	
	public String getStartDate() {
	return startDate;
	}
	
	public void setStartDate(String startDate) {
	this.startDate = startDate;
	}
	
	public Integer getStockBrokers() {
	return stockBrokers;
	}
	
	public void setStockBrokers(Integer stockBrokers) {
	this.stockBrokers = stockBrokers;
	}
	
	public String getDescription() {
	return description;
	}
	
	public void setDescription(String description) {
	this.description = description;
	}
	
	public String getExchangeCode() {
	return exchangeCode;
	}
	
	public void setExchangeCode(String exchangeCode) {
	this.exchangeCode = exchangeCode;
	}

}
