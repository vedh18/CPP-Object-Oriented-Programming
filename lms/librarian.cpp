#include "librarian.h"
#include "book.h"      // For Book class used in member functions
#include "history.h"   // For History records in account
#include "global.h"    // For access to the global Library object
#include "misc_functions.h" // For printMenu function
/*---------------------- Librarian Class Implementation ----------------------*/

// Default constructor
Librarian::Librarian() {}

// Parameterized constructor
Librarian::Librarian(string name, string userID) : User(name, userID, "Librarian") {}

// Add a new book (status set to Available by default)
void Librarian::addBook() {
    cout << "Creating a new Book" << endl;
    string ISBN, title, author, publisher, status;
    string year;
    cout << "Enter Book ISBN or enter 0 to go back: ";
    cin >> ISBN;
    if (ISBN == "0") {
        return;
    }
    if (library.bookMap.find(ISBN) != library.bookMap.end()) {
        cout << "Book with this ISBN already exists, Please try again." << endl;
        addBook();
        return;
    }
    cin.ignore(); 
    cout << "Enter Book Title: ";
    getline(cin, title); 
    cout << "Enter Book Author: ";
    getline(cin, author);  
    cout << "Enter Book Publisher: ";
    getline(cin, publisher);  
    
    cout << "Enter Book Year: ";
    cin >> year;
    
    cin.ignore();
    Book book(ISBN, title, author, publisher, year, "Available");

    library.books.insert(book);
    library.bookMap[ISBN] = book;

    History history("Created Book", book.getTitle(), book.getISBN());
    this->account.history.push_back(history);
}

void Librarian::addStudent() {
    cout << "Creating a new Student" << endl;
    string name, userID;
    cin.ignore();
    cout << "Enter Student ID or enter 0 to go back: " << endl;
    cin >> userID;
    if (userID == "0") {
        return;
    }
    if (library.studentMap.find(userID) != library.studentMap.end()) {
        cout << "Student with this ID already exists, Please try again." << endl;
        addStudent();
        return;
    }
    cout << "Enter Student Name: " << endl;
    getline(cin, name);
    Student student(name, userID);
    library.students.insert(student);
    library.studentMap[userID] = student;
    History history("Created Student", student.getName(), student.getUserID());
    this->account.history.push_back(history);
}

void Librarian::addFaculty() {
    string name, userID;
    cin.ignore();
    cout << "Enter Faculty ID or enter 0 to go back: " << endl;
    cin >> userID;
    if (userID == "0") {
        return;
    }
    if (library.facultyMap.find(userID) != library.facultyMap.end()) {
        cout << "Faculty with this ID already exists, Please try again." << endl;
        addFaculty();
        return;
    }
    cout << "Enter Faculty Name: " << endl;
    getline(cin, name);
    Faculty faculty(name, userID);
    library.faculties.insert(faculty);
    library.facultyMap[userID] = faculty;
    History history("Created Faculty", faculty.getName(), faculty.getUserID());
    this->account.history.push_back(history);
}

void Librarian::addLibrarian() {
    string name, userID;
    cin.ignore();
    cout << "Enter Librarian ID: " << endl;
    cin >> userID;
    if (userID == "0") {
        return;
    }
    if (library.librarianMap.find(userID) != library.librarianMap.end()) {
        cout << "Librarian with this ID already exists, Please try again." << endl;
        addLibrarian();
        return;
    }
    cout << "Enter Librarian Name: " << endl;
    getline(cin, name);
    Librarian librarian(name, userID);
    library.librarians.insert(librarian);
    library.librarianMap[userID] = librarian;
    History history("Created Librarian", librarian.getName(), librarian.getUserID());
    this->account.history.push_back(history);
}

void Librarian::removeBook() {
    string ISBN;
    cout << "Enter Book ISBN or enter 0 to go back: ";
    cin >> ISBN;
    if (ISBN == "0") {
        return;
    }
    if (library.bookMap.find(ISBN) == library.bookMap.end()) {
        cout << "Book with this ISBN does not exist, Please try again." << endl;
        removeBook();
        return;
    }
    // Erase the book from the library collections.
    library.books.erase(library.bookMap[ISBN]);
    library.bookMap.erase(ISBN);
    History history("Deleted Book", library.bookMap[ISBN].getTitle(), ISBN);
    this->account.history.push_back(history);
}

void Librarian::removeStudent() {
    string userID;
    cout << "Enter Student ID or enter 0 to go back: ";
    cin >> userID;
    if (userID == "0") {
        return;
    }
    if (library.studentMap.find(userID) == library.studentMap.end()) {
        cout << "Student with this ID does not exist, Please try again." << endl;
        removeStudent();
        return;
    }
    library.students.erase(library.studentMap[userID]);
    library.studentMap.erase(userID);
    History history("Deleted Student", library.studentMap[userID].getName(), userID);
    this->account.history.push_back(history);
}

void Librarian::removeFaculty() {
    string userID;
    cout << "Enter Faculty ID or enter 0 to go back: ";
    cin >> userID;
    if (userID == "0") {
        return;
    }
    if (library.facultyMap.find(userID) == library.facultyMap.end()) {
        cout << "Faculty with this ID does not exist, Please try again." << endl;
        removeFaculty();
        return;
    }
    library.faculties.erase(library.facultyMap[userID]);
    library.facultyMap.erase(userID);
    History history("Deleted Faculty", library.facultyMap[userID].getName(), userID);
    this->account.history.push_back(history);
}

