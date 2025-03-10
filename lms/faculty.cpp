#include "faculty.h"
#include "global.h"   // For access to the global Library object

Faculty::Faculty() {}

// Parameterized constructor
Faculty::Faculty(string name, string userID) : User(name, userID, "Faculty") {}

// Borrow a book
void Faculty::borrowBook() {
    this->account.calcFine();
    if (this->account.borrowedBooks.size() >= 5) {
        cout << "Cannot borrow more than 5 books" << endl;
        return;
    }
    if (this->account.overdueBooks > 0) {
        cout << "You have " << this->account.overdueBooks << " books overrdue, please return them first." << endl;
        return;
    }

    cout << "Here are the available books: " << endl;
    library.viewAvailableBooks();
    this->account.checkReservedBooks();
    cout << "Enter the ISBN of the book you want to borrow or enter 0 if you wanna go back: ";
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
}
bool operator<(const Faculty &a, const Faculty &b) {
    return a.userID < b.userID;
}
Faculty::~Faculty() {
    // No dynamic resources to free.
}