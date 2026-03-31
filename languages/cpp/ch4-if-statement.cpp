/*
example program 1/2 for ch 4
this program demonstrates the control structures described in ch4 of the book
by showing a simple if-else and nested if statment structure, it also uses the 
assert function described at the end of the chapter to show this off 
*/

#include <iostream> //preprocessor directive for input and output
#include <cassert>  //preprocessor directive for assert function 
#include <string>   //preprocessory directive to use strings

using namespace std; 

int main() {

    //define vars
    char userChar = ' '; // to be input by the user 

    //prompt the user for and get a character to be used in the selection
    cout << "Please enter a single letter (lower or uppercase)" << endl;
    cin >> userChar; 

    //ASCII 65-90 = A-Z caps 
    if (userChar >= 65 && userChar <= 90) {

        cout << "You entered an uppercase letter" << endl; 

        //nested if check if it is an A and output result based with ternary operator
        string letterResult = ""; 
        (userChar == 65) ? letterResult = "The letter is an A" : letterResult = "The letter is not an A"; 
        cout << letterResult << endl; 


    //ASCII 97-122 = a - z lowercase
    } else if (userChar >= 97 && userChar <= 122) {

        cout << "You entered a lowercase letter" << endl; 

    //otherwise terminate the program
    } else {

        cout << "Not a letter, terminating program..." << endl; 
        assert(false); 
    }


    return 0; 
}