void Librarian::removeLibrarian() {
    string userID;
    cout << "Enter Librarian ID or enter 0 to go back: ";
    cin >> userID;
    if (userID == "0") {
        return;
    }
    if (library.librarianMap.find(userID) == library.librarianMap.end()) {
        cout << "Librarian with this ID does not exist, Please try again." << endl;
        removeLibrarian();
        return;
    }
    if (userID == "L0001") {
        cout << "Cannot delete root librarian" << endl;
        return;
    }
    if (userID == this->getUserID()) {
        cout << "Cannot delete self" << endl;
        return;
    }
    library.librarians.erase(library.librarianMap[userID]);
    library.librarianMap.erase(userID);
    History history("Deleted Librarian", library.librarianMap[userID].getName(), userID);
    this->account.history.push_back(history);
}

void Librarian::updateBook() {
    string ISBN;
    cout << "Enter Book ISBN or enter 0 to go back: ";
    cin >> ISBN;
    if (ISBN == "0") {
        return;
    }
    if (library.bookMap.find(ISBN) == library.bookMap.end()) {
        cout << "Book with this ISBN does not exist, Please try again." << endl;
        updateBook();
        return;
    }
    Book book = library.bookMap[ISBN];
    library.books.erase(book);
    cout << "Enter the field you want to update: " << endl;
    vector<string> menu = {"Title", "Author", "Publisher", "Year"};
    int choice = printMenu(menu);
    cout << "PS: You cannot change ISBN number of the book, for that please delete the existing book and add a new one." << endl;
    switch(choice) {
        case 1: {
            cout << "Enter new title: ";
            cin.ignore();
            string newTitle;
            getline(cin, newTitle);
            book.updateTitle(newTitle);
            break;
        }
        case 2: {
            cout << "Enter new author: ";
            cin.ignore();
            string newAuthor;
            getline(cin, newAuthor);
            book.updateAuthor(newAuthor);
            break;
        }
        case 3: {
            cout << "Enter new publisher: ";
            cin.ignore();
            string newPublisher;
            getline(cin, newPublisher);
            book.updatePublisher(newPublisher);
            break;
        }
        case 4: {
            cout << "Enter new year: ";
            string newYear;
            cin >> newYear;
            book.updateYear(newYear);
            break;
        }
        default:
            cout << "Invalid choice" << endl;
            break;
    }
    
    library.books.insert(book);
    library.bookMap[book.getISBN()] = book;
    History history("Updated Book", book.getTitle(), book.getISBN());
    this->account.history.push_back(history);
}

void Librarian::updateStudent() {
    string userID;
    cout << "Enter Student ID or enter 0 to go back: ";
    cin >> userID;
    if (userID == "0") {
        return;
    }
    if (library.studentMap.find(userID) == library.studentMap.end()) {
        cout << "Student with this ID does not exist, Please try again." << endl;
        updateStudent();
        return;
    }
    Student student = library.studentMap[userID];
    library.students.erase(student);
    cout << "Enter the field you want to update: " << endl;
    vector<string> menu = {"Name"};
    int choice = printMenu(menu);
    switch(choice) {
        case 1: {
            cout << "Enter new name: ";
            cin.ignore();
            string temp;
            getline(cin, temp);
            student.updateName(temp);
            break;
        }
        default:
            cout << "Invalid choice" << endl;
            break;
    }
    library.students.insert(student);
    library.studentMap[userID] = student;
    History history("Updated Student", student.getName(), student.getUserID());
    this->account.history.push_back(history);
}

void Librarian::updateFaculty() {
    string userID;
    cout << "Enter Faculty ID or enter 0 to go back: ";
    cin >> userID;
    if(userID == "0") return;
    if(library.facultyMap.find(userID) == library.facultyMap.end()) {
        cout << "Faculty with this ID does not exist, Please try again." << endl;
        updateFaculty();
        return;
    }
    Faculty faculty = library.facultyMap[userID];
    library.faculties.erase(faculty);
    cout << "Enter the field you want to update: " << endl;
    vector<string> menu = {"Name"};
    int choice = printMenu(menu);
    switch(choice) {
        case 1: {
            cout << "Enter new name: ";
            cin.ignore();
            string temp;
            getline(cin, temp);
            faculty.updateName(temp);
            break;
        }
        default:
            cout << "Invalid choice" << endl;
            break;
    }
    library.faculties.insert(faculty);
    library.facultyMap[userID] = faculty;
    History history("Updated Faculty", faculty.getName(), faculty.getUserID());
    this->account.history.push_back(history);
}

void Librarian::updateLibrarian() {
    string userID;
    cout << "Enter Librarian ID or enter 0 to go back: ";
    cin >> userID;
    if (userID == "0") {
        return;
    }
    if (library.librarianMap.find(userID) == library.librarianMap.end()) {
        cout << "Librarian with this ID does not exist, Please try again." << endl;
        updateLibrarian();
        return;
    }
    if (userID == "L0001") {
        cout << "Cannot update root librarian" << endl;
        return;
    }
    Librarian librarian = library.librarianMap[userID];
    library.librarians.erase(librarian);
    cout << "Enter the field you want to update: " << endl;
    vector<string> menu = {"Name"};
    int choice = printMenu(menu);
    switch(choice) {
        case 1: {
            cout << "Enter new name: ";
            cin.ignore();
            string temp;
            getline(cin, temp);
            librarian.updateName(temp);
            break;
        }
        default:
            cout << "Invalid choice" << endl;
            break;
    }
    library.librarians.insert(librarian);
    library.librarianMap[userID] = librarian;
    History history("Updated Librarian", librarian.getName(), librarian.getUserID());
    this->account.history.push_back(history);
}
bool operator<(const Librarian &a, const Librarian &b) {
    return a.userID < b.userID;
}
Librarian::~Librarian() {
    // No dynamic resources to free.
}