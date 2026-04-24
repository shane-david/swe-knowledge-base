/*
Shane David
4/24/2026
This program implements a priority queue and a min heap 
the min heap recieves an array and turns it into a min heap using the 2i + 1 2i + 2 formula
the priority queuee uses an array of nodes that sorts by priority as the nodes area dded
*/

#include <iostream> // preprocessor directive for i/o
#include <string>   // preprocessor directive for strings

using namespace std;

// the min heap class takes in an array at any order and turns it into a heap 
// so that it can follow the rule of 2i+1 2i+2 to get the children of each "node"
// it contains methods for adding and accessing the heap 
class MinHeap {
private:

    //-------------
    //private data
    //-------------
    int* _arr;   // this int pointer represents the array we will create dynamiccaly once the MinHeap is created
    int  _size;  // the size of the array 

    //---------------
    //private methods
    //---------------

    // this methods turns the array at _arr into a heap, it starts at the last parent and does the necessary swaps up 
    // the heap so that the smallest value ends up at the top, once the swap method returns it moves on to the next parent and repeats 
    // it is private because when the array needs to be turned into a heap is handled internally only by the calss
    void arrToHeap() {

        // we want to stop the swaps at the bottomrightmost child and the procedue left and up the heap 
        // the last elment is _size-1, so the last element's parent will be ((_size-1) - 1) / 2 or _size-2 / 2, start there
        // the next parent we want to check will just be on bewlo that so i-- until we reach the start (0)
        for (int i = (_size-2) / 2; i >= 0; i--) {
            swapUpHeap(i); 
        }
    }

    // this method takes in an index of the array, starts there, finds the children, then swaps
    // both of those children as far up the heap as they need to go, it does so recursively 
    void swapUpHeap(int parent) {

        // get the children's from the passed in parent using the 2i+1 2i+2 formula
        int leftChild = 2*parent + 1;
        int rightChild = 2*parent + 2; 

        // set the parent to the current smallest value 
        int smallestValue = parent; 

        //if the left child is not the end of the array (< size) and the child is smaller than 
        //our current smallest value, set the smallest value to be the leftChild 
        if (leftChild < _size && _arr[leftChild] < _arr[smallestValue]) {
            smallestValue = leftChild; 
        }

        //if the right child is not at the end of the array (< size) and the child is smaller than 
        //our current smalles value, set the smallest value to be the rightChild
        if (rightChild < _size && _arr[rightChild] < _arr[smallestValue]) {
            smallestValue = rightChild; 
        }

        //if the parent is not the smallest value, swap it with the smalles value 
        if (parent != smallestValue) {

            //swap
            int temp = _arr[parent];
            _arr[parent] = _arr[smallestValue];
            _arr[smallestValue] = temp; 

            //call this method on the new smallest value to see if it needs to be swapped further up the heap
            swapUpHeap(smallestValue); 
        }
    }

public:

    //-------------
    //constructors
    //-------------

    // default constructor that just sets default values
    MinHeap() {
        _arr = nullptr;
        _size = 0; 
    }

    // paramterized constructor that recieves an array and a size and creates the heap
    MinHeap(int inputArray[], int inputSize) {

        // set the size
        _size = inputSize;

        // dynamically allocated oru array at size _size
        _arr = new int[_size]; 

        // fill our array with the input array
        for (int i = 0; i < inputSize; i++) {
            _arr[i] = inputArray[i]; 
        }

        // call the method to turn it into a heap
        arrToHeap(); 
    }

    //---------------
    //public methods
    //---------------

    // the printTree method iterates through the arr once it is a heap
    // and prints it in a format to display what it looks like as a heap
    void printTree() {

        //start at the top level of size 1 (root)
        int level = 0, numsInLevel = 1; 

        //iterate through the array 
        int i = 0; 
        while (i < _size) {

            //print the spacing so that the nums are centered 
            for (int space = 0; space < (_size / numsInLevel); space++) {
                cout << " "; 
            }

            //print all the nodes on this level
            for (int j = 0; j < numsInLevel && i < _size; j++) {

                // print the nums
                cout << _arr[i];

                // print spacing between the next nume 
                for (int space = 0; space < (_size / numsInLevel); space++) {
                    cout << "  "; 
                }

                // increase i 
                i++; 
            }
            cout << endl; 

            // go to the next level
            level++;

            // increase the lvel size (it always doubles because each child gets two more children)
            numsInLevel *= 2; 
        }

    }

    //-----------
    //Destructors
    //-----------

    //delete the memory from the array
    ~MinHeap() {
        delete[] _arr; 
    }
};

