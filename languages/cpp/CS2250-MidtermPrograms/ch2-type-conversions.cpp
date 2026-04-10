/*
Example program 2/2 for ch2
This program models the type casting concepts discussed in chapter 2 by reading in a user int 
and a double then performing operations that result in a decimal value with implicit casting 
then taking in two ints and dividing them to produce a deicmal value with explicit casting 
*/

#include <iostream> //preprocessor directive for input and output 

using namespace std; 

int main() {

    //implicit casting section
    cout << "Demonstrating implicit type casting..." << endl; 

    //define and int and double for arithmetic (initialize to not have garbage values)
    int implicitInt = 0;
    double implicitDouble = 0.0; 

    //output a prompt using cout from iostream
    cout << "Pleaes enter first an integer value, then a space, then a decimal value: "; 

    //take in the two integers from the user using cin from iostream
    cin >> implicitInt >> implicitDouble; 

    //get a result in a double variable so it implicitly promotes implicitInt to a double in order to perform the arithmetic 
    double result = implicitInt * implicitDouble; 

    //output the result 
    cout << implicitInt << " * " << implicitDouble << " = " << result << endl; 

    //explicit casting section 
    cout << "Demonstrating explicit type casting..." << endl; 

    //define two ints for division (initialize to not have garbage values)
    int userInt1 = 0, userInt2 = 0;

    //output a prompt using cout from iostream
    cout << "Pleaes enter two integer values separated by a space: "; 

    //take in the two integers from the user using cin from iostream
    cin >> userInt1 >> userInt2; 

    //divid them to a decimal result with explicit type casting
    double divResult = static_cast<double>(userInt1) / static_cast<double>(userInt2); 

    //output the results 
    cout << userInt1 << " / " << userInt2 << " = " << divResult << endl; 

    return 0; 
}