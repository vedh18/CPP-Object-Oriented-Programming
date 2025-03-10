#include "book.h"
Book::Book() : borrowedTime(0), reserved(false), reservedTime(0) {}

// Parameterized constructor
Book::Book(string ISBN, string title, string author, string publisher, string year, string status)
    : ISBN(ISBN), title(title), author(author), publisher(publisher), year(year),
      status(status), borrowedTime(0), reserved(false), reservedTime(0) {}

// Getter functions
string Book::getISBN() const { return ISBN; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getPublisher() const { return publisher; }
string Book::getYear() const { return year; }
string Book::getStatus() const { return status; }
string Book::getBorrowerID() const { return borrowerID; }
time_t Book::getBorrowedTime() const { return borrowedTime; }
bool Book::isReserved() const { return reserved; }
time_t Book::getReservedTime() const { return reservedTime; }
string Book::getReserverID() const { return reserverID; }

// Updater (setter) functions
void Book::updateISBN(const string &isbn) { ISBN = isbn; }
void Book::updateTitle(const string &t) { title = t; }
void Book::updateAuthor(const string &a) { author = a; }
void Book::updatePublisher(const string &p) { publisher = p; }
void Book::updateYear(string y) { year = y; }
void Book::updateStatus(const string &s) { status = s; }
void Book::updateBorrowerID(const string &id) { borrowerID = id; }
void Book::updateBorrowedTime(time_t t) { borrowedTime = t; }
void Book::updateReserved(bool r) { reserved = r; }
void Book::updateReservedTime(time_t t) { reservedTime = t; }
void Book::updateReserverID(const string &id) { reserverID = id; }

// Member function implementations

void Book::printBook(){
    cout << left;
    cout << setw(12) << "Title:"     << title     << endl;
    cout << setw(12) << "Author:"    << author    << endl;
    cout << setw(12) << "Publisher:" << publisher << endl;
    cout << setw(12) << "Year:"      << year      << endl;
    cout << setw(12) << "ISBN:"      << ISBN      << endl;
    cout << setw(12) << "Status:"    << status    << endl;
    cout << endl;
}

void Book::borrowBook(){
    if (status == "Reserved"){
        status = "Borrowed";
        reserved = false;
        borrowedTime = std::time(0);
    }
    if (status == "Available"){
        status = "Borrowed";
        borrowedTime = std::time(0);
    }
    else{
        cout << "Book is currently " << status << endl;
    }
}

void Book::returnBook(string userType){
    if (reserved){
        status = "Reserved";
        reservedTime = std::time(0);
        borrowedTime = 0;
    }
    else if (status == "Borrowed"){
        status = "Available";
        borrowedTime = 0;
    }
    if (userType == "Student"){
        time_t currentTime = std::time(0);
        int days = (currentTime - borrowedTime) / timeUnit;
        if (days > 15){
            cout << "You have " << days - 15 << " days overdue for this book." << endl;
        }
    }
    else if (userType == "Faculty"){
        time_t currentTime = std::time(0);
        int days = (currentTime - borrowedTime) / timeUnit;
        if (days > 30){
            cout << "You have " << days - 30 << " days overdue for this book." << endl;
        }
    }
}

void Book::reseverBook(string userID){
    if (status == "Borrowed"){
        reserved = true;
        reserverID = userID;
    }
    else{
        cout << "Book is currently " << status << endl;
    }
}

void Book::unreserveBook(){
    reserved = false;
    reserverID = "";
    if (status == "Reserved"){
        status = "Available";
    }
}
bool operator<(const Book& a, const Book& b) {
    return a.ISBN < b.ISBN;
}
Book::~Book(){}