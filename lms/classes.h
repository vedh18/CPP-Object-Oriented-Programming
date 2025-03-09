#include <bits/stdc++.h>
#include <ctime>
using namespace std;
// LIBRARY MANAGEMENT SYSTEM:

// Lets say we have a unit of time in terms of seconds.
// 1 day = 86400 seconds
// 1 minute = 60 seconds

// TODO:
// Make the main function and input validation.

// If time left TODO:
// Privatize data structures
// Make a verification function for the librarian to verify weather the book is actually returned or weather the fine is actually paid.

int timeUnit = 86400; // 1 day

int printMenu(vector<string> menu){
    for (int i = 0; i < menu.size(); i++){
        cout << i+1 << ". " << menu[i] << endl;
    }
    cout << "Enter your choice: ";
    int x;
    cin >> x;
    return x;
}

time_t convertDateString(const std::string &dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%d %b %Y %H:%M:%S");
    if (ss.fail()) {
        return -1;
    }
    return std::mktime(&tm);
}

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(s);
    std::string token;
    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
std::string timeToDateString(time_t t) {
    std::tm* tm_ptr = std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(tm_ptr, "%d %b %Y %H:%M:%S");
    return oss.str();
} 
class Book {
    private:
        // Generic details
        string ISBN;
        string title;
        string author;
        string publisher;
        int year;
    
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
        Book(string ISBN, string title, string author, string publisher, int year, string status);
    
        // Getter functions
        string getISBN() const;
        string getTitle() const;
        string getAuthor() const;
        string getPublisher() const;
        int getYear() const;
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
        void updateYear(int y);
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
class History {
    private:
        time_t time;
        string action;
    public:
        // Constructors
        History(string action);
        History(string action, string name, string ID);
    
        // Member function to print the history record
        void printHistory();
    
        // Destructor
        ~History();
};
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
        
class Student : public User {
    public:
        // Constructors
        Student();
        Student(string name, string userID);

        // Member functions
        void borrowBook();
        friend bool operator<(const Student &a, const Student &b);
        // Destructor
        ~Student();
};
        
class Faculty : public User {
    public:
        // Constructors
        Faculty();
        Faculty(string name, string userID);

        // Member functions
        void borrowBook();

        friend bool operator<(const Faculty &a, const Faculty &b);
        // Destructor
        ~Faculty();
};
        
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
class Library {
    private:
        void readFromBooks(string file_path);
        void readFromStudents(string file_path);
        void readFromFaculties(string file_path);
        void readFromLibrarians(string file_path);
        void writeToBooks(string filename);
        void writeToStudents(string filename);
        void writeToFaculties(string filepath);
        void writeToLibrarians(string filepath);
    public:
        set<Book> books;
        set<Student> students;
        set<Faculty> faculties;
        set<Librarian> librarians;
        map<string, Book> bookMap;
        map<string, Student> studentMap;
        map<string, Faculty> facultyMap;
        map<string, Librarian> librarianMap;
        
