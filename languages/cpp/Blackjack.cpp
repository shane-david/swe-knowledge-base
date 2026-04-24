/*
Shane David
4/20/2026
This is a program that builds on all C++ knowledge so far to craft a working blackjack program. 
*/

#include <iostream> // preprocessor directive for i/o 
#include <string>   // preprocessor directive for strings 
#include <cctype>   // preporcessor directive for character funcs
#include <vector>   // preprocessor directive to use vectors as a temp data structure for shuffling
#include <cstdlib>   // preprocessor directive for rng
#include <ctime>    // preprocessor directive for seeding the rng

using namespace std;

// helper function to clear the console for all UI stuff
// it depends on the os of the user 
void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Node class that the Linked list contains instances of, holds T for the data
// and a pointer to the next node, since it is a singly linked list it does not need a previous pointer
template <typename T>
class Node {
public:

    Node* pNext; // next node inthe linked list
    T     data;  // type of the passed in template representing data

    // defaulct constructor
    Node() {
        pNext = nullptr; 
    }

    // paramterized constructor
    Node(T setData) {
        data = setData; 
        pNext = nullptr; 
    }
};

// Linked list class that contains type T to create Nodes of type T 
// This is a standard singly linked list that contains functionality 
// to randomly shuffle all of the nodes in the linked list 
template <typename T>
class LinkedList {
private: 

    //------------
    //private data
    //------------

    Node<T>* _pHead; // pointer to the head (start) of linked list
    int      _size;  // size of the linked list, keep track of this for shuffling later 

public:

    //------------
    //constructors
    //------------

    // default constructor
    LinkedList() {
        _pHead = nullptr;
        _size = 0; 
    }

    //--------------
    //public methods
    //--------------

    // this method creates a node of whatever was passed in an pushes it to the front of the linked list
    void push(T item) {

        // create the node with data set to item 
        Node<T>* toAdd = new Node<T>(item); 

        // if the list is empty just make the node the head 
        if (_pHead == nullptr) {

            _pHead = toAdd; 

        //otherwise link it in properly 
        } else {

            toAdd->pNext = _pHead; 
            _pHead = toAdd; 
        }

        //increment size 
        _size++; 
    }

    // this method adds a node at a passed in loaction to the list 
    // it returns whether the addition was successful or not 
    bool add(T item, int index) {

        // do bounds checking on the index
        if (index < 0) {
            return false; 
        }

        // create the new node 
        Node<T>* toAdd = new Node<T>(item); 

        // if the index is 0 (insert at the front)
        if (index == 0 || _pHead == nullptr) {

            toAdd->pNext = _pHead; 
            _pHead = toAdd; 
            _size++; 
            return true; 

        }

        // traverse to the node just before the trarget index and link it in
        // NOTE: we stop early if we hit the end of the list so  there is no need for size bounds checking
        Node<T>* pCurrent = _pHead; 
        int counter = 0;
        while (pCurrent->pNext != nullptr && counter < index - 1) {
            pCurrent = pCurrent->pNext; 
            counter++; 
        }

        // link the node in 
        toAdd->pNext = pCurrent->pNext; 
        pCurrent->pNext = toAdd; 
        _size++; 
        return true; 
    }

    // this method removes the front element of the list (the head) and returns it 
    // it returns nullprt if the list is empty
    T* pop() {

        if (_pHead == nullptr) {
            return nullptr;
        }

        // get the head in a node so we can delete it 
        Node<T>* toDelete = _pHead;

        // get the data as a pointer so that we can return it 
        T* data = new T(_pHead->data);
        
        // unlink the head
        _pHead = _pHead->pNext; 

        // delete the head and decrease the seid
        delete toDelete; 
        _size--; 

        return data; 
        
    }

    // this method returns a pointer to the data at the front of the list but does not 
    // delete it, it is const so that the data can not be delted outside the list 
    const T* peek() {

        // return null if the listis emtpy
        if (_pHead == nullptr) {
            return nullptr; 
        }

        // otherwhise return the address of the data in the head
        return &_pHead->data; 
    }

