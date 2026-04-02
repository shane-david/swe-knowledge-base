/*
example program 1/2 for ch 6
this program demonstrates value returning functions described in ch 6
by creating several functions for basic arithmetic and then performing those operations 
on user defined values
*/

#include <iostream> //preprocessor directive for input and output

using namespace std;

//function prototypes
int add(int, int);
int sub(int, int);
int mul(int, int);
int divide(int, int); 


int main() {

    //define vars
    int userInt1 = 0, userInt2 = 0; 

    //prompt user and get ints
    cout << "Please enter 2 integers" << endl;
    cin >> userInt1 >> userInt2; 

    //perform operations and output 
    cout << userInt1 << " + " << userInt2 << " = " << add(userInt1, userInt2) << endl; 
    cout << userInt1 << " - " << userInt2 << " = " << sub(userInt1, userInt2) << endl; 
    cout << userInt1 << " * " << userInt2 << " = " << mul(userInt1, userInt2) << endl; 
    cout << userInt1 << " / " << userInt2 << " = " << divide(userInt1, userInt2) << endl; 

    return 0;
}

//function definitons 
int add(int n, int m) {
    return n+m;
}

int sub(int n, int m) {
    return n-m;
}

int mul(int n, int m) {
    return n*m; 
}

int divide(int n, int m) {

    if (m == 0) {
        return -1; 
    }

    return n/m; 
}