/* Shane David 
 * CS1450 M / W
 * Assignment 9
 * Description: This class utilized self made single linked lists and double linked lists 
 * that hold airbnbs in order to simulate airbnb filtering. It reads and displays airbnbs into both list and dispalys them
 * it then filers them by criteria and removes lists  of certain types 
 */

import java.io.File; //for files
import java.util.Scanner; //for file reading 
import java.io.IOException; //for error handling
import java.lang.Comparable; //for Airbnb class
import java.util.PriorityQueue; //to store found Airbnbs

public class ShaneDavidAssignment9 {
    public static void main(String[] args) throws IOException {

        //create the linked lists
        AirbnbLinkedList aSingleList = new AirbnbLinkedList();
        DoubleLinkedList aDoubleList = new DoubleLinkedList(); 

        //create airbnb file object and open for reading 
        File airbnbFile = new File("Airbnbs.txt");
        Scanner airbnbFin = new Scanner(airbnbFile); 

        //read information into the lists 
        while (airbnbFin.hasNextLine()) {

            //read in info
            int rate = airbnbFin.nextInt();
            int guests = airbnbFin.nextInt();
            int bedrooms = airbnbFin.nextInt(); 
            String type = airbnbFin.nextLine().trim();  

            //make airbnb and add to lists
            Airbnb aAirbnb = new Airbnb(rate, guests, bedrooms, type);
            aSingleList.addByRate(aAirbnb);
            aDoubleList.addToEnd(aAirbnb);
        }

        //close file
        airbnbFin.close();

        //display lists 
        System.out.println("Airbnbs in Single Linked List - Ordered by Nightly Rates");
        System.out.println(""); 
        aSingleList.display();

        System.out.println("");
        System.out.println("");

        System.out.println("Airbnbs in Doubly Linked List - Airbnbs Printed Backwards");
        System.out.println("");
        aDoubleList.displayBackwards();
        
        System.out.println("");
        System.out.println("");

        //open reqquirements file for reading
        File airbnbRequirements = new File("AirbnbRequirements.txt");
        Scanner requirementsFin = new Scanner(airbnbRequirements); 

        //read in requirements
        int requiredRate = requirementsFin.nextInt();
        int requiredGuests = requirementsFin.nextInt();
        String requiredType = requirementsFin.nextLine().trim(); 

        //close file 
        requirementsFin.close(); 

        //store found airbnbs in priority quees 
        PriorityQueue<Airbnb> foundAirbnbs = aSingleList.findAirbnbs(requiredRate, requiredGuests, requiredType);

        //display pq
        System.out.println("Aribnbs in Priority Queue Meeting Parrot Requirements:");
        System.out.printf("%d a night or less, %d+ guests, and %s%n", requiredRate, requiredGuests, requiredType);
        System.out.println("");
        System.out.printf("%-25s %-15s %-8s %-10s%n", "Airbnb Type", "Nightly Rate", "Guests", "Bedrooms");
        System.out.println("------------------------------------------------------------------------------------");
        while (!foundAirbnbs.isEmpty()) {
            System.out.println(foundAirbnbs.remove().toString()); 
        }
        System.out.println("");
        System.out.println("");

        //remove condos and townhomes from single list 
        int numCondos = aSingleList.removeSpecificType("Condo");
        int numTownhomes = aSingleList.removeSpecificType("Townhome");

        //display results 
        System.out.println("Airbnbs in Single Linked List - Condos and Townhomes Removed");
        System.out.printf("Number of condos removed: %d%n", numCondos);
        System.out.printf("Number of townhomes removed: %d%n", numTownhomes); 

        System.out.println("");

        aSingleList.display();

    }
} 


//-------------
//Airbnb Class
//-------------
class Airbnb implements Comparable<Airbnb> {

    //private data

    private int nightlyRate;
    private int numGuests;
    private int numBedrooms;
    private String type; 

    //constructor
    public Airbnb(int nightlyRate, int numGuests, int numBedrooms, String type) {
        this.nightlyRate = nightlyRate;
        this.numGuests = numGuests;
        this.numBedrooms = numBedrooms;
        this.type = type; 
    }

    //public methods

    @Override
    public String toString() {
        return String.format("%-25s $%-15d %-8d %-10d", type, nightlyRate, numGuests, numBedrooms); 
    }

    @Override
    public int compareTo(Airbnb otherAirbnb) {
        
        //-1 when the other has priority
        if (this.nightlyRate < otherAirbnb.nightlyRate) {

            return -1; 

        //1 when this has priority
        } else if (this.nightlyRate > otherAirbnb.nightlyRate) {

            return 1;

        //0 when they are the same 
        } else {
            return 0; 
        }

    }

    //getters 