// the IPrintString interface defines a pure virtual method for printing 
class IPrintString {
public:
    virtual void printMessage() = 0; 
};

// the node class is used by the priority queue  it is how data is represented 
// it implements the the PrintString interface to have a method to print its string 
// and the data it contains is a string message and an integer representing its priority
class Node : public IPrintString {
public:

    // data that the node contains, string message and int priority
    string message;
    int priority; 

    // define the method for printing the message
    void printMessage() override {
        cout << message << endl; 
    }

    // default constructor
    Node() {
        message = "NONE";
        priority = -1; 
    }

    // paramterized constructor for creating nodes
    Node(string message, int priority) {
        this->message = message;
        this->priority = priority; 
    }
}; 

// the prioirity queue class contains an array of nodes the represents a priority quueue
// to emulate this behavior it sorts the array of nodes each time that a node is added 
// and there is a way to print the messages from all the nodes by priority
class PriorityQueue {
private:

    //-------------
    //private data
    //-------------

    Node* _arr; // the array represenint teh PQ, as a pionter to dynamically allocate 
    int _size;  // the current size of the PQ

    //----------------
    //private methods
    //----------------

    // this is a basic bubble sort to sort the PQ after an element is added
    // it is priveate becuase it will be called internally after every addition
    // and since the PQ is always sorted, it would never need to be called outside the calss
    void sort() {

        //swapped bool to end early if possible 
        bool swapped;

        //amount of times to pass through array 
        for (int i = 0; i < _size - 1; i++) {

            //set swapped to false before starting swaps
            swapped = false;

            //go through array to do swaps if necessary
            for (int j = 0; j < _size - i - 1; j++) {

                //if a swap is needed sawp
                if (_arr[j].priority > _arr[j + 1].priority) {
                    Node temp = _arr[j];
                    _arr[j] = _arr[j + 1];
                    _arr[j + 1] = temp;
                    swapped = true;
                }
            }

            //break out if there were no swaps on that pass 
            if (!swapped) break;
        }
    }

public:

    //-------------
    //constructors
    //-------------

    // default constructo the define default values and intialize pointer
    PriorityQueue() {
        _arr = nullptr;
        _size = 0; 
    }

    //---------------
    //public methods
    //---------------

    // this method adds a node to the pq, since it is an array 
    // it creates a new array at the increased size, copies over the elements
    // then adds the last element, cleans up memory, then sorts it 
    void add(Node newNode) {

        // increase the size by 1
        _size++; 

        // create a new array at size one bigger
        Node* newArr = new Node[_size]; 

        // copy over elements from old array if there is any
        for (int i = 0; i < _size-1; i++) {
            newArr[i] = _arr[i]; 
        }

        // put in the new element
        newArr[_size-1] = newNode; 

        // deleete the memory of the old array
        delete[] _arr; 

        // set the PQ's array to point at the new arr
        _arr = newArr; 

        // sort the array to maintains its priority order 
        sort(); 
    }

    // this method prints the messages off all the nodes in the array 
    // from highest priority to lowest
    void printNodeMessages() {

        // iterate through the array
        for (int i = 0; i < _size; i++) {
            _arr[i].printMessage(); 
        }
    }

    //-----------
    //Destructors
    //-----------

    // deallocate the arrays memory
    ~PriorityQueue() {
        delete[] _arr; 
    }

};

int main() {

    //------------------
    //HEAP DEMONSTRATION
    //------------------

    cout << "Printing min heap..." << endl; 

    // create an array to turn into a heap
    int normalArr[] = {100, 42, 5, 3, 11, 1, 99}; 

    // create the heap, passing in the array and sie
    MinHeap minHeap(normalArr, 7);

    // print the tree to make sure it worked
    minHeap.printTree();

    cout << endl << endl; 

    //----------------------------
    //PRIORITY QUEUE DEMONSTRATION
    //----------------------------

    cout << "Creating prioirity queue..." << endl; 

    // create the priority queue 
    PriorityQueue aPriorityQueue; 

    // create 3 nodes 
    Node node1("I am node 1 of priority 1", 1); 
    Node node2("I am node 2 of priority 2", 2); 
    Node node3("I am node 3 of priority 3", 3); 

    // add nodes to the pq in order 3 1 2 
    aPriorityQueue.add(node3);
    aPriorityQueue.add(node1);
    aPriorityQueue.add(node2);

    // print out the node's message to showcase the sorting
    cout << "Printing priority queue..." << endl; 
    aPriorityQueue.printNodeMessages(); 


    return 0; 
}