        Library();
        void viewAvailableBooks();
        void viewReservableBooks();
        void viewStudents();
        void viewFaculties();
        void viewLibrarians();
        ~Library();
    };

Library library;
// Default constructor
Book::Book() : borrowedTime(0), reserved(false), reservedTime(0) {}

// Parameterized constructor
Book::Book(string ISBN, string title, string author, string publisher, int year, string status)
    : ISBN(ISBN), title(title), author(author), publisher(publisher), year(year),
      status(status), borrowedTime(0), reserved(false), reservedTime(0) {}

// Getter functions
string Book::getISBN() const { return ISBN; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getPublisher() const { return publisher; }
int Book::getYear() const { return year; }
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
void Book::updateYear(int y) { year = y; }
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

History::History(string action) {
    this->action = action;
    this->time = std::time(0);
}

History::History(string action, string name, string ID) {
    this->action = action + " " + name + "(" + ID + ")";
    this->time = std::time(0);
}

void History::printHistory() {
    cout << left << setw(30) << action << setw(30) << std::ctime(&time) << endl;
}

History::~History() {
    // No resources to free
}
string Account::getUserID(){
    return this->userID;
}

void Account::updateUserID(string newUserID){
    this->userID = newUserID;
}

Account::Account() : fine(0), overdueBooks(0) {
    // Default constructor
}

Account::Account(string userID) : userID(userID), fine(0), overdueBooks(0) {
    // Parameterized constructor
}

void Account::checkReservedBooks(){
    cout << "These are the books which you had reserved and are now available: " << endl;
    for (Book book : reservedBooks){
        if (book.getStatus() == "Reserved"){
            book.printBook();
        }
    }
}

void Account::calcFine(){
    for (auto book : borrowedBooks){
        time_t currentTime = std::time(0);
        int days = (currentTime - book.getBorrowedTime()) / timeUnit;
        if (userType == "Student"){
            fine += days * 10;
        }
        else if (userType == "Faculty"){
            if (days > 60){
                overdueBooks++;
            }
        }
    }
}

void Account::payFine(){
    History history("Fine Paid");
    this->history.push_back(history);
    fine = 0;   
}

void Account::viewHistory(){
    for (auto curr_history : history){
        curr_history.printHistory();
    }
}

Account::~Account(){
    // Destructor: No dynamic memory to free.
}
// Default constructor
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
    cout << "Enter the ISBN of the book you want to return: ";
    cin.ignore();
    string ISBN;
    getline(cin, ISBN);

    Book book = library.bookMap[ISBN];
    this->account.borrowedBooks.erase(book);
    library.books.erase(book);

    book.returnBook(this->account.userType);

    library.bookMap[ISBN] = book;
    library.books.insert(book);

    History history("Returned Book", book.getTitle(), book.getISBN());
    this->account.history.push_back(history);
}

void User::reserveBook() {
    if (this->account.reservedBooks.size() >= 3) {
        cout << "Cannot reserve more than 3 books" << endl;
        return;
    }
    cout << "Here are the books which are not available currently and can be reserved: " << endl;
    library.viewReservableBooks();
    cout << "Enter the ISBN of the book you want to reserve: ";
    cin.ignore();
    string ISBN;
    getline(cin, ISBN);

    Book book = library.bookMap[ISBN];
    library.books.erase(book);

    book.reseverBook(this->userID);

    library.bookMap[ISBN] = book;
    library.books.insert(book);

    this->account.reservedBooks.insert(book);
    cout << "Book reserved successfully, you will be notified when it becomes available." << endl;
    History history("Reserved Book", book.getTitle(), book.getISBN());
    this->account.history.push_back(history);
}

void User::unreserveBook() {
    cout << "Here are the books you have reserved: " << endl;
    for (auto book : this->account.reservedBooks) {
        book.printBook();
    }
    cout << "Enter the ISBN of the book you want to unreserve: ";
    cin.ignore();
    string ISBN;
    getline(cin, ISBN);

    Book book = library.bookMap[ISBN];
    library.books.erase(book);
    this->account.reservedBooks.erase(book);

    book.unreserveBook();

    library.bookMap[ISBN] = book;
    library.books.insert(book);
}

User::~User() {
    // Destructor: no dynamic memory to free here.
}

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
    cout << "Enter the ISBN of the book you want to borrow: ";
    cin.ignore();
    string ISBN;
    getline(cin, ISBN);

    Book book = library.bookMap[ISBN];
    library.books.erase(book);
    
    book.borrowBook();

    this->account.borrowedBooks.insert(book);
    library.bookMap[ISBN] = book;
    library.books.insert(book);

    History history("Borrowed Book", book.getTitle(), book.getISBN());
    this->account.history.push_back(history);
}

Student::~Student() {
    // No dynamic resources to free.
}
bool operator<(const Student &a, const Student &b) {
    return a.userID < b.userID;
}
/*---------------------- Faculty Class Implementation ----------------------*/

// Default constructor
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
    cout << "Enter the ISBN of the book you want to borrow: ";
    cin.ignore();
    string ISBN;
    getline(cin, ISBN);
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

/*---------------------- Librarian Class Implementation ----------------------*/

// Default constructor
Librarian::Librarian() {}

// Parameterized constructor
Librarian::Librarian(string name, string userID) : User(name, userID, "Librarian") {}

// Add a new book (status set to Available by default)
void Librarian::addBook() {
    string ISBN, title, author, publisher, status;
    int year;
    cout << "Enter Book ISBN: ";
    cin >> ISBN;

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
    string name, userID;
    cin.ignore();
    cout << "Enter Student Name: " << endl;
    getline(cin, name);
    cout << "Enter Student ID: " << endl;
    cin >> userID;
    Student student(name, userID);
    library.students.insert(student);
    library.studentMap[userID] = student;
    History history("Created Student", student.getName(), student.getUserID());
    this->account.history.push_back(history);
}

void Librarian::addFaculty() {
    string name, userID;
    cin.ignore();
    cout << "Enter Faculty Name: " << endl;
    getline(cin, name);
    cout << "Enter Faculty ID: " << endl;
    cin >> userID;
    Faculty faculty(name, userID);
    library.faculties.insert(faculty);
    library.facultyMap[userID] = faculty;
    History history("Created Faculty", faculty.getName(), faculty.getUserID());
    this->account.history.push_back(history);
}

