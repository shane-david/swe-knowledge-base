/*
example program 2/2 for ch 9
this program demonstrates the structs explained in chapter 9 at a more advanced level 
by creating a struct of Playing Cards and having an array of these cards representing the hand
*/

#include <iostream>  //preprocessor directive for input and output 
#include <cstdlib>   //preprocessor directive for rand() function
#include <ctime>     //preprocessor directive for seeding the rng
#include <string>    //preprocessor directive for strings

using namespace std; 

//enums representing the suit and name of the card
enum Suit { CLUBS, HEARTS, SPADES, DIAMONDS }; 
enum Name { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING }; 

//struct representing the card
struct PlayingCard {
    Suit suit;
    Name name; 
}; 

//function prototypes
PlayingCard getCard(); 

int main() {

    //seed rng
    srand(time(NULL)); 

    //create arrays of strings for suit and name so that we do not have to use switches to print 
    string suits[] = {"Clubs", "Hearts", "Spades", "Diamonds"};
    string names[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"}; 

    //create an array of 5 playing cards
    PlayingCard hand[5]; 

    //iterate through the array and fill it with random cards
    for (int i = 0; i < 5; i++) {
        hand[i] = getCard(); 
    }

    //print out cards 
    for (int i = 0; i < 5; i++) {
        cout << names[hand[i].name] << " of " << suits[hand[i].suit] << endl; 
    }

    return 0; 
}

//function definitions

//randomly generate a playing card 
PlayingCard getCard() {

    //get a random suit (between 0 and 3)
    Suit randomSuit = static_cast<Suit>(rand() % 4); 

    //get a random name (between 0 and 12)
    Name randomName = static_cast<Name>(rand() % 4); 

    //create the struct to return and fill its values
    PlayingCard randomCard;
    randomCard.suit = randomSuit;
    randomCard.name = randomName; 

    return randomCard; 
}