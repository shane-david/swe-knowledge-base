/*
example program 1/2 for ch 8
this program demonstrates arrays and array processing demonstrated in ch 8 
by implementing a bubble sort algorithm for an array 
*/

#include <iostream> //preprocessor directive for input and output

using namespace std;

//function prototypes
void printArr(int arr[], int size);
void bubbleSort(int arr[], int size); 

int main() {

    //create an unsorted array 
    int array[10] = {4, 46, 7, 0, 30, 888, 7, 99, 10, 9}; 

    //print original array 
    cout << "Array before bubble sort: " << endl;
    printArr(array, 10);

    //sort array
    bubbleSort(array, 10); 

    //print sorted array
    cout << "Array after bubble sort: " << endl;
    printArr(array, 10); 

    return 0; 
}

//function definitions
void printArr(int arr[], int size) {

    //iterate through array
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl; 

}

void bubbleSort(int arr[], int size) {

    //swapped bool to end early if possible 
    bool swapped;

    //amount of times to pass through array 
    for (int i = 0; i < size - 1; i++) {

        //set swapped to false before starting swaps
        swapped = false;

        //go through array to do swaps if necessary
        for (int j = 0; j < size - i - 1; j++) {

            //if a swap is needed sawp
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }

        //break out if there were no swaps on that pass 
        if (!swapped) break;
    }
}