/* Shane David
 * CS1450 M/W
 * 10/29/2025
 * Assignment 7
 * This program builds off of assignment 4 but now using queues and priority queues to emulate
 * the panama canal. It adds a Control Center and Canal class to manage ships going in and out of the canal
 * it puts ships from the atlantic ocean into the channel
 * then puts ships from the chanell into two transit ways depending on thier classification 
 * then puts ships from the transit ways into the pacific ocean 
 */

import java.io.File;
import java.io.IOException;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;

public class ShaneDavidAssignment7 {

	public static void main(String[] args) throws IOException {
		
		// Name of files to read from
		final String OCEAN_FILE_NAME = "Ocean7.txt";	
		final String LAND_FILE_NAME = "Land7.txt";	
		final String SHIP_FILE_NAME = "Ships7.txt";	

		// Setup file reference variables to refer to each text file
		File oceanFileName = new File(OCEAN_FILE_NAME);
		File landFileName = new File(LAND_FILE_NAME);
		File shipsFileName = new File(SHIP_FILE_NAME);

		// Open the ocean file for reading by creating a scanner for the file.
		// The 1st line contains the name of the ocean
		// The 2nd line and 3rd line tell how many rows and columns are in ocean grid. 
		// Use the rows and columns to create a 2-D array that models the ocean's grid.
		Scanner oceanFile = new Scanner (oceanFileName);
		String oceanName = oceanFile.nextLine();
		int numberRows = oceanFile.nextInt();
		int numberColumns = oceanFile.nextInt();

		// Create the ocean object based on the values read from the file.
		Ocean7 atlanticOcean = new Ocean7(oceanName, numberRows, numberColumns);

		// Load the ocean with ships and land
		System.out.println("Loading " + oceanName + " Ocean grid with ships and land...");
		System.out.println();

		// Open the ships file for reading by creating a scanner for the file
		// Create the ship objects from the details provided in the file.
		// STUDENT NOTE: In this assignment the number of ships is not part of the file so you
		// need to use a while loop and the hasNext method on the Scanner to read ships until the
		// end of the file is reached.
		Scanner shipsFile = new Scanner (shipsFileName);
		while (shipsFile.hasNext()) {
			
			// Read ship information from the file into separate variables
			int rowNumber = shipsFile.nextInt();
			int columnNumber = shipsFile.nextInt();
			int capacity = shipsFile.nextInt();
			String classification = shipsFile.next();	// cruise, cargo, tanker, navy
			String name = shipsFile.nextLine().trim();
			
			// Create a ship object
			// Place ship object into its correct location in the ocean
			Ship7 ship = new Ship7(classification, capacity, name); 
			atlanticOcean.addElement(rowNumber, columnNumber, ship);
		
		} // while more ships

		// Open the land file for reading by creating a scanner for the file
		// Create the land objects from the details provided in the file.
		Scanner landFile = new Scanner (landFileName);
		while (landFile.hasNext()) {
			
			// Read land location from the file into separate variables
			int rowNumber = landFile.nextInt();
			int columnNumber = landFile.nextInt();
			
			// Create a land object
			// Place land object into its correct location in the ocean
			Land7 land = new Land7(); 
			atlanticOcean.addElement(rowNumber, columnNumber, land);
		
		} // while more land 

		// Display the ocean's grid
		atlanticOcean.displayOcean();

		//-------------------
		//START ASSIGNMENT 7
		//-------------------

		//read in name and column number and size for pacfiic ocean and create it 
		String oceanNamePacific = oceanFile.next();
		int numberRowsPacific = oceanFile.nextInt();
		int numberColumnsPacific = oceanFile.nextInt(); 
		Ocean7 pacificOcean = new Ocean7(oceanNamePacific, numberRowsPacific, numberColumnsPacific);
		
		//create control center and canal objects with default constructors 
		ControlCenter controlCenter = new ControlCenter();
		Canal panamaCanal = new Canal(); 

		//move ships from atlantic ocean to channel
		controlCenter.moveShipsIntoChannel(atlanticOcean, panamaCanal);

		//newlines to make input more readable
		System.out.println("");
		System.out.println("");
		System.out.println("");

		//move ships from channel into transit ways
		controlCenter.moveShipsIntoTransitWays(panamaCanal);

		//newlines to make input more readable
		System.out.println("");
		System.out.println("");
		System.out.println("");

		//move ships fron transit ways into pacific ocean 
		controlCenter.moveShipsIntoPacificOcean(pacificOcean, 8, 1, panamaCanal);


		//newlines to make input more readable
		System.out.println("");
		System.out.println("");
		System.out.println("");

		//display both of the oceans
		System.out.println("Show Atlantic Ocean with no ships...");
		atlanticOcean.displayOcean();

		//newlines to make input more readable
		System.out.println("");
		System.out.println("");
		System.out.println("");

		System.out.println("Show Pacific Ocean with ships...");
		pacificOcean.displayOcean();

		// Close all the files
		oceanFile.close();
		landFile.close();
		shipsFile.close();

		
	} // main
	
} // Assignment 4


