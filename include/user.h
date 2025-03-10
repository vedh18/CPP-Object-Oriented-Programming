#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "account.h"

using namespace std;

class User {
    protected:
        string name;
        string userID;
    public:
        Account account; // Account class to handle user activity
    
        // Constructors
        User();
        User(string name, string userID, string userType);
    
        // Member functions
        string getUserID();
        void updateUserID(string newUserID);
        string getName();
        void updateName(string newName);
        void printUser();
        void returnBook();
        void reserveBook();
        void unreserveBook();
    
        // Virtual destructor
        virtual ~User();
};
#endif