    public int getNightlyRate() {
        return nightlyRate;
    }

    public int getNumGuests() {
        return numGuests;
    }

    public int getNumBedrooms() {
        return numBedrooms; 
    }

    public String getType() {
        return type; 
    }
}

//-----------------------
//AirbnbLinkedList Class
//-----------------------
class AirbnbLinkedList {

    //private data 
    Node head;

    //public methods

    //add an airbnb to the linked list in sorted order
    //based on its nightly rate
    public void addByRate(Airbnb airbnbToAdd) {

        //create a node for the passed in Airbnb
        Node aNode = new Node(airbnbToAdd); 

        //if the list is empty
        if (head == null) {

            head = aNode; 

        //if you are adding to the beginning of the list
        } else if (head.data.compareTo(aNode.data) >= 0) {

            aNode.next = head;
            head = aNode; 

        //otherwise you are adding to the middle
        } else {

            //march through the list until you reach 1 before desired insertion point
            Node previous = head;
            while (previous.next != null && previous.next.data.compareTo(aNode.data) < 0) {
                previous = previous.next; 
            }

            //create current node
            Node current = previous.next;

            //insert aNode
            previous.next = aNode;
            aNode.next = current; 
        }
    }

    //finds airbnbs of specific criteria and puts them in 
    //a priority queue that it returns
    public PriorityQueue<Airbnb> findAirbnbs(int nightlyRate, int numGuests, String type) {

        //creat priority queue
        PriorityQueue<Airbnb> wantedAirbnbs = new PriorityQueue<>(); 

        //march through the list and add airbnbs as found
        Node current = head;
        while (current != null) {

            //if it meets the criteria 
            if (current.data.getNightlyRate() <= nightlyRate && current.data.getNumGuests() >= numGuests && current.data.getType().equals(type)) {
                wantedAirbnbs.offer(current.data); 
            }

            //progress through the list 
            current = current.next; 
        }


        //return result
        return wantedAirbnbs; 

    }

    //removes all airbnbs of a specific type from the linked list
    //and returns the number of airbnbs removed
    public int removeSpecificType(String typeToRemove) {

        //create count variable 
        int count = 0;

        //create nodes to march through 
        Node previous = null;
        Node current = head; 

        //march through ENTIRE list
        while (current != null) {

            //if it is the type we are looking for 
            if (current.data.getType().equals(typeToRemove)) {

                //increment count 
                count++;

                //if we are removing the first element 
                if (current == head) {

                    head = current.next;
                    current = head; 
                
                //otherwise it is a middle element 
                } else {

                    previous.next = current.next;
                    current = current.next; 

                }

            //if it is not the type we are looking for 
            } else {
                previous = current;
                current = current.next; 
            }
        }

        //return result 
        return count; 
    }

    //displays all of the airbnbs in the linked list 
    public void display() {

        //header 
        System.out.printf("%-25s %-15s %-8s %-10s%n", "Airbnb Type", "Nightly Rate", "Guests", "Bedrooms");
        System.out.println("------------------------------------------------------------------------------------");

        //create current node to march through linke list
        Node current = head;

        while (current != null) {
            System.out.println(current.data.toString());
            current = current.next; 
        }
    }

    //private inner node class
    private static class Node {

        //private data
        private Airbnb data;
        private Node next;

        //constructor
        public Node(Airbnb airbnb) {
            this.data = airbnb;
            this.next = null; 
        }
    }
}

//-------------------------
//Double Linked List Class
//-------------------------
class DoubleLinkedList {

    //private data
    private Node head;
    private Node tail; 

    //public methods

    //adds a node to the end of t he list and links it in
    public void addToEnd(Airbnb airbnbToAdd) {

        //create a node with the passed in airbnb
        Node aNode = new Node(airbnbToAdd); 

        //if we are adding to an empty list 
        if (head == null) {

            head = aNode;
            tail = aNode; 
        
        //otherwise add to end of list 
        } else {

           tail.next = aNode; 
           aNode.previous = tail;
           tail = tail.next; 

        }
    }

    //displays the double linked list backward 
    public void displayBackwards() {

        //header 
        System.out.printf("%-25s %-15s %-8s %-10s%n", "Airbnb Type", "Nightly Rate", "Guests", "Bedrooms");
        System.out.println("------------------------------------------------------------------------------------");

        //create node to step through
        Node current = tail; 

        //step through and print 
        while (current != null) {
            System.out.println(current.data.toString());
            current = current.previous; 
        }
    }

    //private inner node class
    private static class Node {

        //private data
        private Airbnb data;
        private Node next;
        private Node previous; 

        //constructor
        public Node(Airbnb airbnb) {
            this.data = airbnb;
            this.next = null; 
            this.previous = null; 
        }
    }
}

