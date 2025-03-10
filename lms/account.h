#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>   // For cout, cin
#include <string>     // For string
#include <set>        // For set (reservedBooks, borrowedBooks)
#include <vector>     // For vector (history)
#include <ctime>      // For time_t

#include "book.h"     // Include Book class
#include "history.h"  // Include History class

using namespace std;

class Account {
    private:
        string userID;
    public:
        string userType; // Student/Faculty/Librarian
    
        set<Book> reservedBooks;
        set<Book> borrowedBooks;
        vector<History> history;
    
        int fine;
        int overdueBooks;
    
        // Constructors
        Account();
        Account(string userID);
    
        // Member functions
        string getUserID();
        void updateUserID(string newUserID);
        void checkReservedBooks();
        void calcFine();
        void payFine();
        void viewHistory();
    
        // Destructor
        ~Account();
    };

#endif // ACCOUNT_H