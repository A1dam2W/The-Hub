package classes;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonIOException;
import com.google.gson.JsonSyntaxException;

public class WristCuff {

    //set initial values for needed members
    public WristCuff() {

    }


    /**
     * List all available shelters within the min and max of supported Chiral frequencies
     */
    void listAllShelters(Set<Integer> chiralFrequencies, ArrayList<TimefallShelter> shelterlist) {   	
    	System.out.println();
    	int result = 0;
    	ArrayList<TimefallShelter> temp = new ArrayList<TimefallShelter>();
    	if (chiralFrequencies.isEmpty()) {
    	}//should prompt the user to enter it again
    	else {
    		for(int i = 0; i < shelterlist.size();i++) {
    			if(chiralFrequencies.contains(shelterlist.get(i).getChiralFrequency()) && shelterlist.get(i).getTimefall() == false){
    				temp.add(shelterlist.get(i));
    				result++;
    			}
    		}
    		if(result == 1) {
    			System.out.println(result + " result\n");
    		}
    		else if(result == 0) {
    			System.out.println(result + " result\n");//TODO   			
    		}
    		else {
    		System.out.println(result + " results\n");
    		}
//    		String formattedString = temp.toString()
//    			    .replace(",", "")  //remove the commas
//    			    .replace("[", "")  //remove the right bracket
//    			    .replace("]", "");  //remove the left bracket
//    		System.out.println(formattedString);
    		for(int j = 0; j < temp.size();j++) {
    			System.out.println(temp.get(j));
    		}
    	}
    }
    
    
    void searchByFrequency(ArrayList<TimefallShelter> shelterlist) {
		boolean repeat = true;
		while(repeat) {
    	Scanner get_opt = new Scanner(System.in);
		System.out.print("What Chiral frequency are you looking for? ");
		String input = get_opt.nextLine();
		int input_int = Integer.parseInt(input);
		for(int i = 0; i < shelterlist.size();i++) {
			if(shelterlist.get(i).getChiralFrequency() == input_int){
				System.out.println();
				System.out.println(shelterlist.get(i));
				repeat = false;
				return;
			}
		}
		System.out.println("That Chiral frequency does not exist.\n");
		}    	
    }
    
    void searchByName(ArrayList<TimefallShelter> shelterlist) {
		boolean repeat = true;
		while(repeat) {
    	Scanner get_opt = new Scanner(System.in);
		System.out.print("What shelter's name are you looking for? ");
		String input = get_opt.nextLine();
		for(int i = 0; i < shelterlist.size();i++) {
			if(shelterlist.get(i).getName().toLowerCase().equals(input.toLowerCase())){
				System.out.println();
				System.out.println("Found!\n");
				System.out.println(shelterlist.get(i));
				repeat = false;
				return;
			}
		}
		System.out.println("No such shelter...\n");
		}    
    }


    /**
     * Functions for:
     * Search for a shelter by Chiral frequency
     * Search for a shelter by name
     */


    /**
     * Find an available shelter with the lowest supported Chiral frequency
     * @throws IOException 
     */
    public void findShelter(ArrayList<Integer> chiralFrequencies, ArrayList<TimefallShelter> shelterlist, String fileName) throws IOException {
    	System.out.println();
    	System.out.println("=== Commencing timefall shelter search ===\n");
    	Collections.sort(chiralFrequencies);//sorted arraylist of integers(ascending)
    	int counter = 0;
//    	ArrayList<TimefallShelter> temp = shelterlist;
    	while(counter < chiralFrequencies.size()) {
    		int min = chiralFrequencies.get(counter);
    		boolean pruned = false;
    		for(int i = 0; i < shelterlist.size();i++) {
    			if(shelterlist.get(i).getChiralFrequency() == min && shelterlist.get(i).getTimefall() == false){//finding the shelter
    				System.out.println();
    				System.out.println("=== Matching timefall shelter found! ===\n");
    				System.out.println(shelterlist.get(i) + "\n");
    				System.out.println("=== Commencing Chiral jump, see you in safety. ===");
    				return;
    			}
    			if(shelterlist.get(i).getChiralFrequency() == min && shelterlist.get(i).getTimefall() == true){
    				shelterlist.remove(i);
    				this.save(shelterlist, fileName);
    				System.out.println("=== Chiral frequency " + min + " unstable, Chiral jump unavailable ===");
    				System.out.println("=== Removing target shelter from the list of shelters and saving updated list to disk. ===");
    				pruned = true;
    				counter++;
    				break;   				
    			}
    		}
    		if(!pruned) {
    			counter++;
    		}   		
    	}
    	System.out.println("=== No shelter available. You are DOOMED. ===");    	
    }



    /**
     * Sort shelters by Chiral frequency
     * @throws IOException 
     * @throws JsonIOException 
     */
    public void sortShelters(String fileName, ArrayList<TimefallShelter> shelterlist) throws JsonIOException, IOException, FileNotFoundException {
    	System.out.println();
    	System.out.println("Shelters successfully sorted by Chiral frequency.");
    	Collections.sort(shelterlist);//now the arraylist is sorted by chiral frequency    	
		this.save(shelterlist, fileName);
    }

    /**
     * Saves the updated list of shelters to disk
     * @throws IOException 
     */
    public void save(ArrayList<TimefallShelter> shelterlist, String fileName) throws IOException, FileNotFoundException {//throws FileNotFoundException, TODO
		Gson gson = new GsonBuilder().setPrettyPrinting().create();
    	List<TimefallShelter> temp = new ArrayList<TimefallShelter>();
    	for(int i = 0; i < shelterlist.size(); i++) {
    		temp.add(shelterlist.get(i));
    	}
    	String json = gson.toJson(temp);
    	BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
        writer.write(json);       
        writer.close(); 
    }
}
