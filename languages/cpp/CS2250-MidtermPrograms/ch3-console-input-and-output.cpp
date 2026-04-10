/*
Example program 1/2 for ch3
This program models the input and output concepts discussed in chapter 3 by prompting for numbers and performing basic arithmetic
it also uses iomanip to set the precision of the results and user entered numbers 
*/

#include <iostream> //preprocessor directive for input and output 
#include <iomanip>  //preprocessor directive to set precision of doubles in output

using namespace std; 

int main() {

    //define vars (initialize to not have garbage values)
    double userNum1 = 0.0, userNum2 = 0.0;

    //output a prompt using cout from iostream
    cout << "Pleaes enter two decimal values separated by a space: "; 

    //take in the two integers from the user using cin from iostream
    cin >> userNum1 >> userNum2; 

    //perform some basic calculations 
    double addResult = userNum1 + userNum2; 
    double mulResult = userNum1 * userNum2; 

    //output the results using cout from iostream
    cout << setprecision(3) << userNum1 << " + " << setprecision(3) << userNum2 << " = " << setprecision(3) << addResult << endl; 
    cout << setprecision(3) << userNum1 << " * " << setprecision(3) << userNum2 << " = " << setprecision(3) << mulResult << endl; 
    

    return 0; 
}