// Represents the Ocean.  
// The ocean contains a grid that is modeled using a 2D array.
// Each location in the grid contains an OceanElement object which is a ship or land. 
class Ocean7 {
	
	private String name;				// Name of ocean
	private int numberRows;				// Number of rows in the grid 
	private int numberColumns;			// Number of columns in the grid
	private OceanElement7[][] grid;	// 2-D array of ocean entities (ship or land)
										// This is a HAS-A relationship - Ocean HAS-A grid

	public Ocean7 (String name, int numberRows, int numberColumns) {
		this.name = name;
		this.numberRows = numberRows;			
		this.numberColumns = numberColumns;	

		// Allocate memory for the grid
		// STUDENT NOTE: The 1st index is the number of rows, the 2nd index is number of columns
		grid = new OceanElement7[numberRows][numberColumns];
	}


	// Returns the name of the ocean
	public String getName() {
		return name;
	}

	
	// Returns the number of rows in the grid
	public int getNumberRows() {
		return numberRows;
	}
		
	
	// Returns the number of columns in the grid
	public int getNumberColumns() {
		return numberColumns;
	}

	
	// Add an ocean element to the grid in a specific row and column location
	public void addElement(int row, int column, OceanElement7 oceanElement) {
		grid[row][column] = oceanElement; 
	}

	
	// Returns the ocean element in the specified row and column in the array.  
	// When a location does NOT contain an ocean element, returns null.
	public OceanElement7 getElement(int row, int column) {
		
		// Return the ocean element which can be null if the location is empty
		// STUDENT NOTE: When you created the array, Java initialized the array with null values
		return grid[row][column];
	}

	//removes an ocean element from the specefied locations
	public void removeElement(int row, int col) {
		grid[row][col] = null; 
	}

	
	// Displays all elements in the ocean's grid
	public void displayOcean() {
		
		// Display header for the number of columns in the 2D array
		for (int column = 0; column < numberColumns; column++) {
			System.out.printf("\t%s %d", "Column", column);
		}
		System.out.printf("\n\n");
		
		// For each row print the elements in that row
		for (int row = 0; row < numberRows; row++) {
			
			System.out.printf("%s%d", "Row ", row);
	
			// For each column display the element type otherwise display "----" to represent null
			for (int column = 0; column < numberColumns; column ++) {
	
				// Get element in location [row,column]
				OceanElement7 element = grid[row][column];
				
				// If there is an element in location [row,column] display its name if its a ship and 
				// type if it is land
				if (element != null) {
					if (element instanceof Ship7) {
						System.out.printf ("\t%-8s", ((Ship7)element).getName());
					}
					else {
						System.out.printf ("\t%-8s", element.getType());
					}
				}
				else {
					System.out.printf ("\t%-8s", "-------");				
				}
			} // for each column
			
			System.out.println();
			System.out.println();
			
		} // for each row
		
	} // displayOcean
	
} // Ocean


// Superclass for different types of objects in the ocean
// The main purpose of this class is to create the polymorphic array to represent the ocean
class OceanElement7 {
	private String type;	// Type of ocean element (ship or land)

