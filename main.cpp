#include <bits/stdc++.h>
using namespace std;

// Object-Oriented Programming (OOP) in C++
// ----------------------------------------

// Class: A blueprint for objects
// Object: An instance of a class
// Encapsulation: Wrapping data and methods into a single unit

class Teacher {
    // Access Modifiers: public, private, protected
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
        // this pointer is used to point to the current object
        this->name = name;
        (*this).dept = dept;
        subject = subject;
        setSalary(sal);
        this->age = new int;
        *(this->age) = age;
    }

    // Shallow copy constructor
    // Custom copy constructor
    // Teacher(Teacher &t) {
    // }

    // Deep copy
    Teacher(Teacher &t) {
        this->name = t.name;
        this->dept = t.dept;
        this->subject = t.subject;
        this->salary = t.salary;
        this->age = new int;
        *(this->age) = *(t.age);
    }

    // Destructor: Special function called when an object is destroyed
    ~Teacher() {
        delete this->age;
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

class Person{
public:
    string name;
    int age;
    Person(string name, int age) {
        this->name = name;
        this->age = age;
    }

};

// Inheritance: A class can inherit attributes and methods from another class
// First the parent class is called and then the student class is called
class Student: public Person {
public:
    string dept;
    // Calling the parent constructor using the child constructor
    Student(string name, int age, string dept): Person(name, age) {
        this->dept = dept;
    }
};

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

    // Copy constructor is used for creating a new object as a copy of an existing object
    Teacher t3(t2);
    
    // If we had used the normal shallow copy constructor, t2's age also would have changed.
    *(t3.age) = 45;
    cout << *(t2.age) << endl;

    Student s1("Alice", 20, "CSE");
    
    return 0;
}
