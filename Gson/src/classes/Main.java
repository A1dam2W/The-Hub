package classes;
import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonIOException;
import com.google.gson.JsonParseException;
import com.google.gson.JsonSyntaxException;
import com.google.gson.reflect.TypeToken;

public class Main {

	/**
	 * Uses GSON to read the file inputed by the user
	 */
	private ArrayList<TimefallShelter> readFile(String temp){
		Gson gson = new Gson();
		ArrayList<TimefallShelter> shelters = gson.fromJson(temp, new TypeToken<ArrayList<TimefallShelter>>() {}.getType());
//		System.out.println(shelters);//TODO remember to remove after testing
		return shelters;		
	}


	/**
	 * Gets the supported chiral frequencies from the user
	 */
	private Set<Integer> setSupportedFrequencies() {
		boolean repeat = true;
		Set<Integer> targetset = new HashSet<Integer>();
		while(repeat) {
			Scanner get_freq = new Scanner(System.in);
			System.out.print("Please provide supported Chiral frequencies:");
			String input = get_freq.nextLine();
			if(input.equals("")) {
				continue;
			}
			String delimiters = "[ ,]+";//delimiters are commas, spaces, and getting rid of the consecutive
			String[] parse = input.split(delimiters);
			Integer[] tonum = new Integer [parse.length];
			for(int i = 0; i < parse.length; i++) {//string array to integer array
				tonum[i] = Integer.parseInt(parse[i]);
			}
			Arrays.sort(tonum);
//			int min = tonum[0];
//			int max = tonum[tonum.length-1];	
//			Integer all_available[] = new Integer[max-min+1];
//			int counter = 0; 
//			int temp_min = min;
//			while(counter < max-min+1) {
//				all_available[counter] = temp_min;			
//				temp_min++;
//				counter++;
//			}//this list all the min and max within the supported chiral frequency ranges
			targetset = new HashSet<Integer>(Arrays.asList(tonum));
//			System.out.println(targetset);
			repeat = false;
		}
		return targetset;
//		get_freq.close();
		//the integer array now is sorted from min to max
	}


	/**
	 * Prints the option menu
	 */
	private void displayOptions() {
		System.out.println(
		"\n1) List all available shelters within the min and max of supported Chiral frequencies\n"
		+ "2) Search for a shelter by Chiral frequency\n"
		+ "3) Search for a shelter by name\n"
		+ "4) Sort shelters by Chiral frequency\n"
		+ "5) Jump to a shelter with the lowest supported Chiral frequency\n"
		);
	}
    public static boolean isValidGUID(String str) {
        String regex  = "^[{]?[0-9a-fA-F]{8}"
              + "-([0-9a-fA-F]{4}-)"
              + "{3}[0-9a-fA-F]{12}[}]?$";//from https://www.geeksforgeeks.org/how-to-validate-guid-globally-unique-identifier-using-regular-expression/
        Pattern p = Pattern.compile(regex);
        if (str == null) {
            return false;
        }
        Matcher m = p.matcher(str);
        return m.matches();
    }
    
    public static boolean isValidPhone(String str) {
        String regex  = "^\\+\\d(.)*(\\(\\d{3}\\))(\\d{3})(\\-)(\\d{4})$";//from https://www.baeldung.com/java-regex-validate-phone-numbers
        Pattern p = Pattern.compile(regex);
        if (str == null) {
            return false;
        }
        Matcher m = p.matcher(str);
        return m.matches();
    }
    
    public static boolean isUniqueName(ArrayList<TimefallShelter> shelters) {
    	Set<String> unique = new HashSet<String>();
    	for(int i = 0; i < shelters.size(); i++) {
    		unique.add(shelters.get(i).getName());
    	}
    	if(shelters.size() == unique.size()) {
    		return true;
    	}
    	return false;
    }
    
    public static boolean isUniqueChiral(ArrayList<TimefallShelter> shelters) {
    	Set<Integer> unique = new HashSet<Integer>();
    	for(int i = 0; i < shelters.size(); i++) {
    		unique.add(shelters.get(i).getChiralFrequency());
    	}
    	if(shelters.size() == unique.size()) {
    		return true;
    	}
    	return false;
    }
    