	public OceanElement7 (String type) {
		this.type = type;
	}
	
	public String getType() {
		return type;
	}

} // OceanElement


// Represents a ship, ships must be comparable
class Ship7 extends OceanElement7 implements Comparable<Ship7>{

	private String name;			// Ship's name
	private String classification; 	// Ship's classification - cruise, cargo, tanker, navy
	private int capacity; 			// Ship's capacity
	
	// Create a ship
	public Ship7 (String classification, int capacity, String name) {
		// The type is in the super class, call the super class constructor to set type.
		// Because we are in the ship class, we know the type is "Ship" so no need to pass in.
		super("Ship");
		
		// The instance variables specific to a ship
		this.classification = classification;
		this.capacity = capacity;
		this.name = name;
	}

	// Returns name of ship
	public String getName() {
		return name;
	}

	//returns the classification of the ship
	public String getClassification() {
		return classification; 
	}

	// This method override the toString method in the Object class.
	// It creates a printable string to describe the ship
	@Override
	public String toString() {
		return String.format("%-10s\t\t%-10s\t\t%d", 
				classification, 
				name,  
				capacity);

	}
	
	@Override // This is where we write the code to compare two Ships.
	// In this assignment, compare two ships based on their capacity.
	// By writing this method, it is now possible to sort an array of ships 
	// by their capacity when calling the Collections.sort method
	public int compareTo(Ship7 otherShip) {
		
		//comparing ship classification 
		//Navy < Tanker < Cargo < Cruise 
		
		//if they are the same return 0 
		if (this.classification.equals(otherShip.classification)) {
			return 0; 
		//if it is a navy ship or the other ship is a cruise ship it has higher priority 
		} else if (this.classification.equals("Navy") || otherShip.classification.equals("Cruise")) {
			return -1; 
		//if it is a cruise ship or the other ship is a navy ship is has the lower priority 
		} else if (this.classification.equals("Cruise") || otherShip.classification.equals("Navy")) {
			return 1; 

		//otherwise, if neither ships are navy or cruise they must be tanker or cargo 
		} else {

			//if this is a tanker it has higher priority
			if (this.classification.equals("Tanker")) {
				return -1; 
			//if it is a cargo it has lower priority 
			} else {
				return 1; 
			}
		}
	}
} // Ship


// Represents land
class Land7 extends OceanElement7 {

	// Create land
	public Land7 () {
		// Because we are in the land class, we know the elementType is "Land" so no need to pass in
		super("Land");  
	}
			
} // Land


//-------------------------
//Assignment 7 new classes
//-------------------------

//class representing the canal
class Canal {

	//private data fields
	private PriorityQueue<Ship7> channel;
	private Queue<Ship7> transitWay1;
	private Queue<Ship7> transitWay2; 

	//constructor
	public Canal() {
		channel = new PriorityQueue<>();
		transitWay1 = new LinkedList<>();
		transitWay2 = new LinkedList<>(); 
	}

	//public methods 

	//adds the passed in ship to the channel using .offer
	public void addShipToChannel(Ship7 ship) {
		channel.offer(ship); 
	}

	//removes ship from channel and returns it 
	public Ship7 removeShipFromChannel() {
		Ship7 removedShip = channel.remove(); 
		return removedShip; 
	}

	//adds ship to transitway1 
	public void addShipToTransitWay1(Ship7 ship) {
		transitWay1.offer(ship); 
	}

	//removes ship from transitway1 
	public Ship7 removeShipFromTransitWay1() {
		Ship7 removedShip = transitWay1.remove();
		return removedShip; 
	}

	//adds ship to transitway2
	public void addShipToTransitWay2(Ship7 ship) {
		transitWay2.offer(ship); 
	}

	//removes ship from transitway2
	public Ship7 removeShipFromTransitWay2() {
		Ship7 removedShip = transitWay2.remove();
		return removedShip; 
	}

	//getters

	//return whether or not the channel is empty
	public boolean isChannelEmpty() {
		return channel.isEmpty(); 
	}

