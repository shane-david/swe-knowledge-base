/* Shane David 
 * CS1450 M/W
 * 10/8/25
 * Assignment 5
 * This assignment experiments with the stack class in the JCF by creating a stack
 * counting the even numbers and printing the stack. It then defines and uses a 
 * GenericStack class the emulates the behavior of a stack. With this GenericStack
 * main creates stacks, merges them, sorts them, and removes any duplicates for integers 
 * and strings 
 */

import java.util.Stack; //for stacks 
import java.util.ArrayList; //for GenericStack
import java.io.File; //for file i/o
import java.io.IOException; //for exceptions 
import java.util.Scanner; // to read from file 


public class ShaneDavidAssignment5 {
    public static void main(String[] args) throws IOException {

        //--------
        //Part 1
        //--------

        //create the values array 
        int[] values = {12,9,3,10,4,2,5,15,7,11,14}; 

        //create stack and fill it with values 
        Stack<Integer> aJavaStack = new Stack<>(); 

        for (int i = 0; i < values.length; i++) {
            aJavaStack.push(values[i]); 
        }

        //call find num evens 
        int javaStackEvens = findNumEven(aJavaStack); 

        //print out the stack and the amount of evens 
        System.out.println("Stack Values After Find Number of Even Values");
        System.out.println("-------------------------------------------------");
        printStack(aJavaStack);
        System.out.println("\nNumber of Even Values: " + javaStackEvens); 
        System.out.println(""); 

        //------------------
        //Part 2 int stacks
        //------------------

        //create and fill int stacks 
        GenericStack<Integer> intStack1 = new GenericStack<>();
        GenericStack<Integer> intStack2 = new GenericStack<>();
        fillIntStack("Numbers1.txt", intStack1);
        fillIntStack("Numbers2.txt", intStack2);

        //print int stacks 
        System.out.println("Values read from Numbers1.txt and pushed onto stack1");
        System.out.println("----------------------------------------------------");
        printStack(intStack1);
        System.out.println("");

        System.out.println("Values read from Numbers2.txt and pushed onto stack2");
        System.out.println("----------------------------------------------------");
        printStack(intStack2);
        System.out.println(""); 

        //combine int stacks 
        GenericStack<Integer> combinedIntStack = combineStacks(intStack1, intStack2); 

        //sort int stack 
        GenericStack<Integer> sortedIntStack = new GenericStack<>();
        sortStack(combinedIntStack, sortedIntStack);

        //print the combined sorted stack
        System.out.println("Combined Number Stack With Duplicates - lowest value on top");
        System.out.println("-----------------------------------------------------------"); 
        printStack(sortedIntStack);
        System.out.println(""); 


        //remove the duplicates into now dupe stack
        GenericStack<Integer> dupeIntStack = removeDuplicates(sortedIntStack); 

        //print out duplicates removed
        System.out.println("Combined Number Stack Duplicates Removed - lowest value on top");
        System.out.println("-----------------------------------------------------------"); 
        printStack(sortedIntStack);
        System.out.println(""); 


        //print out duplicates 
        System.out.println("Duplicates Number Stack - largest value on top");
        System.out.println("--------------------------------------------------");
        printStack(dupeIntStack);
        System.out.println(""); 

        //---------------------
        //Part 2 string stacks
        //---------------------

        //create and fill string stacks
        GenericStack<String> stringStack1 = new GenericStack<>();
        GenericStack<String> stringStack2 = new GenericStack<>(); 
        fillStringStack("Strings1.txt", stringStack1);
        fillStringStack("Strings2.txt", stringStack2);

        //print string stacks
        System.out.println("Values read from Strings1.txt and pushed onto stack1");
        System.out.println("-------------------------------------------------------");
        printStack(stringStack1);
        System.out.println("");

        System.out.println("Values read from Strings2.txt and pushed onto stack2");
        System.out.println("-------------------------------------------------------");
        printStack(stringStack2);
        System.out.println(""); 

        //combine string stacks
        GenericStack<String> combinedStringStack = combineStacks(stringStack1, stringStack2); 

        //sort int stack 
        GenericStack<String> sortedStringStack = new GenericStack<>(); 
        sortStack(combinedStringStack, sortedStringStack);

        //print the combined sorted stack 
        System.out.println("Combined String Stack With Duplicates - lowest value on top");
        System.out.println("------------------------------------------------------------");
        printStack(sortedStringStack);
        System.out.println(""); 

        //remove duplicates into new dupe stack
        GenericStack<String> dupeStringStack = removeDuplicates(sortedStringStack); 

        //print out duplicates removed
        System.out.println("Combined String Stack Duplicates Removed - lowest value on top"); 
        System.out.println("--------------------------------------------------------------");
        printStack(sortedStringStack);
        System.out.println(""); 

        //print out duplicates
        System.out.println("Duplicates String Stack - largest value on top");
        System.out.println("----------------------------------------------"); 
        printStack(dupeStringStack);

    }

