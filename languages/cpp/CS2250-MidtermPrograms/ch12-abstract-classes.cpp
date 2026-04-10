/*
example program 2/2 for ch 12
this program demonstrates the abstract classes described in ch 12
by creating 3 simple classes. A Sahpe abstract base class, Circle and Square classes inherit from
this abstract class, main then showcases the advantages of this through polymorphism 
*/

#include <iostream>  //preprocessor directive for input and output 
#include <string>    //preprocessor directive for strings

using namespace std;

//ABSTRACT
class Shape {
protected:

    //private data
    string _color; 

public:

    //default constructo
    Shape() = default;

    //paramterized constructor
    Shape(string color)
        :_color(color) { }

    //pur virtual method to calculate area 
    virtual double area() = 0; 

    //virtual destructor so that memory is dellocated properly for the polymorhpism in main
    virtual ~Shape() {
        cout << "Destructing shape..." << endl; 
    }
}; 

class Circle : public Shape {
private:

    //private data
    double _radius; 

public:

    //default construcot
    Circle() = default;

    //paramterized constructor
    Circle(string color, double radius)
        :Shape(color), _radius(radius) { }

    //ovverride virtual area method and define functionaility for circles
    double area() override {
        return 3.14 * _radius * _radius; 
    }

    //destructor for circle
    ~Circle() {
        cout << "Destructing circle..." << endl; 
    }
};

class Square : public Shape {
private:

    //private data
    double _sideLength;

public:

    //default constructor
    Square() = default;

    //paramterized constructor
    Square(string color, int sideLength) 
        :Shape(color), _sideLength(sideLength) { }

    //override virtual area method to define functionality for squares
    double area() override {
        return _sideLength * _sideLength; 
    }

    //destructor for square
    ~Square() {
        cout << "Destructing square..." << endl; 
    }
}; 

int main() {

    //create two Shapes, a circle and a square, demonstrating polymorphism
    Shape* s1 = new Circle("white", 3.4); 
    Shape* s2 = new Square("red", 4.0); 

    //print out areas of shapes
    cout << "Area of shape 1 is: " << s1->area() << endl;
    cout << "Area of shape 2 is: " << s2->area() << endl; 

    //delete shapes, should call destrutors here 
    delete s1;
    delete s2; 

    return 0; 
}