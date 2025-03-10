#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <iostream>
#include <string>
#include <vector>
#include "user.h"      // Base class User declaration
#include "book.h"      // For Book class used in member functions
#include "history.h"   // For History records in account
#include "global.h"    // For access to the global Library object
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