void Librarian::addLibrarian() {
    string name, userID;
    cin.ignore();
    cout << "Enter Librarian Name: " << endl;
    getline(cin, name);
    cout << "Enter Librarian ID: " << endl;
    cin >> userID;
    Librarian librarian(name, userID);
    library.librarians.insert(librarian);
    library.librarianMap[userID] = librarian;
    History history("Created Librarian", librarian.getName(), librarian.getUserID());
    this->account.history.push_back(history);
}

void Librarian::removeBook() {
    string ISBN;
    cout << "Enter Book ISBN: ";
    cin >> ISBN;
    // Erase the book from the library collections.
    library.books.erase(library.bookMap[ISBN]);
    library.bookMap.erase(ISBN);
    History history("Deleted Book", library.bookMap[ISBN].getTitle(), ISBN);
    this->account.history.push_back(history);
}

void Librarian::removeStudent() {
    string userID;
    cout << "Enter Student ID: ";
    cin >> userID;
    library.students.erase(library.studentMap[userID]);
    library.studentMap.erase(userID);
    History history("Deleted Student", library.studentMap[userID].getName(), userID);
    this->account.history.push_back(history);
}

void Librarian::removeFaculty() {
    string userID;
    cout << "Enter Faculty ID: ";
    cin >> userID;
    library.faculties.erase(library.facultyMap[userID]);
    library.facultyMap.erase(userID);
    History history("Deleted Faculty", library.facultyMap[userID].getName(), userID);
    this->account.history.push_back(history);
}

void Librarian::removeLibrarian() {
    string userID;
    cout << "Enter Librarian ID: ";
    cin >> userID;
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
    cout << "Enter Book ISBN: ";
    cin >> ISBN;
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
            int newYear;
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
    cout << "Enter Student ID: ";
    cin >> userID;
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
    cout << "Enter Faculty ID: ";
    cin >> userID;
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
    cout << "Enter Librarian ID: ";
    cin >> userID;
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

void Library::readFromBooks(string file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    string line;
    Book book;
    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        vector<string> row;
        string cell;
        istringstream lineStream(line);
        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        book.updateISBN(row[0]);
        book.updateTitle(row[1]);
        book.updateAuthor(row[2]);
        book.updatePublisher(row[3]);
        book.updateYear(stoi(row[4]));
        book.updateStatus(row[5]);
        book.updateBorrowerID(row[6]);
        book.updateBorrowedTime(convertDateString(row[7]));
        book.updateReserved(row[8] == "1");
        book.updateReserverID(row[9]);
        books.insert(book);
        bookMap[book.getISBN()] = book;
    }
    file.close();
}

void Library::readFromStudents(string file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    string line;
    Student student;
    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        vector<string> row;
        string cell;
        istringstream lineStream(line);
        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        // Expected row format:
        // userID,Student Name,Book 1,Issued Date,Book 2,Issued Date,Book 3,Issued Date,Reserved Books (ID)
        student.updateUserID(row[0]);
        student.updateName(row[1]);
        student.account.borrowedBooks.insert(bookMap[row[2]]);
        student.account.borrowedBooks.insert(bookMap[row[4]]);
        student.account.borrowedBooks.insert(bookMap[row[6]]);
        for (string reservedBookID : split(row[8], ':')) {
            student.account.reservedBooks.insert(bookMap[reservedBookID]);
        }
        students.insert(student);
        studentMap[student.getUserID()] = student;
    }
    file.close();
}

void Library::readFromFaculties(string file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    string line;
    Faculty faculty;
    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        vector<string> row;
        string cell;
        istringstream lineStream(line);
        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        // Expected row format:
        // userID,Name,Book 1 (ID),Book 1 Issue Date,Book 2 (ID),Book 2 Issue Date,
        // Book 3 (ID),Book 3 Issue Date,Book 4 (ID),Book 4 Issue Date,Book 5 (ID),Book 5 Issue Date,Reserved Books(IDs)
        faculty.updateUserID(row[0]);
        faculty.updateName(row[1]);
        faculty.account.borrowedBooks.insert(bookMap[row[2]]);
        faculty.account.borrowedBooks.insert(bookMap[row[4]]);
        faculty.account.borrowedBooks.insert(bookMap[row[6]]);
        faculty.account.borrowedBooks.insert(bookMap[row[8]]);
        faculty.account.borrowedBooks.insert(bookMap[row[10]]);
        for (string reservedBookID : split(row[12], ':')) {
            faculty.account.reservedBooks.insert(bookMap[reservedBookID]);
        }
        faculties.insert(faculty);
        facultyMap[faculty.getUserID()] = faculty;
    }
    file.close();
}