    // this method returns a pointer to the data at the given index but does not delete it
    // it returns nullprt if the index is out of bounds, and the pointer is const to the user
    // can not edit the data resulting in unexpected behavior 
    const T* get(int index) {

        // bounds checking
        if (index < 0 || index >= _size) {
            return nullptr; 
        }

        // iterate to the node at the index 
        Node<T>* pCurrent = _pHead; 
        for (int i = 0; i < index; i++) {
            pCurrent = pCurrent->pNext; 
        }

        // return address of the data at the current node
        return &pCurrent->data; 
    }

    // this method removes a node from the linked list at a given index
    // it returns false if the removal was not successful and true otherwise
    bool remove(int index) {

        // bounds checking 
        if (index < 0 || index >= _size) {
            return false; 
        }

        // create an empyt node that represent the one we will delete
        Node<T>* toDelete = nullptr; 

        // if we are removing the head 
        if (index == 0) {

            // set to delete to the head and unlink the head from the list 
            toDelete = _pHead; 
            _pHead = _pHead->pNext; 

        // otherwsie we must traverse to the index 
        } else {

            // travers a current node from the head to one before the node we want to delete
            Node<T>* pCurrent = _pHead; 
            for (int i = 0; i < index - 1; i++) {
                pCurrent = pCurrent->pNext; 
            }

            //set the to delete node and unlike it 
            toDelete = pCurrent->pNext; 
            pCurrent->pNext = toDelete->pNext; 
        }

        // delete the node (garbage colection) and deal with the size
        delete toDelete; 
        _size--;
        return true; 

    }
    
    // the shuffle method shuffles the linked list by rearranging where each node points at
    // this is optimal for memory as we do not have to create any new nodes or data, just change what 
    // each node is pointing at the the order is rearranged 
    void shuffle() {

        // if the size is 1 or empty there is no need to shuffle
        if (_size <= 1) {
            return; 
        }

        // walk through the list and store every node pointer in a vector to prepare to shuffle
        vector<Node<T>*> nodes;
        Node<T>* pCurrent = _pHead; 
        while (pCurrent != nullptr) {

            // store node pointer in the nodes vector
            nodes.push_back(pCurrent);

            // progress to the next node
            pCurrent = pCurrent->pNext; 
        }

        // pick a random node from the vector and make it the new head 
        int randomIndex = rand() % nodes.size(); 
        _pHead = nodes.at(randomIndex); 

        // erase the index we made the head
        nodes.erase(nodes.begin() + randomIndex); 

        // now starting at the new head, iterate setting pNext with a random index until node is empty
        pCurrent = _pHead; 
        while (!nodes.empty()) {

            // get another random index
            randomIndex = rand() % nodes.size(); 

            // link the random node to current
            pCurrent->pNext = nodes.at(randomIndex); 

            // progress pCurrent 
            pCurrent = pCurrent->pNext; 

            // remove the node we just added from the vector
            nodes.erase(nodes.begin() + randomIndex); 
        }

        // now, at the end of the list, make sure it points to nullptr for no circular logic
        pCurrent->pNext = nullptr; 
    }

    //--------
    //getters
    //--------

    // this method retruns the size of the linked list 
    inline int getSize() {return _size;}

    //-----------
    //Destructor
    //-----------

    ~LinkedList() {

        // walk through the list from the head to the end and delete every node
        Node<T>* pCurrent = _pHead; 
        while (pCurrent != nullptr) {

            // save the next node we need so we can access it after deletion 
            Node<T>* pNext = pCurrent->pNext; 

            // delete the node
            delete pCurrent; 

            // progress the node
            pCurrent = pNext; 
        }

        // make sure the head is not pointing to empty memory
        _pHead = nullptr;
        _size = 0; 
    }

}; 

// Card id enum, contains values for all card IDs (types of cards) so there are no weird string errors
enum CardID {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, NONE};

// Card struct, this represents a card, containing variables for the value in blackjack, and its ID
struct Card {

    int value; 
    CardID id; 

    // default constructor (set to default values)
    Card() {
        value = 0; 
        id = NONE; 
    }

    // paramterized constructor (to create a specific card)
    Card(int v, CardID i) {
        value = v;
        id = i; 
    }
};

// Deck class, this represents the deck that the Game class will use for the game
// it contains the cards and the discard pile both as linked lists and contains methods
// for everything that would need to be done to a deck of card in blackjack 
class Deck {
private:

    //-------------
    //private data
    //-------------

