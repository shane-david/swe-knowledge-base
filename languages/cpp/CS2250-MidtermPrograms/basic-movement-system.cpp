/*
This program demonstrats a basic movement system for an ASCII game 
it contains a map class that is simply a 2D array representing a 4x4 matrixs
map contains methods for moving player left, right, up, and down that all include 
bounds checking, it prompts the user for movement and clears the console after each input 
and exits if the player types EXIT instead of a movement key 
*/

#include <iostream> //preprocessor directive for i/o
#include <string>   //preprocessor directive for string use 

using namespace std; 

class Map {
private:

    //-------------
    //private data
    //-------------

    bool   _isRunning;  //bool representing whether the game loop should run or not 
    string _userChoice; //string used to take in the user choice within the run method
    char   _map[4][4];  //2D 4x4 array representing the map 
    int    _width  = 4; //width of the map, set to 4 by default 
    int    _height = 4; //height of the map, set to 4 by default 
    char   _emptyChar;  //the character that will fill in all the empty spots in the array 
    char   _playerChar; //the character that will represent where the player is in the array 
    int    _playerX;    //the current x location of the player
    int    _playerY;    //the current y location of the player 

    /*
    public move methods for each horizontal and vertical, the direction in that line it moves is passed in 
    depending on the direction it handles it creates a newLoc variable and adds the passed in direction
    to either the x or y player location variable. It then swaps the current player location 
    with the new one so now the player is in a new spot and the empty char is in the previous spot
    it then sets the playerX and playerY variables to match the player's new spot, these are all private
    because no one should be moving the player except for the Map class itself within the run method 
    */

    void moveHor(int direction) {

        //moving right means playerX should be increased by 1 
        int newLoc = _playerX + direction; 

        //make sure the new loaction is between 0 and width
        if (newLoc >= 0 && newLoc < _width) {

            //swap the current location with the newLoc
            char player = _map[_playerY][_playerX]; 
            _map[_playerY][_playerX] = _map[_playerY][newLoc];
            _map[_playerY][newLoc] = player; 

            //set the players new locatin
            _playerX = newLoc; 

        //if it failed the bounds test, do not do anything but prompt for another move 
        } else {

            cout << "You can not move there, the map is not big enough!" << endl; 
        }
    }

    void moveVer(int direction) {

        //moving right means playerX should be increased by 1 
        int newLoc = _playerY + direction; 

        //make sure the new loaction is between 0 and height
        if (newLoc >= 0 && newLoc < _height) {

            //swap the current location with the newLoc
            char player = _map[_playerY][_playerX]; 
            _map[_playerY][_playerX] = _map[newLoc][_playerX];
            _map[newLoc][_playerX] = player; 

            //set the players new location
            _playerY = newLoc; 

        //if it failed the bounds test, do not do anything but prompt for another move 
        } else {

            cout << "You can not move there, the map is not big enough!" << endl; 
        }
    }


public:

    //default constructor, fills the arrays with the empty char, sets the empty char
    //and player char, puts the player in a starting position, and starts the loop
    //called with Map aMap(char, char); 
    Map(char playerChar, char emptyChar) {
        
        //set passed in values to class data
        _playerChar = playerChar;
        _emptyChar  = emptyChar; 

        //iterate through 2D array and put _emptyChar in every square
        for (int row = 0; row < _height; row++) {
            for (int col = 0; col < _width; col++) {
                _map[row][col] = _emptyChar; 
            }
        }

        //put player char in the first position of the map 
        _map[0][0] = _playerChar; 
        _playerX = 0;
        _playerY = 0; 

        //set _isRunning to true to begin the movement system loop
        _isRunning = true; 
    }

    //public run method, handles prompting the user and exiting the game 
    void run() {
        
        char userChoice; 

        //make the movement system active while isRunning is true 
        while (_isRunning) {

            //prompt the user for movement input and tell them how to exit
            cout << "Please enter a WASD character to move, type EXIT to stop the program." << endl;
            cout << "W = North, A = West, S = South, D = East" << endl; 
            cout << endl; 

            //display the map 
            displayMap(); 

            //collect the input 
            cin >> _userChoice; 

            //call the respective method depending on what the user input
            if (_userChoice == "EXIT") {
                quitGame(); 
            } else if (_userChoice == "W" || _userChoice == "w") {
                moveVer(-1);
            } else if (_userChoice == "A" || _userChoice == "a") {
                moveHor(-1);
            } else if (_userChoice == "S" || _userChoice == "s") {
                moveVer(1);
            } else if (_userChoice == "D" || _userChoice == "d") {
                moveHor(1); 
            } else {
                cout << "Unknown input, please try again..." << endl; 
            }
        }
    }

    //public method to stop the game from running handles setting 
    //the isRunning variable and telling the user what is happening
    //it is public becuase it is possible a user might one to quit the game 
    //outside of the class for different reasons 
    void quitGame() {

        cout << "Stoping the game..." << endl;
        _isRunning = false; 

    }

    void displayMap() {
        
        //cout a barrier for nice dispaly
        cout << "--------Map--------" << endl;

        //iterate through 2D array cout every char 
        for (int row = 0; row < _height; row++) {

            for (int col = 0; col < _width; col++) {
                cout << _map[row][col]; 
            }

            //endl at end of row 
            cout << endl; 
        }
    }

};

int main() {

    //create a map and call the run method to begin logic
    Map aMap('P', '*'); 
    aMap.run(); 

    return 0; 
}