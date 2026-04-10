/*
Example program 1/2 for ch 2
This program uses the string data type discussed in chapter two to simply prompt the user for their name and greet them 
*/

#include <iostream> //preprocessor directive for prompting and getting input 
#include <string>   //preprocessory directive to actually use the string type 

using namespace std; 

int main() {

    //define vars
    string userName = ""; 

    //prompt the user 
    cout << "Please enter your name: "; 

    //get the name from the console input 
    cin >> userName; 

    //output again to greet the user 
    cout << "Hello " << userName << "!" << endl; 

    return 0; 
}