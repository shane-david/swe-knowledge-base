/* Shane David
 * CS1450 M/W
 * 11/5/2025
 * Assignment 8
 * This program decodes a secret message read in from files using array lists and queues 
 * it reads in characters from the first file, integers from the second file, and a decoding key 
 * it then uses a translator object to translate the message and return a string 
 */

import java.util.Scanner; //for opening files for reading 
import java.io.File; //for File object
import java.io.IOException; //for exepction throws
import java.util.ArrayList; //for array lists
import java.util.Queue; //for queues
import java.util.LinkedList; //to make queues
import java.util.Stack; //for stacks 
import java.util.Iterator; //for iterators 

public class ShaneDavidAssignment8 {
    public static void main(String[] args) throws IOException {

        //------------
        //Array Lists
        //------------

        //create file objects 
        File ArrayKeyFile = new File("ArrayKey.txt");
        File ArrayPart1File = new File("ArrayPart1.txt");
        File ArrayPart2File = new File("ArrayPart2.txt");
        
        //open for reading 
        Scanner arrayKeyFin = new Scanner(ArrayKeyFile);
        Scanner arrayPart1Fin = new Scanner(ArrayPart1File);
        Scanner arrayPart2Fin = new Scanner(ArrayPart2File); 

        //create characters array list 
        ArrayList<Character> arrayCharacters = new ArrayList<>();
        
        //read in file as a string 
        String arrayPart1String = arrayPart1Fin.nextLine(); 

        //add string chracters to array list
        for (int i = 0; i < arrayPart1String.length(); i++) {
            char character = arrayPart1String.charAt(i); 
            arrayCharacters.add(character);
        }

        //create integers array list 
        ArrayList<Integer> arrayIntegers = new ArrayList<>(); 
        
        //add integers to array list 
        while (arrayPart2Fin.hasNextInt()) {
            int arrayInteger = arrayPart2Fin.nextInt(); 
            arrayIntegers.add(arrayInteger); 
        }

        //create key values array list 
        ArrayList<Integer> arrayKeys = new ArrayList<>(); 

        //add keys to array list 
        while (arrayKeyFin.hasNextInt()) {
            int arrayKey = arrayKeyFin.nextInt();
            arrayKeys.add(arrayKey); 
        }

        //create iterators
        Iterator<Character> arrayCharIterator = arrayCharacters.iterator();
        Iterator<Integer> arrayIntIterator = arrayIntegers.iterator();
        Iterator<Integer> arrayKeyIterator = arrayKeys.iterator(); 

        //create translator object
        Translator aTranslator = new Translator(); 

        //create and print out string 
        String arrayMessage = aTranslator.translate(arrayCharIterator, arrayIntIterator, arrayKeyIterator);

        System.out.println("For the 1st set of files (ArrayPart1.txt, ArrayPart2.txt, ArrayKey.txt)");
        System.out.println("The secret string is: " + arrayMessage);

        //close files 
        arrayPart1Fin.close();
        arrayPart2Fin.close();
        arrayKeyFin.close();

        //-------
        //Queues
        //-------

         //create file objects 
        File QueueKeyFile = new File("QueueKey.txt");
        File QueuePart1File = new File("QueuePart1.txt");
        File QueuePart2File = new File("QueuePart2.txt");
        
        //open for reading 
        Scanner QueueKeyFin = new Scanner(QueueKeyFile);
        Scanner QueuePart1Fin = new Scanner(QueuePart1File);
        Scanner QueuePart2Fin = new Scanner(QueuePart2File); 

        //create characters array list 
        Queue<Character> queueCharacters = new LinkedList<>();
        
        //read in file as a string 
        String queuePart1String = QueuePart1Fin.nextLine(); 

        //add string chracters to array list
        for (int i = 0; i < queuePart1String.length(); i++) {
            char character = queuePart1String.charAt(i); 
            queueCharacters.add(character);
        }

        //create integers array list 
        Queue<Integer> queueIntegers = new LinkedList<>(); 
        
        //add integers to array list 
        while (QueuePart2Fin.hasNextInt()) {
            int queueInteger = QueuePart2Fin.nextInt(); 
            queueIntegers.add(queueInteger); 
        }

        //create key values array list 
        Queue<Integer> queueKeys = new LinkedList<>(); 

        //add keys to array list 
        while (QueueKeyFin.hasNextInt()) {
            int queueKey = QueueKeyFin.nextInt();
            queueKeys.add(queueKey); 
        }

        //create iterators
        Iterator<Character> queueCharIterator = queueCharacters.iterator();
        Iterator<Integer> queueIntIterator = queueIntegers.iterator();
        Iterator<Integer> queueKeyIterator = queueKeys.iterator(); 

        //create and print out string 
        String queueMessage = aTranslator.translate(queueCharIterator, queueIntIterator, queueKeyIterator);

        System.out.println("For the 2nd set of files (QueuePart1.txt, QueuePart2.txt, QueueKey.txt)");
        System.out.println("The secret string is: " + queueMessage);

        //close files 
        QueuePart1Fin.close();
        QueuePart2Fin.close();
        QueueKeyFin.close();

    }
 }

 //translator class 
 class Translator {

    //private data fields
    private DecodingStack aStack; 

    //constructor
    public Translator() {
        aStack = new DecodingStack(); 
    }

    //public methods
    public String translate(Iterator<Character> part1Iterator, Iterator<Integer> part2Iterator, Iterator<Integer> keyIterator) {

        //iterate through the keys 
        while (keyIterator.hasNext()) {
            
            int key = keyIterator.next();

            //if it is a 0 get from part 1
            if (key == 0 && part1Iterator.hasNext()) {

                char part1Char = part1Iterator.next();
                aStack.push(part1Char);

            //otherwise convert to char and push onto stack 
            } else if (key == 1 && part2Iterator.hasNext()) {

                int part2Int = part2Iterator.next();
                aStack.push((char)part2Int);

            }
        }

        //create return string
        String returnString = ""; 

        //iterate through decoding stack
        while (!aStack.isEmpty()) {
            char value = aStack.pop(); 
            returnString += value; 
        }

        return returnString; 
    }
 }

 //decoding stack
 class DecodingStack {

    //private data fields
    private Stack<Character> aStack; 

    //constructor
    public DecodingStack() {
        aStack = new Stack<>(); 
    }

    //public stack methods

    //whether or not the stack is empty
    boolean isEmpty() {
        return aStack.isEmpty(); 
    }

    //get the size of the stack
    int size() {
        return aStack.size(); 
    }

    //push a character onto the stack 
    void push(Character value) {
        aStack.push(value);
    }

    //remove and return a value off of the top of the stack 
    char pop() {
        return aStack.pop(); 
    }
 }