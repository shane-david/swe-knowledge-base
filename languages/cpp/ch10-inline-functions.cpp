/*
example program 2/2 for ch 10
this program demonstrates the inline functions demonstrated in ch 10
and the mutator vs accessor class methods demonstrated in ch 10
by creating a simple class with getters and setters as inline functions
*/

#include <iostream>  //preprocessor directive for input and output 
#include <string>    //preprocessor directive for strings

using namespace std; 

class Person {
private:

    //private data
    string _name;
    int _age; 

public:

    //default constructor
    Person() = default;

    //paramterized constructor
    Person(string name, int age)
        :_name(name), _age(age) {}

    //getters

    inline const string& getName()   const {return _name;}

    inline int           getAge()    const {return _age;}

    //setters
    inline void setName(const string& name) {_name = name;}
    inline void setAge(int age)       {_age = age;}
};

int main() {

    //create a person 
    Person me("Shane", 20); 

    //print out 
    cout << "The programmer's name is " << me.getName() << ". He is " << me.getAge() << " years old." << endl; 

    //create a new person with default constructor 
    Person you; 

    //prompt user to set name and height
    string name;
    cout << "What is your name?" << endl;
    cin >> name;
    you.setName(name); 

    int age;
    cout << "How old are you?" << endl;
    cin >> age;
    you.setAge(age);

    //print out new person
    cout << "You are " << you.getName() << ". You are " << you.getAge() << " years old." << endl; 

    return 0; 
}