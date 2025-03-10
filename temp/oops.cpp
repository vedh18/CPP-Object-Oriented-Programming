#include <bits/stdc++.h>
using namespace std;

// Object-Oriented Programming (OOP) in C++
// ----------------------------------------

// Class: A blueprint for objects
// Object: An instance of a class
// Encapsulation: Wrapping data and methods into a single unit

class Teacher {
    // Access Modifiers: public, private, protected --> are used for Abstraction.
    // Data hiding: Private access modifier restricts direct access
private:
    double salary;

public:
    string name;
    string dept;
    string subject;
    int* age;

    // Constructor: Special function called when an object is created
    // Non-parameterized constructor
    Teacher() {
        cout << "Object created" << endl;
    }
    
    // Parameterized constructor
    Teacher(string name, string dept, string subject, double sal, int age) {
        // 'this' pointer is used to refer to the current object
        this->name = name;
        this->dept = dept;
        this->subject = subject;
        setSalary(sal);
        this->age = new int(age);
    }

    // Deep copy constructor (to handle dynamic memory)
    Teacher(Teacher &t) {
        this->name = t.name;
        this->dept = t.dept;
        this->subject = t.subject;
        this->salary = t.salary;
        this->age = new int(*(t.age));
    }

    // Destructor: Special function called when an object is destroyed
    ~Teacher() {
        delete age;
        cout << "Object destroyed" << endl;
    }
    
    // Method to change department
    void changeDept(string newDept) {
        dept = newDept;
    }

    // Setter function for salary
    void setSalary(double newSalary) {
        salary = newSalary;
    }

    // Getter function for salary
    double getSalary() {
        return salary;
    }

    // Method to display teacher information
    void getInfo() {
        cout << "Name: " << name << endl;
        cout << "Department: " << dept << endl;
        cout << "Subject: " << subject << endl;
        cout << "Salary: " << getSalary() << endl;
    }
};

class Person {
public:
    string name;
    int age;
    
    // Constructor
    Person(string name, int age) {
        this->name = name;
        this->age = age;
    }
};

// Inheritance: A class can inherit attributes and methods from another class
// Private members are not inherited, protected members can be inherited as private or protected,
// and public members can be inherited as public, protected, or private.

// Single Inheritance
class Student : public Person {
public:
    string dept;
    
    // Calling the parent constructor using the child constructor
    Student(string name, int age, string dept) : Person(name, age) {
        this->dept = dept;
    }
};

// Multi-level Inheritance
class gradStudent : public Student {
public:
    string researchArea;
    
    gradStudent(string name, int age, string dept, string researchArea) : Student(name, age, dept) {
        this->researchArea = researchArea;
    }
};

// Multiple Inheritance
class TA : public Teacher, public Student {
public:
    string subjectTaught;
    
    TA(string name, int age, string dept, string subject, double sal, string subjectTaught)
        : Teacher(name, dept, subject, sal, age), Student(name, age, dept) {
        this->subjectTaught = subjectTaught;
    }
};

// Polymorphism: Ability to take multiple forms
// Compile-time/Static polymorphism: Function/Constructor overloading (Same name, different parameters)
// Run-time/Dynamic polymorphism: Function overriding (Same name, same parameters, different implementations in base and derived classes)
// Another example is a virtual function which is defined in the base class and overridden in the derived class.


// Abstraction: Hiding the implementation details and showing only the functionality
// Another way of implementing abstraction is using abstract classes.
// Abstract class is a class that acts as a blueprint for other classes, and cannot be instantiated on its own.
// It contains atleast one virtual function.

class Shape {
public:
    virtual void area() = 0;  // Pure virtual function
};

class Circle : public Shape {
public:
    double radius;

    Circle(double radius) {
        this->radius = radius;
    }

    void area() {
        cout << "Area of circle: " << 3.14 * radius * radius << endl;
    }

};

// Static Keyword
void fun() {
    static int x = 0;  // Intializes only once
    x++;               // Retains the value between function calls
    cout << x << endl;
}

// Static variables in OOPs are created only once and shared among all the objects of the class.
// Static objects are created only once and persist throughout the program.

int main() {
    // Creating objects
    Teacher t1;
    t1.name = "John Doe";
    t1.dept = "CSE";
    t1.subject = "Computer Networks";
    t1.setSalary(50000);

    cout << "Salary: " << t1.getSalary() << endl;
    cout << "Name: " << t1.name << endl;

    Teacher t2("Jane Doe", "ECE", "Digital Signal Processing", 60000, 35);
    t2.getInfo();

    // Using copy constructor
    Teacher t3(t2);
    *(t3.age) = 45;  // Changing t3's age should not affect t2
    cout << *(t2.age) << endl;

    Student s1("Alice", 20, "CSE");
    gradStudent gs1("Bob", 25, "ECE", "Signal Processing");
    TA("Uday", 30, t1.dept, t1.subject, t1.getSalary(), "Computer Networks");

    Circle c1(5);
    c1.area();

    fun();
    fun();
    fun();

    if (true){
        Student s2(s1);
        // The destructor of s2 will be called when it is going to exit the if scope
        static Student s3(s2);
        // The destructor of s3 will not be called now and only at the end of the program.
    }
    return 0;
}