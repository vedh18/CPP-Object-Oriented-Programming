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

    // Constructor: Special function called when an object is created
    // Non-parameterized constructor
    Teacher() {
        cout << "Object created" << endl;
    }
    
    // Parameterized constructor
    Teacher(string n, string d, string s, double sal) {
        name = n;
        dept = d;
        subject = s;
        setSalary(sal);
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

int main() {
    // Creating objects
    Teacher t1;
    t1.name = "John Doe";
    t1.dept = "CSE";
    t1.subject = "Computer Networks";
    t1.setSalary(50000);

    cout << "Salary: " << t1.getSalary() << endl;
    cout << "Name: " << t1.name << endl;

    Teacher t2("Jane Doe", "ECE", "Digital Signal Processing", 60000);
    t2.getInfo();

    return 0;
}