    public static boolean isUniqueGUID(ArrayList<TimefallShelter> shelters) {
    	Set<String> unique = new HashSet<String>();
    	for(int i = 0; i < shelters.size(); i++) {
    		unique.add(shelters.get(i).getGuid().replace(" ", ""));
    	}
    	if(shelters.size() == unique.size()) {
    		return true;
    	}
    	return false;
    }
    
    public static boolean Missing(ArrayList<TimefallShelter> shelters) {
    	for(int i = 0; i < shelters.size(); i++) {
    		if(shelters.get(i).getAddress() == null || shelters.get(i).getGuid() == null || 
    				shelters.get(i).getName() == null || shelters.get(i).getChiralFrequency() == null 
    				|| shelters.get(i).getTimefall() == null || shelters.get(i).getPhone() == null) {
    			return false;
    		}
    	}
    	return true;

    }
    
	public static void main(String[] args) throws JsonIOException, IOException {
		Main solution = new Main();
		WristCuff wc = new WristCuff();
		System.out.println("Welcome to Bridges Link.\n");
		boolean repeat = true;
		String temp = "";
		String filename = "";
		while(repeat) {
			Scanner userinput = new Scanner(System.in);
			System.out.print("Please provide timefall shelter data source:");
			filename = userinput.nextLine();
			try{
				File file = new File(filename);//handle bad input here, validate the objects	
				Scanner sc = new Scanner(file);
				while(sc.hasNext()) {
					temp += sc.nextLine();
				}//load the JSON file into a string object
				ArrayList<TimefallShelter> temp_list = solution.readFile(temp);
				boolean haha = false;
				for(int i = 0; i < temp_list.size(); i++) {
					String guid = temp_list.get(i).getGuid().replace(" ", "");
					String phone = temp_list.get(i).getPhone().replace(" ", "");
					if(haha == Main.isValidGUID(guid)){
						haha = true;
						temp = "";
						System.out.println("Invalid GUID!");
						break;
					}
					else if(haha == Main.isValidPhone(phone)) {
						haha = true;
						temp = "";
						System.out.println("Invalid Phone!");
						break;
					}
				}
				if(haha == Main.Missing(temp_list)) {
					haha = true;
				    temp = "";
				    System.out.println("Missing parameters, please double check or provide new file!\n");
				}
				else if(haha == Main.isUniqueChiral(temp_list)) {
			    	haha = true;
				    temp = "";
				    System.out.println("Please provide unique chiral frequencies!\n");
				}
				else if(haha == Main.isUniqueGUID(temp_list)) {
					haha = true;
					temp = "";
					System.out.println("Please provide unique GUIDs!\n");
				}
				else if(haha == Main.isUniqueName(temp_list)) {
					haha = true;
					temp = "";
					System.out.println("Please provide unique names!\n");
				}				
//				sc.close();
//				userinput.close();
				repeat = haha;
			}
			catch (FileNotFoundException fnfe) {
				System.out.println("The file " + filename +" could not be found.");
				System.out.println();
			}
			catch (JsonSyntaxException jpe) {
				System.out.println("In the file " + filename +" data cannot be converted to the proper type as shown above.");
				System.out.println();
			}
			//missing parameter exception not handled
		}
		System.out.println("=== Data Accepted ===\n");
		ArrayList<TimefallShelter> shelter_list = solution.readFile(temp);
		Set<Integer> targetSet = solution.setSupportedFrequencies();
		ArrayList<Integer> targetArrayList = new ArrayList<>(targetSet);
		boolean repeatedly = true;
		while(repeatedly) {
			solution.displayOptions();
			Scanner get_opt = new Scanner(System.in);
			System.out.print("Choose an Option: ");
			String input = get_opt.nextLine();
			if(input.equals("1")) {
				wc.listAllShelters(targetSet, shelter_list);
			}
			else if(input.equals("2")) {
				wc.searchByFrequency(shelter_list);
			}
			else if(input.equals("3")) {
				wc.searchByName(shelter_list);
			}
			else if(input.equals("4")) {
				wc.sortShelters(filename, shelter_list);
			}
			else if(input.equals("5")) {
				wc.findShelter(targetArrayList, shelter_list, filename);
				break;
			}
		}	
	}
}

