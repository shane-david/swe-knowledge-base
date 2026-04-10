// Shane David
// CS1450 M/W
// 9/10/2025
// Assignmnt 2
// Description: This class creates a Vehicles parent class that has 
// Car, Train, Motorcycle, and Bus subclasses whose main functionality is the sound() that returns
// a string representing the sound they make. It also has a repair shop class that has an array of cars and motorcycles.
// Main then creates a vehicels array by reading from a file, prints their details, puts the cars and motrocycles
// into a repair shop, and then prints the repair shop details

import java.io.File; //to create file object
import java.io.IOException; //for file error handling 
import java.util.Scanner; //for file reading 

public class ShaneDavidAssignment2  {
    public static void main(String[] args) throws IOException {
        
        //open file for reading 
        File fileName = new File("Vehicles.txt"); 
        Scanner fin = new Scanner(fileName); 

        //get number of vehicles 
        int numVehicles = fin.nextInt();

        //create vehicle array of that value 
        Vehicle[] vehicles = new Vehicle[numVehicles]; 

        //add vehicles from file to array
        for(int i = 0; i < numVehicles; i++) {

            //read in type 
            String type = fin.next(); 

            //read in name and trim whitespace 
            String name = fin.nextLine().trim();

            //decision making based off of type 

            //if car 
            if (type.equals("car")) {

                //create car object and add to array
                Car aCar = new Car(name); 
                vehicles[i] = aCar; 
            
            //if bus 
            } else if (type.equals("bus")) {

                //create bus object and add to array 
                Bus aBus = new Bus(name);
                vehicles[i] = aBus; 

            //if motorcycle
            } else if (type.equals("motorcycle")) {

                //create motorcycle object and add to array
                Motorcycle aMotorcycle = new Motorcycle(name); 
                vehicles[i] = aMotorcycle; 

            //if train 
            } else if (type.equals("train")) {

                //create train object and add to array
                Train aTrain = new Train(name);
                vehicles[i] = aTrain; 
            }
        }

        //create header for table of vehicles 
        System.out.println("-------------------------------------------------------------");
        System.out.printf("%-15s %-25s %-25s %n", "Type", "Name", "Sound");
        System.out.println("-------------------------------------------------------------");

        //iterate through vehicles and print type name and sound 
        for (int i = 0; i < vehicles.length; i++) {
            System.out.printf("%-15s %-25s %-25s %n", vehicles[i].getType(), vehicles[i].getName(), vehicles[i].sound());
        }

        //give a couple lines of whitespace
        System.out.println();
        System.out.println();


        //------------
        //Repair Shop
        //------------

        //create repair shop object 
        RepairShop shop1 = new RepairShop();

        //fill the repair shop with vehicles
        shop1.fillRepairShop(vehicles);

        //print the repair shop details
        shop1.printRepairShopDetails();

        //close file 
        fin.close(); 

    }
}

//---------------------
//Vehicles Parent Class
//---------------------
class Vehicle {

    //-------------
    //private data
    //-------------

    private String type; 
    private String name; 

    //------------
    //constructors
    //------------

    //default constructor
    public Vehicle() {}

    //paramaterized constructor
    public Vehicle(String type, String name) {
        this.type = type;
        this.name = name; 
    }

    //---------------
    //public methods
    //---------------

    //sound method, generic sound
    public String sound() {
        return "*generic car sounds*"; 
    }

    //--------
    //getters
    //--------

    public String getType() {
        return type;
    }

    public String getName() {
        return name; 
    }

}

//-------------
//Bus subclass
//-------------
class Bus extends Vehicle {

    //-------------
    //Constructors
    //-------------

    //default constructor
    public Bus() {}

    //paramterized constructor
    public Bus(String name) {

        //call super method for vehicle constructor
        super("Bus", name); 
    }

    //--------------
    //public methods
    //--------------

    //sound method 
    @Override
    public String sound() {
        return "Rum-rum-rum-rummm"; 
    }
}

//------------
//car subclass
//------------
class Car extends Vehicle {

    //-------------
    //Constructors
    //-------------

    //default constructor
    public Car() {}

    //paramterized constructor
    public Car(String name) {

        //call super method for vehicle constructor
        super("Car", name); 
    }

    //--------------
    //public methods
    //--------------

    //sound method 
    @Override
    public String sound() {
        return "Vroom-vroom-vroommm"; 
    }
    
}

//--------------------
//Motorcycle subclass
//--------------------
class Motorcycle extends Vehicle {

    //-------------
    //Constructors
    //-------------

    //default constructor
    public Motorcycle() {}

    //paramterized constructor
    public Motorcycle(String name) {

        //call super method for vehicle constructor
        super("Motorcycle", name); 
    }

    //--------------
    //public methods
    //--------------

    //sound method 
    @Override
    public String sound() {
        return "Bom-bom-bom"; 
    }
    
}

//---------------
//Train subclass
//---------------
class Train extends Vehicle {

    //-------------
    //Constructors
    //-------------

    //default constructor
    public Train() {}

    //paramterized constructor
    public Train(String name) {

        //call super method for vehicle constructor
        super("Train", name); 
    }

    //--------------
    //public methods
    //--------------

    //sound method 
    @Override
    public String sound() {
        return "Chooga-chooga-chooga"; 
    }
    
}

//-----------------
//RepairShop Class
//-----------------
class RepairShop {

    //-------------
    //private data
    //-------------

    private int numCars;
    private int numMotorcycles;
    private Vehicle[] vehiclesToRepair; 

    //-------------
    //constructors
    //-------------

    //default constructor
    public RepairShop() {}

    //---------------
    //public methods
    //---------------

    //fill the repair shop with cars and motorcycles
    public void fillRepairShop(Vehicle[] vehicles) {

        //determine amount of cars and motorcycles 
        for(int i = 0; i < vehicles.length; i++) {

            //if car 
            if(vehicles[i] instanceof Car) {
                numCars++;
            //if motorcycle
            } else if (vehicles[i] instanceof Motorcycle) {
                numMotorcycles++;
            }
        }

        //create vehiclesToRepair array 
        vehiclesToRepair = new Vehicle[numCars+numMotorcycles]; 

        //create iterator for vehicles to repair
        int j = 0; 

        //iterate throgh vehicels and add cars and motorcycles
        for(int i = 0; i < vehicles.length; i++) {

            //if car or motorcycle and j does not exceed length of vehiclesToRepair
            if(vehicles[i] instanceof Car || vehicles[i] instanceof Motorcycle && j < numCars+numMotorcycles) {
                vehiclesToRepair[j] = vehicles[i];
                j++; 
            }
        }
    }

    public void printRepairShopDetails() {

        //print header 
        System.out.println("---------------------------------------------");
        System.out.println("Car and Motorcycle Repair Shop");
        System.out.println("---------------------------------------------");

        //print number of cars and motorcycles
        System.out.printf("%-25s %d%n", "Number of Cars: ", numCars);
        System.out.printf("%-25s %d%n", "Number of Motorcycles: ", numMotorcycles);
        System.out.println();

        //iterate through cars to repair and print name and type 
        for(int i = 0; i < vehiclesToRepair.length; i++) {
            System.out.printf("%-15s --- %-25s %n", vehiclesToRepair[i].getType(), vehiclesToRepair[i].getName()); 

        }
    }
}
