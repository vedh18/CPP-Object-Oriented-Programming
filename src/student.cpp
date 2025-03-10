#include "student.h"
#include "global.h"    // To access the global Library object
/*---------------------- Student Class Implementation ----------------------*/

// Default constructor
Student::Student() {}

// Parameterized constructor
Student::Student(string name, string userID) : User(name, userID, "Student") {}

// Borrow a book
void Student::borrowBook() {
    if (this->account.borrowedBooks.size() >= 3) {
        cout << "Cannot borrow more than 3 books" << endl;
        return;
    }
    if (this->account.fine > 0) {
        cout << "You have a fine of " << this->account.fine << " rupees, please pay the fine first." << endl;
        return;
    }
    cout << "Here are the available books: " << endl;
    library.viewAvailableBooks();
    // Display the books which were reserved by the user and are now available.
    this->account.checkReservedBooks();
    cout << "Enter the ISBN of the book you want to borrow or enter 0 to go back: ";
    cin.ignore();
    string ISBN;
    getline(cin, ISBN);
    if (ISBN == "0") {
        return;
    }
    if (library.bookMap.find(ISBN) == library.bookMap.end()) {
        cout << "Book not found" << endl;
        borrowBook();
        return;
    }
    if (!(library.bookMap[ISBN].getStatus() == "Available" || (library.bookMap[ISBN].getStatus() == "Reserved" && library.bookMap[ISBN].getReserverID() == this->getUserID()))) { 
        cout << "Book is already borrowed or reserved, Please enter one of the books from the list above" << endl;
        borrowBook();
        return;
    }
    Book book = library.bookMap[ISBN];
    library.books.erase(book);
    
    book.borrowBook();

    this->account.borrowedBooks.insert(book);
    library.bookMap[ISBN] = book;
    library.books.insert(book);

    History history("Borrowed Book", book.getTitle(), book.getISBN());
    this->account.history.push_back(history);
    cout << "Successfully borrowed the book " << book.getTitle() << endl;
}
bool operator<(const Student &a, const Student &b) {
    return a.userID < b.userID;
}
Student::~Student() {
    // No dynamic resources to free.
}