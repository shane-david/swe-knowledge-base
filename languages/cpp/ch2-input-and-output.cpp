/*
Example program 1/2 for ch2
This program models the input and output concepts discussed in chapter 2 by prompting for numbers and performing basic arithmetic
*/

#include <iostream> //preprocessor directive for input and output 

using namespace std; 

int main() {

    //define vars (initialize to not have garbage values)
    int userInt1 = 0, userInt2 = 0;

    //output a prompt using cout from iostream
    cout << "Pleaes enter two integer values separated by a space: "; 

    //take in the two integers from the user using cin from iostream
    cin >> userInt1 >> userInt2; 

    //perform some basic calculations 
    int addResult = userInt1 + userInt2; 
    int mulResult = userInt1 * userInt2; 

    //output the results using cout from iostream
    cout << userInt1 << " + " << userInt2 << " = " << addResult << endl; 
    cout << userInt1 << " * " << userInt2 << " = " << mulResult << endl; 

    return 0; 
}