    LinkedList<Card> _cards; 
    LinkedList<Card> _discardPile; 

    //---------------
    //private methods
    //---------------
    
    // thid method is only called at the creation of the deck 
    // it fills the deck with 4 cards of each ID (Ace-King)
    void BuildDeck() {

        // card values that parallel the CardID enum order to fill the cards
        int values[] = {11,2,3,4,5,6,7,8,9,10,10,10,10}; 

        // loop for four times for each suit to get proper amount of cards 
        for (int suit = 0; suit < 4; suit++) {

            // loop through the CardId enum for each suit and create the card, adding it to the linked list
            for (int id = ACE; id <= KING; id++) {
                _cards.push(Card(values[id-ACE], static_cast<CardID>(id))); 
            }
        }

    }

public:

    //-------------
    //constructors
    //-------------

    //default constructor create the linked lists
    Deck() {
        BuildDeck(); 
    }

    //--------------
    //public methods
    //--------------

    // method to deal a card (removes it from the deck, whoever called it now owns the card and its memory)
    Card* dealCard() {
        return _cards.pop(); 
    }

    // method that recieves a card back (from the Game) and puts it in the discard pile 
    // it returns whether or not the discard was successful 
    bool discardCard(Card* card) {

        // if they pass a nullptr in return false 
        if (card == nullptr) {
            return false; 
        }

        // add the discarded card to the discard pile
        _discardPile.push(*card); 

        // get rid of the card memory because _discardPile now owns it 
        delete card; 
        return true; 
    }

    // this method resets the deck (moves all cards from discard to card pile)
    // it makes sure that all the cards are in the deck before it does so
    bool reset() {

        // make sure that all 52 cards are either in _cards or _discardPile
        if (_cards.getSize() + _discardPile.getSize() != 52) {
            cerr << "[Deck] ERROR: Cannot reset, deck does not own all cards!" << endl; 
            return false; 
        }

        // if we made it this far we are ready to reset, pop every card off dicard pile
        // and push it back onto the standar card pile 
        while (_discardPile.getSize() > 0) {

            // get the card from the discard pile
            Card* card = _discardPile.pop(); 

            // push it onto the card pile 
            _cards.push(*card); 

            // delete the memory because _cards owns it now 
            delete card; 
        }

        return true; 
    }

    void shuffle() {
        
        // try to reset to do a full shuffle 
        if (reset()) {

            _cards.shuffle();

        }
    }

};

// deciion enum represening the things that  BlackjackEntity can do
enum Decision {HIT, STAND, SPLIT, DOUBLE, BAD };

// BlackjackEntity ABSTRACT class, it defines the base behavior of teh player and dealer
// it is the parent of both of those classes so that polymorphism can be used within the Game Class
// this class and its children will define behavior for how those entities shoold interact with the Game
class BlackjackEntity {
protected:

    //---------------
    //protected data
    //---------------

    LinkedList<Card> _hand; 
    bool             _canPlay;
    int              _pointTotal; 


public:

    //-------------
    //constructors
    //-------------

    //paramterized constructor
    BlackjackEntity() {
        _canPlay = true;
        _pointTotal = 0; 
    }

    //--------------
    //public methods
    //--------------   

    // hit method takes in a Card* and adds it the entities hand then reccalulates the point total 
    void Hit(Card* card) {

        // if it is an ace determine the value 
        if (card->id == ACE) {

            card->value = getAceValue(); 

        } 
        
        // add the cards point total to the entities point total
        _pointTotal += card->value; 

        // add the card to the entities hand 
        _hand.push(*card); 

        // delete the memory because _hand now owns it 
        delete card; 

    }

    // stand method just sets the _canPlay variable to false so that the entity can no longer decide
    void Stand() {
        _canPlay = false; 
    }

    // is bust method determines whether or not the play has busted 
    bool isBust() {
        return _pointTotal > 21; 
    }

    // discard hand method takes a reference to the deck and discards all the cards in the hand
    // it returns whether or not the discard was successful
    bool discardHand(Deck& deck) {

        // iterate through the hand and discard every created card until it is empty
        while (_hand.getSize() > 0) {

            // get the card from the hand
            Card* card = _hand.pop();

            // try to remove it, if at any point the removal fails, exit this method
            if (!deck.discardCard(card)) {
                delete card; 
                return false; 
            } 
        }

        return true; 
    }

