/*
Basic Program representing a Binary Search Tree in C++
it contains a Node class and a Binary Search Tree calss that can
add nodes, remove leaves, print every value of the tree in order, and search
the BST, returning true if there is a matching value in the BST
*/

#include <iostream> // preprocessor directive for input and output 
#include <ctime>    // to seed rand
#include <random>   // for rng

using namespace std; 

class Node {
private:

    int   _data;  // int representing the data stored at the node 
    Node* _left;  // Node pointer representing the left child of the node in the BST
    Node* _right; // Node pointer representing the right child of the node in the BST

public:

    //default constructor
    Node() = default; 

    //paramaterized constructor that sets the data and sets the left and right nodes to NULL
    Node(int data) {
        _data = data;
        _left = nullptr;
        _right = nullptr; 
    }

    //--------
    //getters
    //--------

    int getData() {
        return _data;
    }

    Node* getLeft() {
        return _left; 
    }

    Node* getRight() {
        return _right; 
    }

    //--------
    //setters
    //--------

    void setData(int data) {
        _data = data; 
    }

    void setRight(Node* right) {
        _right = right;
    }

    void setLeft(Node* left) {
        _left = left; 
    }
};

class BinarySearchTree {
private:

    //-------------
    //private data
    //-------------

    Node* _root; // Node pointer that points to the root of the BST

    // the destroy tree method is called by the destructor only so it is private
    // it does a post order traversal so that children are deleted first, then deletes the node from memory
    void destroyTree(Node* newRoot) {

        if (newRoot != nullptr) {

            //go left
            destroyTree(newRoot->getLeft());

            //go right
            destroyTree(newRoot->getRight()); 

            //delete node
            delete newRoot; 

        }
    }
public:

    //default constructor 
    BinarySearchTree() = default; 

    //---------------
    //public methods
    //---------------

    // method that addes a node to the tree in the correct postion this method creates handles the sitaution where we have no Nodes,
    // no leaves or need to iterate through the binary search tree by creating a current Node* that iterats goes left for less than and right for greater than 
    // until it reaches a leaf then addes the node in the right spot, if there is a duplicate value it returns false and does not add the value to the BST
    bool addNode(Node* toAdd) {

        // if there are no nodes we start the tree by creating the root 
        if (_root == nullptr) {

            _root = toAdd; 
            return true; 

        //otherwise try to insert the node, no leaves is handled by default, the iteration just stops almost immediately 
        } else {

            // create a current Node and a parent node that we step through the BST until the current node reaches Null, and therefore we are ready to add 
            Node* currentNode = _root;  //start current at the root 
            Node* parentNode = nullptr; //there is not parent to the root so we start at null

            // step through the BST until the currentNode is null
            while (currentNode != nullptr) {

                // go left if toAdd is less than the current node 
                if (toAdd->getData() < currentNode->getData()) {

                    parentNode = currentNode;             // progress parent to what the current is 
                    currentNode = currentNode->getLeft(); // progress current left 

                // go right if toAdd is greater than the current node
                } else if (toAdd->getData() > currentNode->getData()) {

                    parentNode = currentNode;              // progress parent to what the current is 
                    currentNode = currentNode->getRight(); // progress current right 
                
                // otherwise they are equal, return false and break out of the loop 
                } else {

                    return false; 

                }
            }

            // now that current is at a leaf node, add either right or left depening on value with respect to the parent
            if (toAdd->getData() < parentNode->getData()) {
                parentNode->setLeft(toAdd); 
            } else if (toAdd->getData() > parentNode->getData()) {
                parentNode->setRight(toAdd); 
            }

            //return true if we have made it to this point to indicate that the value was added to the BST
            return true; 
        }
    }

