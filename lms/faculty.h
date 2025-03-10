#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <string>
#include "user.h"     // Base class User declaration

class Faculty : public User {
    public:
        // Constructors
        Faculty();
        Faculty(string name, string userID);

        // Member functions
        void borrowBook();

        friend bool operator<(const Faculty &a, const Faculty &b);
        // Destructor
        ~Faculty();
};

#endif