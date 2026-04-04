/*
example program 1/2 for ch 10
this program demonstrates the classes explained in chapter 10 by creating a simple 
class, insantiating it, and using its methods in main 
*/

#include <iostream>  //preprocessor directive for input and output 

using namespace std; 

class Clock {
private:

    //private data 
    int _hour;
    int _minute;
    int _second; 

public:

    //default constructor
    Clock() = default;

    //paramterized constructor
    Clock(int hour, int minute, int second)
        :_hour(hour), _minute(minute), _second(second) {}

    //tick method that goes up a second
    void tick() {
        _second++; 
        update(); 
    }

    //update method that makes sure the time is organized correctly
    void update() {

        //go to next minut at 60 s
        if (_second = 60) {
            _minute++;
            _second = 0; 
        }

        //go to next hour at 60 mins
        if (_minute = 60) {
            _hour++;
            _minute = 0; 
        }

        //rest to 1 at 12 hrs
        if (_hour = 13) {
            _hour = 1; 
        }

    }
    //method that prints out the time
    void checkTime() {

        //if the minutes is a single digit at a 0 in front 
        if (_minute < 10) {
            cout << _hour << ":0" << _minute << endl; 
        } else {
            cout << _hour << ":" << _minute << endl; 
        }
    }

};

int main() {


    //create a clock at 12:59
    Clock aClock(12, 59, 0); 

    //show time
    aClock.checkTime(); 

    //tick 60 seconds
    for (int i = 0; i < 60; i++) {
        aClock.tick(); 
    }

    //show time
    aClock.checkTime(); 
}