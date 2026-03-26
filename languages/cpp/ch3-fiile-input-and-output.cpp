/*
example program 2/2 for ch 3
this program demonstrates file input and output by opening the file 
ch3-test-file for reading and outputing each string to the console on its own line
*/

#include <iostream> //preprocessor directive for ouptuting file string
#include <fstream>  //preprocessory directive for reading test file 
#include <string>   //to store the strings from the file in a variable 

using namespace std; 

int main() {

    //open the test file for reading
    ifstream fin;
    fin.open("ch3-test-file.txt"); 

    //define word variable representing the next word in the file 
    string word; 

    //while you can still get another string from the file, output it 
    while (fin >> word) {
        cout << word << endl; 
    }

    //close the file 
    fin.close(); 

    return 0; 
}