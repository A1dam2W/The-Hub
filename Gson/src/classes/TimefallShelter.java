package classes;
import java.io.FileNotFoundException;
import java.util.Collections;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class TimefallShelter implements Comparable<TimefallShelter> {
	/**
	 * Here: all the needed class members and their getters and setters
	 */
	@SerializedName("chiralFrequency")
	@Expose
	private Integer chiralFrequency;
	@SerializedName("timefall")
	@Expose
	private Boolean timefall;
	@SerializedName("guid")
	@Expose
	private String guid;
	@SerializedName("name")
	@Expose
	private String name;
	@SerializedName("phone")
	@Expose
	private String phone;
	@SerializedName("address")
	@Expose
	private String address;

	public TimefallShelter() {}

	public TimefallShelter(Integer chiralFrequency, Boolean timefall, String guid, String name, String phone, String address) {
		this.chiralFrequency =chiralFrequency;
		this.timefall = timefall;
		this.guid = guid;
		this.name = name;
		this.phone = phone;
		this.address = address;
	}
		

	public Integer getChiralFrequency() {
	return chiralFrequency;
	}

	public void setChiralFrequency(Integer chiralFrequency) {
	this.chiralFrequency = chiralFrequency;
	}

	public Boolean getTimefall() {
	return timefall;
	}
	
	public String PrettyprintTimefall() {
		if(this.timefall == true) {
			return "Current";
		}
		return "None";
	}

	public void setTimefall(Boolean timefall) {
	this.timefall = timefall;
	}

	public String getGuid() {
	return guid;
	}

	public void setGuid(String guid) {
	this.guid = guid;
	}

	public String getName() {
	return name;
	}

	public void setName(String name) {
	this.name = name;
	}

	public String getPhone() {
	return phone;
	}

	public void setPhone(String phone) {
	this.phone = phone;
	}

	public String getAddress() {
	return address;
	}

	public void setAddress(String address) {
	this.address = address;
	}
	/**
	 * overriding comparator for sorting
	 */

	@Override
	public int compareTo(TimefallShelter compShelter) {
		/* For Ascending order*/
		return this.getChiralFrequency() - compShelter.getChiralFrequency();
	}

	/**
	 * String representation of a shelter
	 */
	@Override
	public String toString() {
		return "Shelter information:\n"
				+ "- Chiral frequency: " + this.getChiralFrequency() +"\n"
				+ "- Timefall: " + this.PrettyprintTimefall() + "\n"
				+ "- GUID: " + this.getGuid() + "\n"
				+ "- Name: " + this.getName() + "\n"
				+ "- Phone: " + this.getPhone() + "\n"
				+ "- Address: " + this.getAddress() + "\n";
	}
}
