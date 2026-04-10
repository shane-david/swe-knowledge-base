/* Shane Davild
 * CS1450 (M/W)
 * 9/3/25
 * Assignment #1
 * Description: This program generates random numbers and writes them to a file 
 * it then reads those numbers from the file and puts them into seperate arrays
 * it then merges the two arrays into one sorted array 
 */

import java.io.File; //to create files 
import java.io.IOException; // for file exceptions 
import java.util.Scanner; //Scanner object for reading from files
import java.io.PrintWriter; //for writing to files 
import java.util.Arrays; //for .sort() 

public class ShaneDavidAssignment1 {
    public static void main(String[] args) throws IOException{

        //------------------------------
        //write random values to a file 
        //------------------------------

        //set up the file reference variable 
        File assignment1 = new File("assignment1.txt"); 

        //create the file and open it for writing 
        PrintWriter fout = new PrintWriter(assignment1); 

        //generate two random values between 1 and 15 
        int size1 = (int) ((Math.random() * 15) + 1); 
        int size2 = (int) ((Math.random() * 15) + 1); 

        //print out size1 and size 2 
        System.out.println("Size 1: " + size1);
        System.out.println("Size 2: " + size2);


        //write size1+size2 random values between 0 and 49 to a file using a for loop 
        for (int i = 0; i < size1+size2; i++) {

            //generate a random number between 0 and 49
            int random = (int) (Math.random() * 50); 

            //write the value to the file 
            fout.println(random);

            //send it to the console 
            System.out.println(random);

        }

        //print out line to mark end of writing 
        System.out.println("--------------------------------------------------------"); 

        //close the file 
        fout.close();

        //---------------------------
        //fill two arrays with values 
        //---------------------------

        //open the file for reading 
        Scanner fin = new Scanner(assignment1); 

        //create an array of size 1 
        int[] array1 = new int[size1]; 

        //read values from file into array 
        for(int i = 0; i < size1; i++) {

            array1[i] = fin.nextInt(); 
        }

        //report the reading 
        System.out.println("Read " + size1 + " values from file and placed into array1");
        System.out.println("Read " + size2 + " values from file and placed into array2");
        

        //create an array of size 2 
        int[] array2 = new int[size2]; 

        //read values from file into array
        for(int i = 0; i < size2; i++) {
            
            array2[i] = fin.nextInt(); 
        }

        //sort array1 and array2 using the .sort() method
        Arrays.sort(array1);
        Arrays.sort(array2); 

        //---------------------------
        //combine array1 and array2
        //---------------------------

        //create merged array of size size1+size2
        int[] mergedArray = new int[size1+size2]; 

        //iterator variables for array1 and array2 and merged array
        int i = 0;
        int j = 0; 
        int k = 0; 

        //while loop to iterate through both arrays at the same time include k < size1+size2 as a precaution
        while (i < size1 && j < size2 && k < (size1+size2)) {

            //if array 1 has the smaller value 
            if (array1[i] < array2[j]) {

                //add the array 1 value 
                mergedArray[k] = array1[i]; 

                //step throgh array 1 
                i++; 

            //if array 2 has the smaller value 
            } else {

                //add the array 2 value 
                mergedArray[k] = array2[j];

                //step through array 2 
                j++; 
            }

            //step through the merged array 
            k++; 
        }

        //while loop to step through array1 if applicable (will not execute if array 1 has already been iterated through as i will be equal to size1)
        while (i < size1 && k < (size1+size2)) {

            //add elements to merged array
            mergedArray[k] = array1[i];

            //step through both arrays
            k++;
            i++; 
        }

        //while loop to step through array2 if applicable (will not execute if array 2 has already been iterated through as j will be equal to size2)
        while (j < size2  && k < (size1+size2)) {

            //add elements to merged array
            mergedArray[k] = array2[j];

            //step through both arrays
            k++;
            j++; 
        }

        //display values in sorted merged array 
        System.out.println("Random values in sorted order in merged array:"); 
        for (int iterator = 0; iterator < size1+size2; iterator++) {
            System.out.println(mergedArray[iterator]);
        }

        //tell the user where the file is
        System.out.println("File is in directory: " + assignment1.getAbsolutePath());

        //close the file 
        fin.close();
    }
}