    // this method resets the black jack entity so that they can play again after a round 
    void reset() {
        _canPlay = true; 
        _pointTotal = 0; 
    }

    //--------
    //getters
    //--------


    inline bool canPlay() {return _canPlay;}

    //return a reference to the hand so that it can be used in the game
    inline LinkedList<Card>& getHand() {return _hand;}
    inline int getPoints() {return _pointTotal;} 

    //----------------
    //virtual methods
    //----------------

    virtual Decision decide() = 0;
    virtual int getAceValue() = 0; 


};


// the player class is a child of BlakJackEntity, it overrides and defines functionality 
// for decision and getAceValue as well as adding functionality for splitting and doubling
class Player : public BlackjackEntity {
private:

    //-------------
    //private data
    //-------------

    int  _money;
    int  _currentBet;
    bool _hasSplit; 
    LinkedList<Card> _splitHand; 
    int _splitTotal;
    bool _splitTurn; 

public:

    //------------
    //constructors
    //------------

    // default constructor 
    Player() {
        _money = 0;
        _currentBet = 0;
        _hasSplit = false; 
        _splitTotal = 0;
        _splitTurn = false; 
    }

    // paramterized consturctor
    Player(int startMoney) {

        _money = startMoney; 
        _currentBet = 0;
        _hasSplit = false; 
        _splitTotal = 0;
        _splitTurn = false; 
    }

    //--------------
    //public methods
    //--------------

    // the double method doubles the player's current bet 
    // and stands, so they set canPlay to false
    // it returns whether or not they player was able to double 
    bool Double(Card* card) {
        
        // subtract another instance of the bet from the player's hand (if you can)
        if (_money >= _currentBet) {

            _money -= _currentBet; 

        // if this could not happen, the player can not double, return false 
        } else {

            return false; 

        }

        // double the current bet 
        _currentBet *= 2; 

        // give the player their last card
        Hit(card); 

        // stand (they can no longer play) 
        _canPlay = false; 
        return true; 
    }

    // the spllit method moves the second card from _hand into _splitHand
    // it then deducts anotehr bet of value _currentBet from money, returning false if the player can not afford to split  
    // it then sets the split variables accordingly 
    bool Split() {

        // subtract another instance of the bet from the player's hand (if you can)
        if (_money >= _currentBet) {

            _money -= _currentBet; 

        // if this could not happen, the player can not double, return false 
        } else {

            return false; 

        }

        // if we did not return pop the second card from the main hand
        Card* secondCard = _hand.pop();

        //put the second card into the split hand and set the split total
        _splitHand.push(*secondCard); 
        _splitTotal = secondCard->value; 
        _pointTotal -= secondCard->value; 

        //get rid of the second card's memory has the split hand now owns it 
        delete secondCard; 

        // set teh split variales
        _hasSplit = true;
        _splitTurn = false; 
        return true; 
    }

    // this mthod hits to the split card, it emulates the hit method but edits the split hand and total instead
    void hitSplit(Card* card) {
       
        // if it is an ace determine the value 
        if (card->id == ACE) {

            card->value = getAceValue(); 

        } 
        
        // add the cards point total to the entities point total
        _splitTotal += card->value; 

        // add the card to the entities hand 
        _splitHand.push(*card); 

        // delete the memory because _hand now owns it 
        delete card; 

    }

    // this method determinse if the split hand busted or not 
    bool isSplitBust() {
        return _splitTotal > 21; 
    }

    // this method switches the play to the split hand by setting the bools
    void switchToSplit() {
        _splitTurn = true;
        _canPlay = true; // if the player's can play was set to false for their first hand reanble it for the split hand 
    }

    // thid method calls the blackjack entity reset and updates the split state 
    void reset() {
        BlackjackEntity::reset();
        _hasSplit = false;
        _splitTotal = 0;
        _splitTurn = false; 
    }

    // this method is an update to discardHand so that teh split hand is also discarded
    bool discardHand(Deck& deck) {

        //discard main hand
        if (!BlackjackEntity::discardHand(deck)) {
            return false; 
        }

        //discard split hand
        while (_splitHand.getSize() > 0) {
            Card* card = _splitHand.pop(); 
            if (!deck.discardCard(card)) {
                delete card;
                return false; 
            }
        }

        return true; 
    }

