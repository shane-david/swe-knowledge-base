/*
example program 1/2 for ch 12
this program demonstrates the pointer type explained in ch12
by creating several pointers, stack and free store and showcasing their behavior 
it also has functions that receive and return pointers and garbage collection at the ned
*/

#include <iostream>  //preprocessor directive for input and output 

using namespace std;

//function prototypes
int* add(int* a, int* b); 

int main() {
    
    //create two ints
    int x = 10, y = 20; 

    //create 2 stack pointers, set 2 to ints above
    int* pX = &x;
    int* pY = &y;

    //create a heap pointer set to the sum of the 2 above ints
    int* pSum = add(pX, pY); 

    //output addresses and values 
    cout << "Value of pX (address of x): " << pX << ". Value of x: " << *pX << endl; 
    cout << "Value of pY (address of y): " << pY << ". Value of y: " << *pY << endl;
    cout << "Value of pSum: " << pSum << ". Value pSum points to: " << *pSum << endl; 
    cout << endl; 

    //create a shallow copy of above heap pointer
    int* shallowCopy = pSum;

    //create deep copy of above heap pointer
    int* deepCopy = new int(*pSum); 

    //output address and value to display difference 
    cout << "Address of original: " << pSum << " Value of original: " << *pSum << endl; 
    cout << "Address of shallow copy: " << shallowCopy << " Value of shallow copy: " << *shallowCopy << endl;
    cout << "Address of deep copy: " << deepCopy << " Value of ddep copy: " << *deepCopy << endl; 

    //free up memory
    delete pSum;
    delete deepCopy;
    pSum = nullptr;
    deepCopy = nullptr;

    return 0; 
}

int* add(int* a, int* b) {
    int* result = new int(*a + *b);
    return result; 
}