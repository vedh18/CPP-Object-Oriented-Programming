#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include "user.h"      // Base class declaration


using namespace std;

class Student : public User {
    public:
        // Constructors
        Student();
        Student(string name, string userID);

        // Member functions
        void borrowBook();
        friend bool operator<(const Student &a, const Student &b);
        // Destructor
        ~Student();
};

#endif