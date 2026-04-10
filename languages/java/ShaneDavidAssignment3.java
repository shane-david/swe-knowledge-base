/* Shane David
 * CS1450 M/W
 * 9/16/2025
 * Assignment 3
 * Description: this program creates a dog system using interfaces and abstract classes 
 * it users interfaces for roles, the abstract dog class for a generic class, and concrete classes the extend dog and implement the roles
 * main then tests this system by reading in dogs from a file and adding them to an array
 * then finding the protectors and making an array list
 * then finding the best protector
 * then finding the most common ability
 */

import java.io.File; //for file i/o
import java.io.IOException; //for file error handling
import java.util.Scanner; //to read from the file 
import java.util.ArrayList; //for array lists 

public class ShaneDavidAssignment3 {
    public static void main(String[] args) throws IOException {

        //---------------
        //arrauy of dogs
        //---------------

        //open file for reading 
        File filename = new File("Dogs.txt");
        Scanner fin = new Scanner(filename); 

        //read in number of dogs
        int numDogs = fin.nextInt(); 

        //create array 
        Dog[] dogs = new Dog[numDogs]; 

        //fill array 
        for(int i = 0; i < dogs.length; i++) {

            //read in type and name
            String type = fin.next(); 
            String name = fin.next(); 

            //read in abilitys 
            int serviceAbility = fin.nextInt();
            int herdAbility = fin.nextInt();
            int huntAbility = fin.nextInt();
            int protectAbility = fin.nextInt();

            //if it is a border collie
            if (type.equals("BorderCollie")) {

                BorderCollie aBorderCollie = new BorderCollie(name, serviceAbility, herdAbility, protectAbility); 
                dogs[i] = aBorderCollie; 

            //if it is a boxer
            } else if (type.equals("Boxer")) {

                Boxer aBoxer = new Boxer(name, serviceAbility, herdAbility, huntAbility, protectAbility);
                dogs[i] = aBoxer; 

            //if it is a german shepherd
            } else if (type.equals("GermanShepherd")) {

                GermanShepherd aGermanShepherd = new GermanShepherd(name, serviceAbility, herdAbility, protectAbility);
                dogs[i] = aGermanShepherd; 

            //if it is a golden retriever
            } else if (type.equals("GoldenRetriever")) {

                GoldenRetriever aGoldenRetriever = new GoldenRetriever(name, serviceAbility, huntAbility); 
                dogs[i] = aGoldenRetriever; 

            //error handling
            } else {
                System.out.println("Not a valid type");
            }

        }

        //close file
        fin.close();

        //-----------------
        //Helper functions 
        //-----------------

        //call find protectors
        ArrayList<Dog> protectors = findProtectors(dogs); 

        //protector table header 
        System.out.println("DOGS THAT PROTECT");
        System.out.println("-----------------------------------------------------------------------------------");
        System.out.printf("%-15s %-12s %-40s %-20s%n", "Dog", "Protection", "Temperatment", "Breed"); 
        System.out.println("-----------------------------------------------------------------------------------");

        //dispaly information
        for (int i = 0; i < protectors.size(); i++) {
            String name = protectors.get(i).getName();
            int protect = ((Protector)(protectors).get(i)).protect(); 
            String temperament = protectors.get(i).temperament(); 
            String breed =  protectors.get(i).getBreed(); 
            System.out.printf("%-15s %-12d %-40s %-20s%n", name, protect, temperament,breed); 
        }

        //newline for seperation
        System.out.println();

        //call best protector
        Dog bestProtector = findBestProtector(protectors); 

        //table header 
        System.out.println("BEST PROTECTING DOG");
        System.out.println("-----------------------");

        //best protector info 
        System.out.printf("Name: %s%n", bestProtector.getName());
        System.out.printf("Breed: %s%n", bestProtector.getBreed());
        System.out.printf("Temperament: %s%n", bestProtector.temperament());
        System.out.printf("Protecting Ability: %d%n", ((Protector)bestProtector).protect()); 

        //newline for seperation
        System.out.println();

        //call most common ability 
        String mostCommonAbility = findMostCommonAbility(dogs); 

        //table header
        System.out.println("MOST COMMON ABILITY FOR THE DOGS");
        System.out.println("----------------------------------");

        //print info
        System.out.printf("%s is the most common ability among the given dogs", mostCommonAbility); 

    }

    public static ArrayList<Dog> findProtectors (Dog[] dogs) {

        //create array list 
        ArrayList<Dog> protectors = new ArrayList<Dog>(); 

        //iterate through dogs
        for (int i = 0; i < dogs.length; i++) {

            //if dog is a protecter add it to protectors
            if (dogs[i] instanceof Protector) {
                protectors.add(dogs[i]); 
            }
        }

        return protectors; 
    }

    public static Dog findBestProtector(ArrayList<Dog> protectors) {

        //create best protect ability for first protector 
        //use dynamic casting to access the protect method 
        int bestProtectAbility = ((Protector)protectors.get(0)).protect();
        int bestProtectorIndex = 0; 

        //iterate through protectors
        for (int i = 0; i < protectors.size(); i++) {

            //make sure it is a protector just in case 
            if (protectors.get(i) instanceof Protector) {

                //if there is a new best protector
                if (((Protector)protectors.get(i)).protect() > bestProtectAbility) {
                    bestProtectAbility = ((Protector)protectors.get(i)).protect(); 
                    bestProtectorIndex = i; 
                }
            }
        }

        //return best protector
        return protectors.get(bestProtectorIndex); 
    }

