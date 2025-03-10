#include "user.h"
#include "global.h"

User::User() {}

// Parameterized constructor
User::User(string name, string userID, string userType) {
    this->name = name;
    this->userID = userID;
    this->account.updateUserID(userID);
    this->account.userType = userType;
}

string User::getUserID() {
    return this->userID;
}

void User::updateUserID(string newUserID) {
    this->userID = newUserID;
    this->account.updateUserID(newUserID);
}

string User::getName() {
    return this->name;
}

void User::updateName(string newName) {
    this->name = newName;
}

void User::printUser() {
    cout << left;
    cout << setw(12) << "Name: " << name << endl;
    cout << setw(12) << "ID: " << userID << endl;
    cout << endl;
}

void User::returnBook() {
    if (this->account.borrowedBooks.size() == 0) {
        cout << "No books to return" << endl;
        return;
    }
    cout << "Here are the books you have borrowed: " << endl;
    for (auto book : this->account.borrowedBooks) {
        book.printBook();
    }
    cout << "Enter the ISBN of the book you want to return or enter 0 to go back: ";
    cin.ignore();
    string ISBN;
    getline(cin, ISBN);

    if (ISBN == "0"){
        return;
    }

    if (library.bookMap.find(ISBN) == library.bookMap.end()) {
        cout << "Invalid ISBN, Please try again" << endl;
        returnBook();
        return;
    }

    if (this->account.borrowedBooks.find(library.bookMap[ISBN]) == this->account.borrowedBooks.end()) {
        cout << "You did not borrow this book, Please try again" << endl;
    }
    Book book = library.bookMap[ISBN];
    this->account.borrowedBooks.erase(book);
    library.books.erase(book);

    book.returnBook(this->account.userType);

    library.bookMap[ISBN] = book;
    library.books.insert(book);

    History history("Returned Book", book.getTitle(), book.getISBN());
    this->account.history.push_back(history);

    cout << "Book returned successfully" << endl;
}

void User::reserveBook() {
    if (this->account.reservedBooks.size() >= 3) {
        cout << "Cannot reserve more than 3 books, Please unreserve and come back!" << endl;
        return;
    }
    cout << "Here are the books which are not available currently and can be reserved: " << endl;
    library.viewReservableBooks();
    cout << "Enter the ISBN of the book you want to reserve or enter 0 to go back: ";
    cin.ignore();
    string ISBN;
    getline(cin, ISBN);
    if (ISBN == "0") {
        return;
    }
    if (library.bookMap.find(ISBN) == library.bookMap.end()) {
        cout << "Invalid ISBN, Please try again" << endl;
        reserveBook();
        return;
    }
    // check if the status of the book is borrowed and not reserved
    if (!(library.bookMap[ISBN].getStatus() == "Borrowed" && !library.bookMap[ISBN].isReserved())) {
        cout << "This book is not available for reservation, Please put one of the books in the list above" << endl;
        reserveBook();
        return;
    }
    Book book = library.bookMap[ISBN];
    library.books.erase(book);

    book.reseverBook(this->userID);

    library.bookMap[ISBN] = book;
    library.books.insert(book);

    this->account.reservedBooks.insert(book);
    cout << "Book reserved successfully, you will be notified when it becomes available." << endl;
    History history("Reserved Book", book.getTitle(), book.getISBN());
    this->account.history.push_back(history);

    cout << "Book reserved successfully" << endl;
}

void User::unreserveBook() {
    cout << "Here are the books you have reserved: " << endl;
    for (auto book : this->account.reservedBooks) {
        book.printBook();
    }
    cout << "Enter the ISBN of the book you want to unreserve or enter 0 to go back: ";
    cin.ignore();
    string ISBN;
    getline(cin, ISBN);
    if (ISBN == "0") {
        return;
    }
    if (library.bookMap.find(ISBN) == library.bookMap.end()) {
        cout << "Invalid ISBN, Please try again" << endl;
        reserveBook();
        return;
    }
    if (this->account.reservedBooks.find(library.bookMap[ISBN]) == this->account.reservedBooks.end()) {
        cout << "You have not reserved this book, Please enter one of the books from the list above." << endl;
        reserveBook();
        return;
    }
    Book book = library.bookMap[ISBN];
    library.books.erase(book);
    this->account.reservedBooks.erase(book);

    book.unreserveBook();

    library.bookMap[ISBN] = book;
    library.books.insert(book);

    cout << "Book unreserved successfully" << endl;
}

User::~User() {
    // Destructor: no dynamic memory to free here.
}