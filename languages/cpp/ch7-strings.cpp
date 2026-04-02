/*
example program 2/2 for ch 7
this program demonstrates the string data type discussed in ch7
and several string functions editing this string and outputting their edited version 
*/

#include <iostream> //preprocessor directive for input and output
#include <string>   //preprocessor directive for strings

using namespace std;

int main() {

    //define vars
    string userString = ""; 
    int helloPos = 0; 

    //prompt user and get a string that hopefully has "Hello" in it 
    cout << "Please enter a sentence that contains \"Hello\"" << endl; 
    cin >> userString; 
    
    //get the position of hello if there is one 
    helloPos = userString.find("Hello"); 

    //if .find did not fine hello it will return string::npos
    if (helloPos == string::npos) {

        cout << "String does not contain \"Hello\"" << endl << "Appending it now..." << endl; 
        userString += " Hello"; 
        cout << "New string is " << userString << endl; 

    } else {

        cout << "\"Hello\" found at index: " << helloPos << endl;

    }

    return 0; 
}