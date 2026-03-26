/*
Example program 2/2 for ch. 1
Finds the real roots of a quadratic using the quadratic equation 
Excercies 21 from ch. 1 in the book 
*/

#include <iostream> //preprocessor directive for i/o
#include <cmath>    //preprocessor directive for math functions

using namespace std; 

int main() {

    //define vars

    int a = 1, b = 5, c = 6;         //the a, b, c from the quadratic equation 
    double root1 = 0.0, root2 = 0.0; //inital definitions for the two roots 

    //calculate - quadratic formula is (-b +/- sqrt(b^2 - 4ac)) / 2a

    double discriminant = sqrt(pow(b,2) - (4*a*c)); //first get the discriminat 
    root1 = (-b + discriminant) / (2*a);      //root 1 is +
    root2 = (-b - discriminant) / (2*a);      //root 2 is -

    //output 

    cout << "The roots of: " << a << "x^2 + " << b << "x + " << c << " are: " << root1 << " and " << root2; 

    return 0; 
}