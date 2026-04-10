/*
example program 2/2 for ch 11
this program demonstrates the composition concepts discussed in ch 11
by a piece and a board class, the board class contains the piece
*/

#include <iostream>  //preprocessor directive for input and output 
#include <string>    //preprocessor directive for strings

using namespace std; 

class Piece {
private:

    string _color; 
    int    _location; 

public:

    //default constructor
    Piece() = default; 

    //paramterized constructor
    Piece(string color, int location)  
        :_color(color), _location(location) { }

    //getter and setter for location 
    inline int getLocation() const {return _location;}

    inline void move(int delta) {_location += delta;}

    //getter for colo
    inline const string& getColor() {return _color;}
}; 

class Board {
private:

    Piece player1Piece;
    Piece player2Piece; 

public:

    //default constructor that sets the pieces to inital values
    Board()
        :player1Piece("White", 0), player2Piece("Black", 1) { }

    //display the pieces
    void displayBoard() {
        cout << player1Piece.getColor() << " is at location " << player1Piece.getLocation() << endl;
        cout << player2Piece.getColor() << " is at location " << player2Piece.getLocation() << endl; 
    }

    //do a turn 
    void doTurn(int player1Move, int player2Move) {

        player1Piece.move(player1Move); 
        player2Piece.move(player2Move); 

    }
};

int main() {

    //create board
    Board aBoard; 

    //display baord
    aBoard.displayBoard(); 

    //move the pieces 
    aBoard.doTurn(4, 1);

    //display the baord again
    aBoard.displayBoard(); 
    
    return 0; 
}