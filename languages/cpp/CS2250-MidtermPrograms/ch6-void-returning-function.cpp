/*
example program 2/2 for ch 6
this program demonstrates void returning functions described in ch 6
by creating void functions that acoomplish single argument arithmetic 
and use references to directly modify values 
*/

#include <iostream> //preprocessor directive for input and output
#include <cmath>    //preprocessor directive for arithmetic

using namespace std;

//function prototypes
void square(int&);
void power10(int&); 

int main() {

    //define vars
    int userInt = 0; 

    //prompt user and get ints
    cout << "Please enter an integer" << endl;
    cin >> userInt;

    //perform operations and output
    cout << "Before squaring: " << userInt << endl; 
    square(userInt);  
    cout << "After squaring: " << userInt << endl; 

    cout << "Before raising to to the power of 10: " << userInt << endl;
    power10(userInt);
    cout << "After raising to the power of 10: " << userInt << endl; 
    return 0;

}

//function definitions 
void square(int& n) {
    n = pow(n, 2); 
}

void power10(int& n) {
    n = pow(n,10); 
}