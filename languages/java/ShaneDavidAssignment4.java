/* Shane David 
 * CS1450 (M/W)
 * Assignment 4
 * Description: this program uses a 2d array and the compareable interface to create an ocean 
 * (represented by 2d array) and add ships and land to it according to a file 
 * it then displays the ocean and calls a method to gather all the ships in the ocean 
 * sort them, and display their information 
 */

import java.io.File; //for file i/o
import java.io.IOException; //for error handling 
import java.util.Scanner; //for file reading 
import java.util.ArrayList; //for array lists 
import java.util.Collections; // for sort

public class ShaneDavidAssignment4 {
    public static void main(String[] args) throws IOException {

        //create ocean file object and open for reading 
        File oceanFile = new File("Ocean.txt"); 
        Scanner oceanFin = new Scanner(oceanFile); 

        //read in name and size 
        String oceanName = oceanFin.nextLine();
        int numRows = oceanFin.nextInt();
        int numCols = oceanFin.nextInt(); 

        //create ocean object
        Ocean aOcean = new Ocean(oceanName, numRows, numCols); 

        //close ocean file 
        oceanFin.close();

        //create ships file and open for reading 
        File shipsFile = new File("Ships.txt"); 
        Scanner shipsFin = new Scanner(shipsFile); 

        //while there are ships in the ships file 
        while (shipsFin.hasNext()) {

            //read in values 
            int shipRow = shipsFin.nextInt();
            int shipCol = shipsFin.nextInt(); 
            int capacity = shipsFin.nextInt(); 
            String classification = shipsFin.next();
            String name = shipsFin.nextLine().strip(); 

            //create ship object
            Ship aShip = new Ship(classification, capacity, name);

            //add to ocean
            aOcean.addElement(shipRow,shipCol, aShip);
        }

        //close ships file 
        shipsFin.close();

        //creat land file and open for reading 
        File landFile = new File("Land.txt");
        Scanner landFin = new Scanner(landFile); 

        //whiel there is land in the land file 
        while (landFin.hasNext()) {

            //read in values
            int landRow = landFin.nextInt();
            int landCol = landFin.nextInt(); 

            //create land object
            Land aLand = new Land();

            //add to ocean 
            aOcean.addElement(landRow, landCol, aLand);
        }

        //close land file 
        landFin.close(); 

        //call print ocean 
        aOcean.displayOcean();

        //print some space
        System.out.println();
        System.out.println();

        //call print ships report
        printShipsReport(aOcean);

    }

    public static void printShipsReport(Ocean ocean) {

        ArrayList<Ship> shipsList = new ArrayList<>(); 

        //iterate through rows of ocean
        for (int row = 0; row  < ocean.getNumberRows(); row++) {
            //iterate through cols of ocean
            for (int col = 0; col < ocean.getNumberColumns(); col++) {

                //if the element is a ship put it in shipsList
                if (ocean.getElement(row, col) instanceof Ship) {
                    shipsList.add( (Ship) ocean.getElement(row, col)); 
                }
            }
        }

        //sort ships array
        Collections.sort(shipsList); 

        //print table header
        System.out.println("***********************************************************************************");
        System.out.println("                                Ocean Ship Report                                  ");
        System.out.println("                    (From Smallest Capacity to Largest Capacity)                   ");
        System.out.println("***********************************************************************************");
        System.out.printf("%-16s\t\t%-16s\t\t%-10s%n", "Classification", "Name", "Capacity"); 
        System.out.println("-----------------------------------------------------------------------------------");


        //iterate throuh ships list 
        for (int i = 0; i < shipsList.size(); i++) {

            //print out ships toString()
            System.out.println(shipsList.get(i).toString()); 
        }

    }
}

//-----------
//Ocean Class
//-----------
class Ocean {

    //private state
    private String name;
    private int numberRows;
    private int numberColumns;
    OceanElement[][]  grid; 

    //public constructor
    public Ocean(String name, int numberRows, int numberColumns) {

        //intialize state
        this.name = name;
        this.numberRows = numberRows;
        this.numberColumns = numberColumns; 

        //initalize 2d array 
        grid = new OceanElement[numberRows][numberColumns]; 

    }

    //public methods

    //get set the padded in element at the passed in position 
    public void addElement(int row, int column, OceanElement element) {
        grid[row][column] = element; 
    }

    //return element at passed in position 
    public OceanElement getElement(int row, int column) {
        return grid[row][column]; 
    }

    //iterate throug grid and print out type of each element in it 
    public void displayOcean() {

        //tell about loading 
        System.out.println("Loading " + name + " grid with land and ships...");

        //print out table 

        //iterate through rows, start at -1 for header 
        for (int row = -1; row < numberRows; row++) {

            //iterate throug cols start at -1 for header
            for (int col = -1; col < numberColumns; col++) {

                //if row is -1 its the header
                if (row == -1) {

                    //if the col is -1 it just a tab
                    if (col == -1) {
                        System.out.printf("        ");

                    //otherwise print the Column plus column number 
                    } else {
                        System.out.printf("%-16s", "Column " + col); 
                    }
                
                //otherwise print the row 
                } else {

                    //if the col is -1 print row 
                    if (col == -1) {
                        System.out.printf("%-8s", "Row " + row); 

                    //otherwise print the element 
                    } else {
                        
                        //if it is null
                        if (getElement(row, col) == null) {
                            System.out.printf("%-16s", "-------"); 
                        //if it is a Ship
                        } else if (getElement(row, col) instanceof Ship) {
                            System.out.printf("%-16s", ((Ship) getElement(row, col)).getName()); 
                        //if it is land 
                        } else if (getElement(row, col) instanceof Land) {
                            System.out.printf("%-16s", "Land"); 
                        }
                    }
                }

            } //end for col 

            //go to next line at the end of row 
            System.out.printf("%n"); 

        } //end for row

    }

    //getters

    public String getName() {
        return name; 
    }

    public int getNumberRows() {
        return numberRows; 
    }

    public int getNumberColumns() {
        return numberColumns; 
    }

}

//----------------------------
//OceanElement Abstract Class
//----------------------------
abstract class OceanElement {

    //private state
    private String type; 

    //public constructor
    public OceanElement(String type) {
        this.type = type; 
    }

    //getter
    public String getType() {
        return type; 
    }
}

//------------
//Ship Class 
//------------
class Ship extends OceanElement implements Comparable<Ship> {

    //private state
    private String name;
    private String classification;
    private int capacity; 

    //public constructor
    public Ship(String classification, int capacity, String name) {
        
        //intialize type with superclass constructor 
        super("Ship"); 

        //intialize state
        this.classification = classification; 
        this.capacity = capacity; 
        this.name = name;
    }

    //public methods 

    @Override
    //overriden from Object class to print classifition name and capacity in a formatted string 
    public String toString() {
        return String.format("%-16s\t\t%-16s\t\t%d", classification, name, capacity); 
    }

    @Override
    //overriden from comparable interface to compare ships by capacity 
    public int compareTo(Ship otherShip) {

        //if smaller it should go first 
        if (capacity < otherShip.capacity) {

            return -1; 

        //if bigger it should go second
        } else if (capacity > otherShip.capacity) {

            return 1; 
        
        //if they are the same 
        } else {
            return 0;
        }
    }

    //getters 
    public String getName() {
        return name;
    }
}

//-----------
//Land Class
//-----------
class Land extends OceanElement {

    //public constructor
    public Land() {

        //set the type 
        super("Land"); 

    }

}