    // this override of decide makes the decision based off the player input, 
    // it prompts the player for what they want to do, based off of what they can do
    Decision decide() override {

        //make a string and bools that represnts the options they have 
        string possibleDecisions = "[H] Hit\n[S] Stand\n"; 
        bool canDouble = false;
        bool canSplit = false; 

        //make an array that contains the valid characters 

        //if they can double add double
        if (!_splitTurn && _money >= _currentBet) {
            possibleDecisions += "[D] Double\n"; 
            canDouble = true; 
        }

        //if they can split add split (MAKE SURE THEY HAVE ENOUGH CARDS TO AVOID SEGMENTATION FAULTS)
        if (!_splitTurn && _hand.getSize() >= 2 && _hand.peek()->id == _hand.get(1)->id && _money >= _currentBet) {
            possibleDecisions += "[P] Split\n"; 
            canSplit = true; 
        }

        //prompt the user 
        cout << "It is your turn! Please enter a single character representing what you want to do:" << endl;
        cout << possibleDecisions << endl; 

        //get the user input 
        char userInput = ' '; 
        cin >> userInput; 

        //normalize input 
        userInput = toupper(userInput); 

        //keep trying to get user input until a valid one exists 
        while (userInput != 'S' && userInput != 'H' && !(userInput == 'D' && canDouble) && !(userInput == 'P' && canSplit)) {

            //tell them to try again 
            cout << "Invalid Input! Please try again:" << endl ;
            cout << possibleDecisions << endl; 

            //get another character and normalize it 
            cin >> userInput; 
            userInput = toupper(userInput); 
        }

        //now switch their input to return what needs to be returned
        switch (userInput) {
        case 'S':
            return STAND; 
        case 'H':
            return HIT;
        case 'D':
            return DOUBLE;
        case 'P':
            return SPLIT; 
        default:
            return BAD; 
        }   
    }

    // the get ace value method determines the value of the ace based off of the user choice 
    int getAceValue() override {

        // prompt the user for what they want the value to be 
        cout << "You have drawn an ACE, would you like it to be a 1 or an 11?" << endl; 
        cout << "Your current point total is: " << (_splitTurn ? _splitTotal : _pointTotal) << endl;; 
        int aceValue; 
        cin >> aceValue; 

        // make sure they entered a valid ace value 
        while (aceValue != 1 && aceValue != 11) {

            cout << "That is not a valid ACE value, please enter a single integer (1 or 11): ";
            cin >> aceValue; 
        }

        // set the ace value 
        return aceValue; 
    }

    // method to set the player bet, it returns false if the player tries to bet more than they have
    bool bet(int amount) {

        // make sure they can bet that 
        if (amount > _money) {
            return false; 
        }

        // set the current bet 
        _currentBet = amount; 

        // subtract it from their money
        _money -= _currentBet; 

        return true; 
    }

    // method for when the player wins the bet
    void win() {
        cout << "You win $" << _currentBet << endl; 
        _money += _currentBet * 2;
    }

    // method for when the player ites
    void tie() {
        cout << "Tie, you get your money back" << endl; 
        _money += _currentBet;
    }

    // method for if the player lost
    void resetBet() {
        _currentBet = 0; 
    }

    //--------
    //getters
    //--------

    inline bool hasSplit()                  {return _hasSplit;}
    inline bool isSplitTurn()               {return _splitTurn;}
    inline int getSplitTotal()              {return _splitTotal;}
    inline LinkedList<Card>& getSplitHand() {return _splitHand;}
    inline int getMoney()                   {return _money;}      
    inline int getBet()                     {return _currentBet;} 

};

// the dealer class represent the dealer black jack entity, instead of prompting logic for things
// like decision and get ace value it just has logic that depends on the state of its hand 
class Dealer : public BlackjackEntity {
public:

    //-----------------
    //overriden methods
    //-----------------

    // decision, the dealer hits on 16 or less and stands on 17 or more
    Decision decide() override {

        // if the dealer's total is 16 or less they must hit 
        if (_pointTotal <= 16) {

            return HIT; 

        // otherwise they must stand
        } else {

            return STAND;

        }
    }

