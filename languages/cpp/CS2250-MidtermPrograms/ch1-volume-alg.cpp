/*
Example program 1/2 for ch. 1
Calculates the volume of a sphere 
Excercies 17 from end of chapter 1 in book 
*/

#include <iostream> //preprocessor directive for i/o
#include <cmath>    //preprocessor directive for math functions

using namespace std; 

int main() {

    //define vars

    const double PI = 3.14159265; //const double to represent pi 
    double radius = 3.0;          //hardcode radius to be 3 for testing purposes
    double volume = 0.0;          //declare volume var


    //calculate

    //volume of a sphere is (4.0/3.0)*pi*r^3
    volume = (3.0/4.0) * PI * pow(radius, 3); 

    //output 

    cout << "The volume is: " << volume << endl; 

    return 0; 
}