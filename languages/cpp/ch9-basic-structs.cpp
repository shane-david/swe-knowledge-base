/*
example program 1/2 for ch 9
this program demonstrates the structs explained in chapter 9 at a basic level
by creating a struct and then filling and using its members within main 
*/

#include <iostream> //preprocessor directive for input and output 
#include <string>   //preprocessor directive to use strings

using namespace std;

//struct representing a playing card, contains suit and name as strings
struct PlayingCard {
    string name;
    string suit; 
};

int main() {

    //create the struct 
    PlayingCard userCard; 

    //prompt the user for name and suit 
    cout << "Please enter your playing card in the following format: CardName Suit" << endl;
    cin >> userCard.name;
    cin >> userCard.suit; 

    //tell the user what their card is 
    cout << "Your card is the " << userCard.name << " of " << userCard.suit << endl; 

    return 0; 
}