#ifndef BOOK_H
#define BOOK_H

#include <iostream>    // For cout, endl
#include <iomanip>     // For setw
#include <string>      // For string
#include <ctime>       // For time_t
using namespace std;

// Lets say we have a unit of time in terms of seconds.
// 1 day = 86400 seconds
// 1 minute = 60 seconds

// int timeUnit = 86400; // 1 day
class Book {
    private:
        // Generic details
        string ISBN;
        string title;
        string author;
        string publisher;
        string year;
    
        // Book status details
        // "Available", "Borrowed", "Reserved"
        string status;
        string borrowerID;
        time_t borrowedTime;
        bool reserved;
        time_t reservedTime;
        string reserverID;
    public:
        // Constructors
        Book();
        Book(string ISBN, string title, string author, string publisher, string year, string status);
    
        // Getter functions
        string getISBN() const;
        string getTitle() const;
        string getAuthor() const;
        string getPublisher() const;
        string getYear() const;
        string getStatus() const;
        string getBorrowerID() const;
        time_t getBorrowedTime() const;
        bool isReserved() const;
        time_t getReservedTime() const;
        string getReserverID() const;
    
        // Updater (setter) functions
        void updateISBN(const string &isbn);
        void updateTitle(const string &t);
        void updateAuthor(const string &a);
        void updatePublisher(const string &p);
        void updateYear(string y);
        void updateStatus(const string &s);
        void updateBorrowerID(const string &id);
        void updateBorrowedTime(time_t t);
        void updateReserved(bool r);
        void updateReservedTime(time_t t);
        void updateReserverID(const string &id);
    
        // Other member functions
        void printBook();
        void borrowBook();
        void returnBook(string userType);
        void reseverBook(string userID);
        void unreserveBook();
    
        friend bool operator<(const Book& a, const Book& b); // Overloaded < operator for sorting
        // Destructor
        ~Book();
};
#endif