    // this method steps through the tree in the same exact way the addNode does, it handles the case that the root is the one the user is trying to remove 
    // and returns false if the user tries to remove a node that is not a leaf or does not exist in the binary search tree 
    bool removeLeafNode(int value) { 

        //if the tree is empty return false 
        if (_root == nullptr) {

            return false; 

        // otherwise iterate through it looking for value 
        } else {

            // create a current and parent node to keep track of where we are in the BST
            Node* currentNode = _root;
            Node* parentNode = nullptr; 

            // while current is not the value and not null progress propelry
            while (currentNode != nullptr && currentNode->getData() != value) {

                // go left if value is less than the current node 
                if (value < currentNode->getData()) {

                    parentNode = currentNode;             // progress parent to what the current is 
                    currentNode = currentNode->getLeft(); // progress current left 

                // go right if toAdd is greater than the current node
                } else if (value > currentNode->getData()) {

                    parentNode = currentNode;              // progress parent to what the current is 
                    currentNode = currentNode->getRight(); // progress current right 
                
                } 
            }

            //if current is null the value was not in the tree so return false
            if (currentNode == nullptr) {

                return false;
            
            //otherwise if it is not a leaf return false, do not remove
            } else if (currentNode->getLeft() != nullptr || currentNode->getRight() != nullptr) {

                return false; 

            //otherwise the value is in the tree and it is a leaf 
            } else {

                //if we are at the root, just set it to nullptr
                if (parentNode == nullptr) {
                    _root = nullptr; 

                //otherwise see if we need to delete the left or right link 
                } else if (parentNode->getLeft() == currentNode) {
                    parentNode->setLeft(nullptr); 
                } else {
                    parentNode->setRight(nullptr); 
                }

                // delete the node 
                delete currentNode;
                currentNode = nullptr; 

                //return that it was deleted
                return true; 

            }

        }
    }

    //this method recursively searches through the BST, if it finds the value specified it returns true, if it gets to a null value it returns false becuase it was not in the BST
    bool search(Node* newRoot, int value) {

        // base case: newRoot is null, we have reached the end of the BST before finding the value
        if (newRoot == nullptr) {
            return false; 
        }

        // base case: we found the value, return treu
        if (newRoot->getData() == value) {
            return true; 
        }

        // recursive case: got left is less than newRoot and right if greater than newRoot
        if (value < newRoot->getData()) {
            return search(newRoot->getLeft(), value); 
        } else {
            return search(newRoot->getRight(), value); 
        }

    }

    // this method does an in order search recursive search of the binary search tree, printing our the value of each node 
    // the in order serach prints the nodes in sequential order because it visits all the left nodes (least) and then visits the right nodes (most)
    void printNodes(Node* newRoot) {

        // recursive case: keep going as long as the newRoot hase a valid value
        if (newRoot != nullptr) {

            //vist the left nodes recursively
            printNodes(newRoot->getLeft()); 

            //print out the values 
            cout << newRoot->getData() << endl;

            //visit the right nodes recursively
            printNodes(newRoot->getRight()); 
        }
    }

    //--------
    //getters
    //--------
    
    Node* getRoot() {
        return _root; 
    }

    //-----------
    //destructor
    //-----------

    ~BinarySearchTree() {  
        destroyTree(_root); 
    }
    

}; 


//simple main program that demonstrate the functinality of the BST
int main() {

    // seed the randomness 
    srand(time(NULL)); 

    cout << "Creating Binary Search Tree with 10 random values and 110 at the end..." << endl; 

    //creat a BST
    BinarySearchTree* bst1 = new BinarySearchTree(); 

    // put 10 random elements between 0 and 100 in the tree 
    int counter = 0;
    int randomNum = 0; 
    while (counter < 10) {

        //get a random number 
        randomNum = rand() % 101; 

        //create a node with that random number 
        Node* randomNode = new Node(randomNum); 

        //try to add number, if it is successful increase the counter 
        if (bst1->addNode(randomNode)) {

            counter++; 

        //if it was not added, clean up the garbage
        } else {
            delete randomNode;
            randomNode = nullptr; 
        }
    }

    //add 110 at the end so we know it is a leaf and can demonstrate removing later 
    int lastValue = 110;
    Node* lastNode = new Node(lastValue); 
    bst1->addNode(lastNode); 

    // print the values in order 
    bst1->printNodes(bst1->getRoot()); 

    cout << "Searching the binary serach tree for smallest value..." << endl; 

    // search the bst for numbers from 0-100 until it finds one 
    int valueinBST = 0; 
    for (int i = 0; i <= 100; i++) {
        
        if (bst1->search(bst1->getRoot(), i)) {
            valueinBST = i; 
            break; 
        }
    }

    //print out the found value 
    cout << "Found " << valueinBST << " in the BST!" << endl;

    cout << "Removing the last value (leaf) from the BST..." << endl;

    //try to remove the last value we added earlier 
    if (bst1->removeLeafNode(lastValue)) {
        cout << "Removed " << lastValue << "!" << endl; 
    }

    //print the bst again 
    bst1->printNodes(bst1->getRoot()); 

    // garbage collection
    delete bst1; 

    return 0; 
}