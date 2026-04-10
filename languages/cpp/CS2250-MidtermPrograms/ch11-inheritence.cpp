/*
example program 1/2 for ch 11
this program demonstrates inheritence discussed in ch 11 by creating 3 simple classes
an animal base class, and a dog, cat, and bird classes that inherit from animal 
main then creates an instance of each of these classes and showcases their same and overriden behavior
*/

#include <iostream>  //preprocessor directive for input and output 
#include <string>    //preprocessor directive for strings


using namespace std; 

class Animal {
protected:

    //private data
    string _name; 
    int    _weight;

public:

    //default constructor
    Animal() = default;

    //paramterized constructor
    Animal(string name, int weight)
        :_name(name), _weight(weight) { }

    //method for animal to make noise
    virtual void speak() {
        cout << "Animal Sounds" << endl; 
    }
};

class Dog : public Animal {
public:

    //costructor
    Dog(string name, int weight)
        :Animal(name, weight) {}

    //override speak method
    void speak() override {
        cout << "Bark! -" << _name << endl; 
    }
};

class Cat : public Animal {
public:

    //constructor
    Cat(string name, int weight)
        :Animal(name, weight) { }

    //override speak method
    void speak() override {
        cout << "Meow! -" << _name << endl; 
    }
};

class Bird : public Animal {
public:

    //constructor
    Bird(string name, int weight)
        :Animal(name, weight) { }

    //override speak method
    void speak() override {
        cout << "Chirp! -" << _name << endl; 
    }
};

int main() {

    //create each animal 
    Animal aAnimal("NPC", 100);
    Dog aDog("Spot", 20);
    Cat aCat("Peaches", 15);
    Bird aBird("Parrot", 5); 

    //have them all speak
    aAnimal.speak();
    aDog.speak();
    aCat.speak();
    aBird.speak(); 
}
