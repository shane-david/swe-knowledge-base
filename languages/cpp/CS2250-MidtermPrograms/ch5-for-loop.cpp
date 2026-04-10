/*
example program 1/2 for ch 5
this program demonstrates the repition control structure described in ch5
by showing a simple for loop that iterates to a randomly generated number in 
a user defined range and prints out each iteration number
*/

#include <iostream> //preprocessor directive for input and output
#include <ctime>    //preprocessor directive for seeding randomness

using namespace std;

int main() {

    //seed ring
    srand(time(NULL)); 

    //define vars  
    int iterationRNG = 0;
    int userMax = 0;

    //prompt user and get max for rng
    cout << "Please enter an integer representing the maximun number of iterations for the following loop." << endl;
    cin >> userMax;

    //get the random value between 1 and the user max
    iterationRNG = (rand() % (userMax-1)) + 1; 

    //report randomness
    cout << "Looping " << iterationRNG << " times..." << endl; 

    //for loop iterationRNG times printing out each i 
    for (int i = 0; i < iterationRNG; i++) {
        cout << "Iteration " << i+1 << endl; 
    }

    return 0; 
}