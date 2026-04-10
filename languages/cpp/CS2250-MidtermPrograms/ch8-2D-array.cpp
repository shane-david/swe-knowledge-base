/*
example program 2/2 for ch 8
this program demonstrates 2D arrays demonstrated in ch 8
by initializing a 2D array and printint it out as a matrix 
*/

#include <iostream> //preprocessor directive for input and output

using namespace std;

int main() {

    //create and initialize the 2D array 
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    //print the array 
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            cout << matrix[row][col] << " "; 
        }
        cout << endl; 
    }
    return 0; 
}