/*
example program 1/2 for ch 7
this program demonstrates the user defined simple data types discussed in ch 7
by defining and utilizing an enum to have the user select a level and then demonstrating 
their int values by using a switch to output the level 
*/

#include <iostream> //preprocessor directive for input and output

using namespace std;

//define enum 
enum Level { EASY, HARD, EXTREME }; 

int main() {

    //define vars
    Level userLevel;
    int userLevelInt = -1; 

    //have the user enter a level they want 
    cout << "Enter and integer for your desired level: " << endl << "1 = EASY" << endl << "2 = HARD" << endl << "3 = EXTREME" << endl;
    cin >> userLevelInt; 

    //decrement to make same as 0 starting point of ennums
    userLevelInt--; 

    //switch to tell user thier value 
    switch (userLevelInt) {
    case EASY:
        cout << "You are on easy mode!" << endl;
        userLevel = EASY;
        break;
    case HARD:
        cout << "You are on hard mode!" << endl;
        userLevel = HARD;
        break;
    case EXTREME:
        cout << "You are on extreme mode!" << endl;
        userLevel = EXTREME; 
        break;
    default:
        cout << "Invalid level..." << endl; 
    }

    return 0; 
}