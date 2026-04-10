/*
Shane David 
CS140 M/W
Due 12/3/2025
Assignment 10
Description: This assignment utilizes a self created BinaryTree class that contains parrots
to print out a song according to the parrot's given phrase. It does this by using a level order 
traversal. It then uses a recursive traversal to print out all of the names of the parrots on the leaf nodes
*/

import java.io.File; //for files
import java.util.Scanner; //for file reading 
import java.io.IOException; //for error handling
import java.lang.Comparable; //to make the parrot class comparable 
import java.util.LinkedList;
import java.util.Queue; //for the level order method 

public class ShaneDavidAssignment10 {
    public static void main(String[] args) throws IOException {

        //create instance of the tree
        BinaryTree parrotTree = new BinaryTree(); 

        //open parrot file for reading 
        File parrots = new File("parrots.txt"); 
        Scanner fin = new Scanner(parrots); 

        //read in parrots and add them to the tree
        while (fin.hasNext()) {

            int id = fin.nextInt();
            String name = fin.next(); 
            String songPhrase = fin.nextLine().trim(); 

            Parrot aParrot = new Parrot(id, name, songPhrase);
            parrotTree.insert(aParrot); 
        }

        //print out song with the level traverse
        System.out.println("Parrot Christmas Song");
        System.out.println("---------------------"); 
        parrotTree.levelOrder();

        System.out.println(""); 

        //print out leaves names with the recursive traverse 
        System.out.println("Parrots one Leave Nodes");
        System.out.println("-----------------------"); 
        parrotTree.visitLeaves();

        //close the file 
        fin.close();
    }
}

//------------
//Parrot Class
//------------
class Parrot implements Comparable<Parrot> {

    //private data
    private int id;
    private String name;
    private String songPhrase; 

    //constructor
    public Parrot(int id, String name, String songPhrase) {
        this.id = id;
        this.name = name;
        this.songPhrase = songPhrase; 
    }

    //getters 
    public String getName() {
        return name;
    }

    public String getSongPhrase() {
        return songPhrase; 
    }

    //public methods
    public int compareTo(Parrot otherParrot) {

        if (this.id < otherParrot.id) {
            return -1; 
        } else if (this.id > otherParrot.id) {
            return 1; 
        } else {
            return 0; 
        }

    }
}

//------------------
//Binary Tree Class
//------------------
class BinaryTree {

    //private data
    private TreeNode root;

    //constructor
    public BinaryTree() {
        root = null; 
    }

    //public methods

    //insert method, this method recieves a parrot and adds it to the tree in the proper position
    //by travelling to the tree left if the value of the passed in parrot is less than the current parrot
    //and right if it is greater then. Once it reaches a leaf it adds the parrot to the tree and returns true.
    //If it finds a duplicate it returns false and does not add anything to the tree
    public boolean insert(Parrot parrotToAdd) { 

        //make the parrot the root if the tree is empty 
        if (root == null) {

            root = new TreeNode(parrotToAdd); 

        //otherwise try to insert 
        } else {

            //create parent and current to march through the tree 
            //and keep track of the needed Nodes
            TreeNode parent = null;
            TreeNode current = root; 

            while (current != null) {
                //left 
                if (parrotToAdd.compareTo(current.parrot) == -1) {

                    parent = current;
                    current = current.left; 
                
                //right 
                } else if (parrotToAdd.compareTo(current.parrot) == 1) {

                    parent = current;
                    current = current.right; 

                //dupe 
                } else {
                    return false; 
                }
            }

            //once we have progressed to the proper leaf add either left or right depending on the parent 
            if (parrotToAdd.compareTo(parent.parrot) == -1) {
                parent.left = new TreeNode(parrotToAdd);
            } else if (parrotToAdd.compareTo(parent.parrot) == 1) {
                parent.right = new TreeNode(parrotToAdd); 
            }
        }

        //if we make it here it has been added so return true 
        return true; 
    }

    //this method does the level traversal of the binary tree and prints out the parrot phrase at every node it visits
    //it uses a queue to store the below left from right and then removes from the front of the queue to visit nodes
    //it is done when the queue is empty 
    public void levelOrder() {

        //if the tree actually as elements in it start the traversal 
        if (root != null) {

            //create the queue to store nodes and add the root 
            Queue<TreeNode> levelQueue = new LinkedList<>(); 
            levelQueue.offer(root); 

            //string for storing the song
            String song = ""; 

            //while the root is not empty traverse by moving 
            //through the queue from front to back and adding children to the queue if they exist 
            while (!levelQueue.isEmpty()) {

                TreeNode current = levelQueue.remove(); 
                song += current.parrot.getSongPhrase() + " "; 

                //if the children exist add them to the queue left then right
                if (current.left != null) {
                    levelQueue.offer(current.left); 
                }
                if (current.right != null) {
                    levelQueue.offer(current.right); 
                }

            }

            //print out the song once the traversal is over
            System.out.println(song); 
            
        }
    }

    //this method calls the private visit leaves with the root because
    //the root can only be passed in within the class
    public void visitLeaves() {
        visitLeaves(root);
    }

    //private methods

    //this class uses a recursive post order traversal to travers thorugh the tree
    //once it finds a leaf node (both children are null) it prints out the name of the parrot
    private void visitLeaves(TreeNode root) {

        //recursive case
        if (root != null) {

            //vist left 
            visitLeaves(root.left);

            //visit right 
            visitLeaves(root.right);

            //print out name if leaf 
            if (root.right == null && root.left == null) {
                System.out.println(root.parrot.getName()); 
            }
        }
    }



    //private inner class 
    private static class TreeNode {
        private Parrot parrot;
	    private TreeNode left;
	    private TreeNode right;
	
        public TreeNode(Parrot parrot) {
            this.parrot = parrot;
            left = null;
            right = null; 
        }
    }
}