    public static int findNumEven(Stack<Integer> stack) {

        //create tempStack to store values while we iterate
        Stack<Integer> tempStack = new Stack<>();

        //count evens
        int numEvens = 0; 

        while (!stack.isEmpty()) {

            int value = stack.pop(); 

            if (value % 2 == 0) {
                numEvens++; 
            }

            tempStack.push(value); 
        }

        //refill the original stack
        while (!tempStack.isEmpty()) {
            stack.push(tempStack.pop()); 
        }

        //return num evens 
        return numEvens; 
    }

    public static void printStack(Stack<Integer> stack) {

        //creat temp stack to store popped values 
        Stack<Integer> tempStack = new Stack<>(); 

        //print out values from stack and store in temp stack
        while(!stack.isEmpty()) {

            int value = stack.pop();
            System.out.println(value);
            tempStack.push(value); 
        }

        //refill the original stack
        while(!tempStack.isEmpty()) {
            stack.push(tempStack.pop()); 
        }
    }

    public static void fillIntStack(String filename, GenericStack<Integer> stack) throws IOException {

        File intFile = new File(filename); 
        Scanner fin = new Scanner(intFile); 

        while (fin.hasNextInt()) {
            int value = fin.nextInt(); 
            stack.push(value);
        }

        fin.close();
    }

    public static void fillStringStack(String filename, GenericStack<String> stack) throws IOException {

        File stringFIle = new File(filename);
        Scanner fin = new Scanner(stringFIle);

        while (fin.hasNextLine()) {
            String value = fin.nextLine(); 
            stack.push(value); 
        }

        fin.close();
    }

    public static <E> void printStack(GenericStack<E> stack) {

        //create temp stack
        GenericStack<E> tempStack = new GenericStack<>(); 

        //print out values and store in temp stack
        while (!stack.isEmpty()) {
            E value = stack.pop(); 
            System.out.println(value); 
            tempStack.push(value);
        }

        //put values in original stack 
        while (!tempStack.isEmpty()) {
            stack.push(tempStack.pop()); 
        }
    }

    public static <E> GenericStack<E> combineStacks(GenericStack<E> stack1, GenericStack<E> stack2) {

        //create combined stack 
        GenericStack<E> combinedStack = new GenericStack<>(); 

        //add elements from stack1
        while(!stack1.isEmpty()) {
            combinedStack.push(stack1.pop());
        }

        //add elements from stack2
        while(!stack2.isEmpty()) {
            combinedStack.push(stack2.pop()); 
        }

        //return result
        return combinedStack; 
    }

    public static <E extends Comparable<E>> void sortStack(GenericStack<E> unsortedStack, GenericStack<E> sortedStack) {

        //start iterating through unsorted stack
        while(!unsortedStack.isEmpty()) {

            E value = unsortedStack.pop(); 

            //if the unsorted stack has values in it, and they are smaller than the value we need to put on top, move them
            //to the unsorted stack until theyre all gone or there is a bigger value on top 
            while(!sortedStack.isEmpty() && sortedStack.peek().compareTo(value) < 0) {
                unsortedStack.push(sortedStack.pop()); 
            }

            //once the value is ready to be put on top put it on top
            sortedStack.push(value);
        }
    }

    public static <E extends Comparable<E>> GenericStack<E> removeDuplicates(GenericStack<E> stack) {

        //create temp and dupes stack
        GenericStack<E> dupes = new GenericStack<>();
        GenericStack<E> tempStack = new GenericStack<>(); 

        //get previous value to compare
        E previousValue = stack.pop(); 

        //iterate through stack 
        while (!stack.isEmpty()) {

            //pop out the next value 
            E currValue = stack.pop(); 

            //if they are the same put it into dupes stack 
            if (previousValue.compareTo(currValue) == 0) {

                dupes.push(currValue);

            //otherwise put in temp stack and set prevValue to currValue
            } else {

                tempStack.push(previousValue);
                previousValue = currValue; 

            }

            //if it is the last value put the current value into the stack
            if (stack.isEmpty()) {
                tempStack.push(currValue);
            } 
        }

        //put temp stack back into original stack
        while (!tempStack.isEmpty()) {
            stack.push(tempStack.pop()); 
        }

        //return dupes stack
        return dupes; 
    }
}



//-------------------
//GenericStack class
//-------------------
class GenericStack<E> {

    //private data 
    private ArrayList<E> list; 

    //constructor
    GenericStack() {
        list = new ArrayList<>(); 
    }

    //public methods

    public boolean isEmpty() {
        return list.isEmpty(); 
    }

    public int getSize() {
        return list.size(); 
    }

    public E peek() {
        return list.get(list.size() - 1); 
    }

    public E pop() {
        int position = list.size() - 1;
        E value = list.get(position); 
        list.remove(position); 
        return value; 
    }

    public void push(E value) {
        int position = list.size();
        list.add(position, value); 
    }
}
