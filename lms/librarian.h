#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <iostream>
#include <string>
#include <vector>
#include "user.h"      // Base class User declaration
using namespace std;

class Librarian : public User {
    public:
        // Constructors
        Librarian();
        Librarian(string name, string userID);

        // Member functions
        void addBook();
        void addStudent();
        void addFaculty();
        void addLibrarian();

        void removeBook();
        void removeStudent();
        void removeFaculty();
        void removeLibrarian();

        void updateBook();
        void updateStudent();
        void updateFaculty();
        void updateLibrarian();

        friend bool operator<(const Librarian &a, const Librarian &b);
        // Destructor
        ~Librarian();
};
#endif