    // get ace value, the dealer just selects 11 unless it will bring them over 21, then they select 1 
    int getAceValue() override {

        if (_pointTotal + 11 > 21) {
            return 1; 
        } else {
            return 11;  
        }
    }

};

// the game class handles the entire flow and logic of the game 
// it handles getting the player started with money, starting a round with 2 cards for the dealer and player
// drawing the board with ascii art, taking the player and dealer's turn and dealing with the results 
// and starting/ending the round and the game 
class Game {
private:

    //-------------
    //private data
    //-------------

    Deck _deck;
    Dealer _dealer;
    Player _player; 
    Decision _prevDecision = BAD; 

    //---------------
    //HELPER METHODS
    //---------------

    // this method is private because it is only used by draw board 
    // it takes in the card that the board wants to draw and produces
    // a readable string that can be drawn with ascii art
    string cardToString(const Card* card) {

        // create an array of the strings I want to be displayed so they can be indexed by the enum 
        string cardNames[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"}; 

        // if the passed in card does not have an ID log an error
        if (card->id == NONE) {
            cerr << "[GAME] trying to draw an invalid card!" << endl;
            return "ERROR"; 
        }

        // return the string that will represent the card 
        return "[" + cardNames[card->id] + "]"; 
    }

    // this method is private because it is only used within the games run method to display the board
    // it starts by clearing the board then drawin the dealers hand, then drawing the player's hand with a ui at the bottom for points, moeny, ect
    // it takes in a bool representing if the dealer card is hidden or not 
    void drawBoard(bool cardIsHidden = true) {

        // clear the console 
        clearConsole(); 

        //draw the dealer heading 
        cout << "--------------------" << endl;
        cout << "       DEALER       " << endl; 
        cout << "--------------------" << endl;

        //iterate through the dealer's hand 
        for (int i = 0; i < _dealer.getHand().getSize(); i++) {

            // get the next card in the dealer's hand
            const Card* card = _dealer.getHand().get(i); 

            // hide the second card if it is meant to be hidden
            if (i == 1 && cardIsHidden) {

                cout << "[?] "; 

            // otherwise display the card's character
            } else {

                cout << cardToString(card) << " "; 
            }
        }
        cout << endl << endl; 

        //draw the player heading
        cout << "--------------------" << endl;
        cout << "       PLAYER       " << endl; 
        cout << "--------------------" << endl;

        //iterate through the player's hand
        for (int i = 0; i < _player.getHand().getSize(); i++) {

            // get the next card in the player's hand
            const Card* card = _player.getHand().get(i); 

            // display the card's character
            cout << cardToString(card) << " ";
        }
        cout << endl << endl; 

        //if the player has split, draw the split hand
        if (_player.hasSplit()) {

            //draw the split hand heading
            cout << "--------------------" << endl;
            cout << "    SPLIT HAND      " << endl; 
            cout << "--------------------" << endl;

            //iterate through teh split hand
            for (int i = 0; i < _player.getSplitHand().getSize(); i++) {

                // get the next card in the split hand
                const Card* card = _player.getSplitHand().get(i);

                // display the card's character
                cout << cardToString(card) << " ";
            }
            cout << endl << endl; 
            cout << "Split Points: " << _player.getSplitTotal() << endl; 
        }

        //draw a simple UI for the player's points, money, and bet  
        cout << "Points:  " << _player.getPoints() << endl;
        cout << "Money:  $" << _player.getMoney() << endl;  
        cout << "Bet:    $" << _player.getBet() << endl; 
        cout << "--------------------" << endl << endl; 

        //output the result of the last decision if there was one 
        if (_prevDecision == HIT) {
            cout << "HIT!" << endl; 
        } else if (_prevDecision == STAND) {
            cout << "STAND" << endl;
        } else if (_prevDecision == DOUBLE) {
            cout << "DOUBLE" << endl; 
        } else if (_prevDecision == SPLIT) {
            cout << "SPLIT"; 
        }
        cout << endl << endl; 

    }

    // this method promts the player for a bet and tries to bet it until they enter a proper amount
    void playerBet() {

        // prompt the player for a bet
        cout << "You have $" << _player.getMoney() << ". How much would you like to bet? Please enter an integer number." << endl;
        
        // get the user's bet
        int playerBet = 0;
        cin >> playerBet; 

        // try to bet that amount until the player has entered a proper bet
        while (!_player.bet(playerBet)) {

            cout << "Invalid Bet! You only have $" << _player.getMoney() << ". Please enter a value less than or equal to your money." << endl;
            cin >> playerBet; 
        }
    }

    //-----------------
    //GAMEFLOW METHODS
    //-----------------

    // the run method deals with the logic of when the deal takes their turn
    // when the player takes theirs, and when to end the round, it is called by startRound
    void run() {

        // first the player takes their turn
        takeTurn(_player); 

        // draw the board after the player's turn
        drawBoard(); 

        // get bust variabls depending on split or not 
        bool mainBust = _player.isBust(); 
        bool splitBust = _player.isSplitBust(); 

        // get a variale that is for all bust, if the player has not split it only cares about mainBust but if they have it cares about both
        bool allBust = _player.hasSplit() ? (mainBust && splitBust) : mainBust; 

        // if the player busted skip the dealer's turn and just end the roung
        if (allBust) {

            endRound(); 

        // otherwise doe the dealer's turn
        } else {

            takeTurn(_dealer, true);
            
            // draw the board with the dealer's card unhidden
            drawBoard(false); 

            // end the round
            endRound(); 
        }
    }

    // the take turn method handles the player or dealer's turn 
    // it takes a reference to a BlackJackEntity (either the player or dealer)
    // calls their decision method and then deals with whatver decision is returned
    void takeTurn(BlackjackEntity& entity, bool isDealersTurn = false) {

        // do the turn while the entity can play (until they stand or bust)
        while (entity.canPlay()) {

            // get the entitie's decisoin
            Decision decision = entity.decide(); 
            _prevDecision = decision; 

            // deal with the logic based off of the decision

            // if the entity hit 
            if (decision == HIT) {

                // if the player is palying their split hand, hit that instead
                if (!isDealersTurn && _player.hasSplit() && _player.isSplitTurn()) {
                    _player.hitSplit(_deck.dealCard()); 
                } else {
                    // hit from the top card of the deck
                    entity.Hit(_deck.dealCard()); 
                } 

            // if the entity stood
            } else if (decision == STAND) {

                // if the player has a split hand and hasn't played it yet, switch to it 
                if (!isDealersTurn && _player.hasSplit() && !_player.isSplitTurn()) {
                    _player.switchToSplit(); 
                } else {
                    entity.Stand(); 
                }

            // if the entity doubled
            } else if (decision == DOUBLE) {

                // we can assume that this entity is the player because only the player could return this value from the enum
                _player.Double(_deck.dealCard()); 

            } else if (decision == SPLIT) {

                //make the player split and deal them one card to each ahnd
                _player.Split(); 
                _player.Hit(_deck.dealCard());
                _player.hitSplit(_deck.dealCard()); 
            }

            // draw the board after each instance of the turn
            drawBoard(!isDealersTurn);

            // if the player is playing the split hand check for split bust
            if (!isDealersTurn && _player.hasSplit() && _player.isSplitTurn()) {
                if (_player.isSplitBust()) {
                    cout << "BUST on split hand" << endl;
                    entity.Stand(); 
                }

            // otherwise just check for a normal bust 
            } else if (entity.isBust()) {

                cout << "BUST!" << endl; 
                entity.Stand(); 

                // if the player busted and can switch to a split, switch to it 
                if (_player.hasSplit() && !_player.isSplitTurn()) {
                    _player.switchToSplit(); 
                }
            }
 

            // let the player step through (MOSTLY FOR DEBUG)
            cout << endl;
            cout << "-----------------------------" << endl;
            cout << "TYPE C THEN ENTER TO CONTINUE" << endl;
            cout << "-----------------------------" << endl;
            char garbageInput = ' ';
            cin >> garbageInput; 
        }

        // set the previous deciosn back to bad
        _prevDecision = BAD; 
    }

    //----------------------
    //STARTER/ENDER METHODS
    //----------------------

    // this method takes care of everything necessary to start a round of black jack, it assumes that the round 
    // has been cleaned up and ended properly by endRoun 
    void startRound() {

        // clear the console 
        clearConsole(); 

        // shuffle the deck (should be reset from endRound)
        _deck.shuffle(); 

        // get the player's bet 
        playerBet(); 

        // deal two cards to the player
        _player.Hit(_deck.dealCard()); 
        _player.Hit(_deck.dealCard()); 

        // deal two cards to the dealer
        _dealer.Hit(_deck.dealCard());
        _dealer.Hit(_deck.dealCard());

        // draw the board 
        drawBoard(); 

        // run the round
        run(); 
    }

    void endRound() {

        // draw the board with the dealer's hand unhidden to show it off
        drawBoard(false); 

        // tel; the player their point total and the dealer's point total
        cout << "--------------------" << endl;
        cout << "      SUMMARY       " << endl;
        cout << "--------------------" << endl;
        cout << "Player Points: " << _player.getPoints() << endl;
        cout << "Dealer Points: " << _dealer.getPoints() << endl; 
        cout << endl << endl; 

        // determine the result of the summary
        if (!_player.isBust()) {

            // if the daler busted or the player has more points the player won
            if (_dealer.isBust() || _player.getPoints() > _dealer.getPoints()) {

                _player.win();

            // if the dealer and player have same points the player ties
            } else if (_dealer.getPoints() == _player.getPoints()) {

                _player.tie(); 

            // otherwise the dealer won 
            } else {
                cout << "Dealer wins, you lose your bet!" << endl; 
            }

        // if the player did bust the dealer wins 
        } else {
            cout << "Dealer wins, you lose your bet!" << endl; 
        }

        // if there is a split hand, do the same logic on that hand
        if (_player.hasSplit()) {
            
            // tell the player this is a split summary
            cout << "--------------------" << endl;
            cout << "   SPLIT SUMMARY    " << endl;
            cout << "--------------------" << endl;
            cout << "Split Points: " << _player.getSplitTotal() << endl;

            // determine the result of the split summary
            if (!_player.isSplitBust()) {

                // if the daler busted or the player has more points the player won
                if (_dealer.isBust() || _player.getSplitTotal() > _dealer.getPoints()) {

                    cout << "From split hand: "; 
                    _player.win();

                // if the dealer and player have same points the player ties
                } else if (_dealer.getPoints() == _player.getSplitTotal()) {

                    _player.tie(); 

                // otherwise the dealer won 
                } else {
                    cout << "Dealer wins, split hand loses!" << endl; 
                }

            // if the player did bust the dealer wins 
            } else {
                cout << "Split hand busted!" << endl; 
            }
        }

        //reset the player's bet
        _player.resetBet(); 

        //discard the players and dealers hands
        _player.discardHand(_deck);
        _dealer.discardHand(_deck); 

        //reset the player and dealer's point totals
        _player.reset();
        _dealer.reset(); 

        // let the player continue when they are ready 
        cout << endl;
        cout << "-----------------------------" << endl;
        cout << "TYPE C THEN ENTER TO CONTINUE" << endl;
        cout << "-----------------------------" << endl;
        char garbageInput = ' ';
        cin >> garbageInput; 

    }

    void endGame() {

        cout << "--------------------" << endl;
        cout << "     GAME OVER      " << endl;
        cout << "--------------------" << endl;
    
    }


public:

    //-------------
    //constructors
    //-------------

    // get starting money and set the player's starting money
    Game(int startingMoney)
        : _player(startingMoney) { }

    //---------------
    //public methods
    //---------------

    // the startgame method takes care of the intro and starts the round
    // this is the only public method because it is the only one called by main
    // then the rest of the logic is handled within the class
    void startGame() {

        cout << "--------------------" << endl;
        cout << "WELCOME TO BLACKJACK" << endl;
        cout << "--------------------" << endl;
        cout << "You are starting with $" << _player.getMoney() << "." << endl;
        cout << "Follow the prompts along the way. Good luck!" << endl << endl; 

        // let the player continue when they are ready 
        cout << endl;
        cout << "-----------------------------" << endl;
        cout << "TYPE C THEN ENTER TO CONTINUE" << endl;
        cout << "-----------------------------" << endl;
        char garbageInput = ' ';
        cin >> garbageInput; 

        // start the first round
        while (_player.getMoney() > 0) {
            startRound(); 
        }

        //once the money is 0 or less ned the game
        endGame(); 

    }

};

int main() {

    // seed rng
    srand(time(nullptr));

    Game blackJack(1000); 

    blackJack.startGame(); 


    return 0; 
}