void Library::readFromLibrarians(string file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    string line;
    Librarian librarian;
    while (getline(file, line)) {
        if (line.empty()) {
            break;
        }
        vector<string> row;
        string cell;
        istringstream lineStream(line);
        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        // Expected row format: userID,Name
        librarian.updateUserID(row[0]);
        librarian.updateName(row[1]);
        librarians.insert(librarian);
        librarianMap[librarian.getUserID()] = librarian;
    }
    file.close();
}

void Library::writeToBooks(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    // Format: ISBN,Title,Author,Publisher,Year,Status,BorrowerID,BorrowedTime,Reserved,ReserverID
    for (auto book : books) {
        file << book.getISBN() << ","
             << book.getTitle() << ","
             << book.getAuthor() << ","
             << book.getPublisher() << ","
             << book.getYear() << ","
             << book.getStatus() << ","
             << book.getBorrowerID() << ","
             << timeToDateString(book.getBorrowedTime()) << ","
             << (book.isReserved() ? "1" : "0") << ","
             << book.getReserverID() << endl;
    }
    file.close();
}

void Library::writeToStudents(string filename) {
    ofstream file(filename);
    if (!file.is_open()){
        cerr << "Error opening file" << endl;
        return;
    }
    // Format: userID,Student Name,Book 1,Issued Date,Book 2,Issued Date,Book 3,Issued Date,Reserved Books (ID)
    for (auto student : students) {
        file << student.getUserID() << "," << student.getName() << ",";
        int i = 0;
        for (auto book : student.account.borrowedBooks) {
            file << book.getISBN() << "," << timeToDateString(book.getBorrowedTime());
            if (i < 2) {
                file << ",";
            }
            i++;
        }
        file << ",";
        i = 0;
        for (auto book : student.account.reservedBooks) {
            file << book.getISBN();
            if (i < student.account.reservedBooks.size() - 1) {
                file << ":";
            }
            i++;
        }
        file << endl;
    }
    file.close();
}

void Library::writeToFaculties(string filepath) {
    ofstream file(filepath);
    if (!file.is_open()){
        cerr << "Error opening file" << endl;
        return;
    }
    // Format: userID,Name,Book 1 (ID),Book 1 Issue Date,...,Reserved Books (IDs)
    for (auto faculty : faculties) {
        file << faculty.getUserID() << "," << faculty.getName() << ",";
        int i = 0;
        for (auto book : faculty.account.borrowedBooks) {
            file << book.getISBN() << "," << timeToDateString(book.getBorrowedTime());
            if (i < 4) {
                file << ",";
            }
            i++;
        }
        file << ",";
        i = 0;
        for (auto book : faculty.account.reservedBooks) {
            file << book.getISBN();
            if (i < faculty.account.reservedBooks.size() - 1) {
                file << ":";
            }
            i++;
        }
        file << endl;
    }
    file.close();
}

void Library::writeToLibrarians(string filepath) {
    ofstream file(filepath);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    // Format: userID,Name
    for (auto librarian : librarians) {
        file << librarian.getUserID() << "," << librarian.getName() << endl;
    }
    file.close();
}

Library::Library() {
    readFromBooks("files\\books.csv");
    readFromStudents("files\\Users\\students.csv");
    readFromFaculties("files\\Users\\faculty.csv");
    readFromLibrarians("files\\Users\\librarians.csv");
}

void Library::viewAvailableBooks() {
    time_t currentTime = std::time(0);
    vector<Book> updatedBooks;
    
    for (auto book : books) { // iterate by copy
        if (book.isReserved()) {
            int days = (currentTime - book.getReservedTime()) / timeUnit;
            if (days > 5) {
                book.updateStatus("Available");
                book.updateReserved(false);
                book.updateReservedTime(0);
                book.updateReserverID("");
                bookMap[book.getISBN()] = book; // update in the map
            }
        }
        if (book.getStatus() == "Available") {
            book.printBook();
        }
        updatedBooks.push_back(book);
    }
    
    books.clear();
    for (auto &book : updatedBooks) {
        books.insert(book);
    }
}

void Library::viewReservableBooks() {
    for (auto book : books) {
        if (book.getStatus() == "Borrowed" && !book.isReserved()) {
            book.printBook();
        }
    }
}

void Library::viewStudents() {
    for (auto student : students) {
        student.printUser();
    }
}

void Library::viewFaculties() {
    for (auto faculty : faculties) {
        faculty.printUser();
    }
}

void Library::viewLibrarians() {
    for (auto librarian : librarians) {
        librarian.printUser();
    }
}

Library::~Library() {
    writeToBooks("files\\books.csv");
    writeToStudents("files\\Users\\students.csv");
    writeToFaculties("files\\Users\\faculty.csv");
    writeToLibrarians("files\\Users\\librarians.csv");
}