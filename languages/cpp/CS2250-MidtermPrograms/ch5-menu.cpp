/*
example program 2/2 for ch 5
this program demonstrates the repition control structure described in ch5
by using a do...while loop to create a simple menu that continues to prompt the user
until they enter a valid option
*/

#include <iostream> //preprocessor directive for input and output
#include <string>   //to use strings

using namespace std; 

int main() {

    //define vars
    int userInput = 0; 
    string menuPrompt = "Please, select an option from the menu\n1: Option 1\n2: Option 2\n3: Option 3 "; 

    //do while loop prompting the user until a valid input is selected, must iterate at least once 
    do {
        cout << menuPrompt << endl; 
        cin >> userInput; 
    } while (userInput <= 0 || userInput > 3); 

    //output results
    switch (userInput) {
    case 1:
        cout << "Option 1 selected" << endl;
        break; 
    case 2:
        cout << "Option 2 selected" << endl;
        break; 
    case 3:
        cout << "Option 3 selected" << endl;
        break; 
    }

    return 0; 
}