	//return whther or not transit way 1 is empty
	public boolean isTransitWay1Empty() {
		return transitWay1.isEmpty(); 
	}

	//return whther or not transit way 2 is empty
	public boolean isTransitWay2Empty() {
		return transitWay2.isEmpty(); 
	}

}

//class for controlling movement through canal
class ControlCenter {

	//public methods

	//moves ships from passed in oecan into channel 
	//starts at bottom right of ocean and adds to passed in canal
	public void moveShipsIntoChannel(Ocean7 ocean, Canal canal) {

		//display message 
		System.out.println("Controller: Moving ships from ocean to channel that forms approach to the transit ways:");
		System.out.println("----------------------------------------------------------------------------------------");


		//iterate through rows and columns backwards to start from bottom right of grid
		for (int row = ocean.getNumberRows() - 1; row >= 0; row--) {
			for (int col = ocean.getNumberColumns() - 1; col >= 0; col--) {

				//get the ocean element
				OceanElement7 gridPiece = ocean.getElement(row, col); 

				//if the element is a ship move it into the channel
				if (gridPiece instanceof Ship7) {

					canal.addShipToChannel((Ship7) gridPiece);
					ocean.removeElement(row, col);

					//display moving information 
					System.out.println("Moved to channel: " + gridPiece.toString());

				}
			}
		}
	}

	//moves ships from the channel to transitway1 or transitway2
	//cruise ships are moved to transity way 1 
	//all other ships are moved to transitway2
	public void moveShipsIntoTransitWays(Canal canal) {

		//display action message
		System.out.println("Controller: Moving ships waiting in the channel into transit ways:");
		System.out.println("------------------------------------------------------------------");

		//while the channel is not empty
		while(!canal.isChannelEmpty()) {

			//get the front ship
			Ship7 frontShip = canal.removeShipFromChannel();

			//if it is a cruise ship move it to transitway1
			if (frontShip.getClassification().equals("Cruise")) {

				canal.addShipToTransitWay1(frontShip);

				//display moving message
				System.out.println("Moved into transit way #1: " + frontShip.toString()); 

			//otherwwise move to transitway 2
			} else {

				canal.addShipToTransitWay2(frontShip);

				//display moving message
				System.out.println("Moved into transit way #2: " + frontShip.toString()); 

			}
		}
	}

	//move ships from transity way into pacific ocean
	//start at (8,1) and go up a row each time 
	//alternate transitway1 and transitway2
	public void moveShipsIntoPacificOcean(Ocean7 ocean, int row, int column, Canal canal) {

		//display action message
		System.out.println("Controller: Moving ships from transit ways into Pacific Ocean:");
		System.out.println("--------------------------------------------------------------");

		//have a counter to determine which transitways turn it is 
		int transitTurn = 0; 

		//while at least one canal has ships in it 
		while (!canal.isChannelEmpty() || !canal.isTransitWay2Empty()) {

			//if transitway 1 is not empty and it is its turn or transitway2 is empty take from transitway 1
			if ((transitTurn % 2 == 0 || canal.isTransitWay2Empty()) && !canal.isTransitWay1Empty()) {

				//remove from transit 1 and add to ocean at row and col
				Ship7 movedShip = canal.removeShipFromTransitWay1(); 
				ocean.addElement(row, column, movedShip);

				//display moving message
				System.out.println("Moved into Pacific ocean: " + movedShip.toString());

			//otherwise transit 2 is not empty and it is its turn or transit 1 is empty take from transit 2
			} else if ((transitTurn % 2 != 0 || canal.isTransitWay1Empty()) && !canal.isTransitWay2Empty()) {

				//remove from transit 2 and add to ocean at row and col
				Ship7 movedShip = canal.removeShipFromTransitWay2();
				ocean.addElement(row, column, movedShip);

				//display moving message
				System.out.println("Moved into Pacific ocean: " + movedShip.toString());				
			}

			//decrease row 
			row--; 

			//increase counter
			transitTurn++; 
		}
	}
}

