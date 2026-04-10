/*
example program 2/2 for ch 4
this program demonstrates the control structures described in ch4 of the book
by showing a simple switch case structure in c++ by modeling a simple menu 
with basic calculator functionality 
*/

#include <iostream> //preprocessor directive for input and output
#include <cassert>  //preprocessor directive for assert function 

using namespace std;

int main() {

    //define vars
    char operationChar = ' '; 
    int userInt1 = 0, userInt2 = 0, result = 0; 

    //prompt and get the operation char from the user 
    cout << "Please enter a single character representing what operatoin you want to perform (+,-,*,/)" << endl; 
    cin >> operationChar; 

    //prompt and get 2 ints to perform operation on 
    cout << "Please enter two integers separated by a space to perform the operation on." << endl;
    cin >> userInt1 >> userInt2; 

    //switch the operation char and perform the respective operation
    //NOTE: division uses assert to prevent dividing by 0 
    switch (operationChar) {
    case '+':
        result = userInt1 + userInt2;
        break;
    case '-':
        result = userInt1 - userInt2;
        break;
    case '*':
        result = userInt1 * userInt2;
        break; 
    case '/':
        assert(userInt2 != 0); 
        result = userInt1 / userInt2;
        break;
    default:
        cout << "Invalid character, terminating program" << endl; 
        assert(false);
    }

    //output the result 
    cout << userInt1 << " " << operationChar << " " << userInt2 << " = " << result; 

    return 0; 
}