    public static String findMostCommonAbility(Dog[] dogs) {

        //define counters for each ability
        int server = 0, herder = 0, hunter = 0, protector = 0; 

        //iterate through dogs 
        for (int i = 0; i < dogs.length; i++) {

            //if it is a server
            if (dogs[i] instanceof Server) {
                
                //increment counter
                server++;

            //if it is a herder
            } else if (dogs[i] instanceof Herder) {

                //increment counter
                herder++;

            //if it is a hunter
            } else if (dogs[i] instanceof Hunter) {

                //increment counter
                hunter++;

            //if it is a protector
            } else if (dogs[i] instanceof Protector) {

                //increment counter
                protector++; 
            }

        }

        //return string based of which one is greatest (>= incase there are two equal abilites) 
        if (server >= herder && server >= hunter && server >= protector) {
            return "Server";
        } else if (herder >= server && herder >= hunter && herder >= protector) {
            return "Herder";
        } else if (hunter >= server && hunter >= herder && hunter >= protector) {
            return "Hunter";
        } else if (protector >= server && protector >= herder && protector >= hunter) {
            return "Protector"; 
        } else {
            return "NONE"; 
        }
    }
}

//-----------
//Interfaces
//-----------

//Server
interface Server {

    //abstract method returning ability to be of service
    public abstract int serve(); 
}

//Herder
interface Herder {

    //abstract method returning ability to herd
    public abstract int herd(); 
}

//Hunter
interface Hunter {

    //abstract method returning ability to hunt
    public abstract int hunt();
}

//Protector
interface Protector {

    //abstract method returning ability to protect
    public abstract int protect(); 
}

//-----------------
//Abstract Classes
//-----------------

//Dog 
abstract class Dog {

    //private data

    private String name;
    private String breed; 

    //abstract public methods

    public abstract String temperament(); 

    //getters

    public String getName() {
        return name;
    }

    public String getBreed() {
        return breed; 
    }

    //setters
    
    public void setName(String name) {
        this.name = name; 
    }

    public void setBreed(String breed) {
        this.breed = breed; 
    }
}

//-----------------
//Concrete Classes
//-----------------

//Border Collie 
class BorderCollie extends Dog implements Server, Herder, Protector {

    //private data 

    private int serviceAbility;
    private int herdAbility;
    private int protectAbility;

    //constructor
    public BorderCollie(String name, int serviceAbility, int herdAbility, int protectAbility) {
        
        //set name and breed
        setName(name);
        setBreed("Border Collie");

        //set abilities
        this.serviceAbility = serviceAbility;
        this.herdAbility = herdAbility;
        this.protectAbility = protectAbility; 
    }

    //public methods

    @Override
    public int serve() {
        return serviceAbility; 
    }

    @Override
    public int herd() {
        return herdAbility; 
    }

    @Override
    public int protect() {
        return protectAbility; 
    }

    @Override
    public String temperament() {
        return "Intelligent, tenacious, energetic"; 
    }

}

//Boxer
class Boxer extends Dog implements Server, Herder, Hunter, Protector {

    //private data 

    private int serviceAbility;
    private int herdAbility;
    private int huntAbility; 
    private int protectAbility;

    //constructor
    public Boxer(String name, int serviceAbility, int herdAbility, int huntAbility, int protectAbility) {
        
        //set name and breed
        setName(name);
        setBreed("Boxer");

        //set abilities
        this.serviceAbility = serviceAbility;
        this.herdAbility = herdAbility;
        this.huntAbility = huntAbility; 
        this.protectAbility = protectAbility; 
    }

    //public methods

    @Override
    public int serve() {
        return serviceAbility; 
    }

    @Override
    public int herd() {
        return herdAbility; 
    }

    @Override
    public int hunt() {
        return huntAbility; 
    }

    @Override
    public int protect() {
        return protectAbility; 
    }

    @Override
    public String temperament() {
        return "Fearless, confident, brave"; 
    }

}

//German Shepherd
class GermanShepherd extends Dog implements Server, Herder, Protector {

    //private data 

    private int serviceAbility;
    private int herdAbility;
    private int protectAbility;

    //constructor
    public GermanShepherd(String name, int serviceAbility, int herdAbility, int protectAbility) {
        
        //set name and breed
        setName(name);
        setBreed("German Shepherd");

        //set abilities
        this.serviceAbility = serviceAbility;
        this.herdAbility = herdAbility;
        this.protectAbility = protectAbility; 
    }

    //public methods

    @Override
    public int serve() {
        return serviceAbility; 
    }

    @Override
    public int herd() {
        return herdAbility; 
    }

    @Override
    public int protect() {
        return protectAbility; 
    }

    @Override
    public String temperament() {
        return "Confident, watchful, courageous"; 
    }

}

//Golden Retriever
class GoldenRetriever extends Dog implements Server, Hunter {

    //private data 

    private int serviceAbility;
    private int huntAbility; 

    //constructor
    public GoldenRetriever(String name, int serviceAbility, int huntAbility) {
        
        //set name and breed
        setName(name);
        setBreed("Golden Retriever");

        //set abilities
        this.serviceAbility = serviceAbility;
        this.huntAbility = huntAbility; 
    }

    //public methods

    @Override
    public int serve() {
        return serviceAbility; 
    }

    @Override
    public int hunt() {
        return huntAbility; 
    }

    @Override
    public String temperament() {
        return "Friendly, intelligent, devoted"; 
    }

}