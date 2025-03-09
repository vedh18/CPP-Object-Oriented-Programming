#include <bits/stdc++.h>
#include <ctime>
using namespace std;
// LIBRARY MANAGEMENT SYSTEM:

// - Students and Faculty: Can borrow books, return them, and view their borrowing history.

// - Users should be able to borrow and return books within specified limits
// - Students will incur fines for overdue returns, while faculty members will have extended borrowing privileges without fines. Librarians will have the authority to  update both books and users in the system.
// - The system will provide a clean and user-friendly interface to perform operations such as borrowing, returning.
// - It will also demonstrate the implementation of OOP concepts like inheritance, abstraction, and polymorphism through its class structure.

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
class Library{
    private:
        void readFromBooks(string file_path){
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
        void readFromStudents(string file_path){
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
                // userID,Student Name,Book 1,Issued Date,Book 2,Issued Date,Book 3,Issued Date,Reserved Books (ID)
                student.updateUserID(row[0]);
                // student.name = row[1];
                student.updateName(row[1]);
                student.account.borrowedBooks.insert(bookMap[row[2]]);
                student.account.borrowedBooks.insert(bookMap[row[4]]);
                student.account.borrowedBooks.insert(bookMap[row[6]]);
                // Resrved Books (IDs) contains comma seperated string IDs of the books the student has reserved.
                for (string reservedBookID : split(row[8], ':')) {
                    student.account.reservedBooks.insert(bookMap[reservedBookID]);
                }
                students.insert(student);
                studentMap[student.getUserID()] = student;
            }
            file.close();
        }
        // userID,Name,Book 1 (ID),Book 1 Issue Date,Book 2 (ID),Book 2 Issue Date,Book 3 (ID),Book 3 Issue Date,Book 4 (ID),Book 4 Issue Date,Book 5 (ID),Book 5 Issue Date,Reserved Books(IDs)
        void readFromFaculties(string file_path){
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
                faculty.updateUserID(row[0]);
                faculty.updateName(row[1]);
                faculty.account.borrowedBooks.insert(bookMap[row[2]]);
                faculty.account.borrowedBooks.insert(bookMap[row[4]]);
                faculty.account.borrowedBooks.insert(bookMap[row[6]]);
                faculty.account.borrowedBooks.insert(bookMap[row[8]]);
                faculty.account.borrowedBooks.insert(bookMap[row[10]]);
                // Resrved Books (IDs) contains colon seperated string IDs of the books the student has reserved.
                for (string reservedBookID : split(row[12], ':')) {
                    faculty.account.reservedBooks.insert(bookMap[reservedBookID]);
                }
                faculties.insert(faculty);
                facultyMap[faculty.getUserID()] = faculty;
            }
            file.close();
        }
        // userID,Name
        void readFromLibrarians(string file_path){
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
                librarian.updateUserID(row[0]);
                librarian.updateName(row[1]);
                librarians.insert(librarian);
                librarianMap[librarian.getUserID()] = librarian;
            }
            file.close();
        }
        // All the books from the books set should be written to the books.csv file.
        void writeToBooks(string filename){
            ofstream file(filename);
            if (!file.is_open()) {
                cerr << "Error opening file" << endl;
                return;
            }
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
        // Format: userID,Student Name,Book 1,Issued Date,Book 2,Issued Date,Book 3,Issued Date,Reserved Books (ID)
        void writeToStudents(string filename){
            ofstream file(filename);
            if (!file.is_open()){
                cerr << "Error opening file" << endl;
                return;
            }
            for (auto student : students){
                file << student.getUserID() << "," << student.getName() << ",";
                int i = 0;
                for (auto book : student.account.borrowedBooks){
                    file << book.getISBN() << "," << timeToDateString(book.getBorrowedTime());
                    if (i < 2){
                        file << ",";
                    }
                    i++;
                }
                file << ",";
                i = 0;
                for (auto book : student.account.reservedBooks){
                    file << book.getISBN();
                    if (i < student.account.reservedBooks.size() - 1){
                        file << ":";
                    }
                    i++;
                }
                file << endl;
            }
            file.close();
        }
        // Format: userID,Name,Book 1 (ID),Book 1 Issue Date, ... ,Reserved Books (IDs)
        void writeToFaculties(string filepath){
            ofstream file(filepath);
            if (!file.is_open()){
                cerr << "Error opening file" << endl;
                return;
            }
            for (auto faculty : faculties){
                file << faculty.getUserID() << "," << faculty.getName() << ",";
                int i = 0;
                for (auto book : faculty.account.borrowedBooks){
                    file << book.getISBN() << "," << timeToDateString(book.getBorrowedTime());
                    if (i < 4){
                        file << ",";
                    }
                    i++;
                }
                file << ",";
                i = 0;
                for (auto book : faculty.account.reservedBooks){
                    file << book.getISBN();
                    if (i < faculty.account.reservedBooks.size() - 1){
                        file << ":";
                    }
                    i++;
                }
                file << endl;
            }
            file.close();
        }
        void writeToLibrarians(string filepath){
            ofstream file(filepath);
            if (!file.is_open()) {
                cerr << "Error opening file" << endl;
                return;
            }
            for (auto librarian : librarians){
                file << librarian.getUserID() << "," << librarian.getName() << endl;
            }
            file.close();
        }
    public:
        set<Book> books;
        set<Student> students;
        set<Faculty> faculties;
        set<Librarian> librarians;
        map<string, Book> bookMap;
        map<string, Student> studentMap;
        map<string, Faculty> facultyMap;
        map<string, Librarian> librarianMap;
        Library(){
            readFromBooks("files\\books.csv");
            readFromStudents("files\\Users\\students.csv");
            readFromFaculties("files\\Users\\faculties.csv");
            readFromLibrarians("files\\Users\\librarians.csv");
        }
        void viewAvailableBooks() {
            time_t currentTime = std::time(0);
            std::vector<Book> updatedBooks;
            
            for (auto book : books) {  // Iterate by value (copy)
                if (book.isReserved()) {
                    int days = (currentTime - book.getReservedTime()) / timeUnit;
                    if (days > 5) {
                        book.updateStatus("Available");
                        book.updateReserved(false);
                        book.updateReservedTime(0);
                        book.updateReserverID("");
                        bookMap[book.getISBN()] = book; // Update in the map
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
        
        void viewReservableBooks(){
            for(auto book : books){
                if (book.getStatus() == "Borrowed" && book.isReserved() == false){
                    book.printBook();
                }
            }
        }
        void viewStudents(){
            for(auto student : students){
                student.printUser();
            }
        }
        void viewFaculties(){
            for (auto faculty : faculties){
                faculty.printUser();
            }
        }
        void viewLibrarians(){
            for(auto librarian : librarians){
                librarian.printUser();
            }
        }
        ~Library(){
            writeToBooks("files\\books.csv");
            writeToStudents("files\\Users\\students.csv");
            writeToFaculties("files\\Users\\faculties.csv");
            writeToLibrarians("files\\Users\\librarians.csv");
        }
}; 

Library library;

class History {
    private:
        time_t time;
        string action; 
        // Borrowed, Returned, Reserved, Fine Paid, Created Book, Updated Book, Deleted Book, 
        // Created Student, Updated Student, Deleted Student, Created Faculty, Updated Faculty, Deleted Faculty, 
        // Created Librarian, Updated Librarian, Deleted Librarian.
    public:
        History(string action){
            this->action = action;
            this->time = std::time(0);
        }
        History(string action, string name, string ID){
            this->action = action;
            this->action += " ";
            this->action += name;
            this->action += "(";
            this->action += ID;
            this->action += ")";
            this->time = std::time(0);
        }
        void printHistory(){
                cout << left << setw(30) << action  << setw(30) << std::ctime(&time) << endl;
        }
        ~History(){}
};
class Account {
    private:
        string userID;
    public:
        string userType; // Student/Faculty/Librarian

        set<Book> reservedBooks;
        set<Book> borrowedBooks;

        vector<History> history;

        int fine = 0;
        int overdueBooks = 0;
        string getUserID(){
            return this->userID;
        }
        void updateUserID(string newUserID){
            this->userID = newUserID;
        }
        Account(){}
        Account(string userID){
            this->userID = userID;
            this->fine = 0;
        }
        void checkReservedBooks(){
            cout << "These are the books which you had reserved and are now available: " << endl;
            for (auto book : reservedBooks){
                if (book.getStatus() == "Reserved"){
                    book.printBook();
                }
            }
        }
        void calcFine(){
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
        void payFine(){
            History history("Fine Paid");
            this->history.push_back(history);
            fine = 0;   
        }
        void viewHistory(){
            for (auto curr_history : history){
                curr_history.printHistory();
            }
        }
        ~Account(){}
};
class User {
    private:
        string name;
        string userID;
    public:
        Account account; // Account class to handle user activity
        User(){}
        User(string name, string userID, string userType){
            this->name = name;
            this->userID = userID;
            this->account.updateUserID(userID);
            this->account.userType = userType;
        }
        string getUserID(){
            return this->userID;
        }
        void updateUserID(string newUserID){
            this->userID = newUserID;
            this->account.updateUserID(newUserID);
        }
        string getName(){
            return this->name;
        }
        void updateName(string newName){
            this->name = newName;
        }
        void printUser(){
            cout << left;
            cout << setw(12) << "Name: " << name << endl;
            cout << setw(12) << "ID: " << userID << endl;
            cout << endl;
        }   
        void returnBook(){
            if (this->account.borrowedBooks.size() == 0){
                cout << "No books to return" << endl;
                return;
            }
            cout << "Here are the books you have borrowed: " << endl;
            for (auto book : this->account.borrowedBooks){
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
        void reserveBook(){
            if (this->account.reservedBooks.size() >= 3){
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
        void unreserveBook(){
            cout << "Here are the books you have reserved: " << endl;
            for (auto book : this->account.reservedBooks){
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
        ~User(){}
    };


class Student : public User {
    public:
        Student(){}
        Student(string name, string userID) : User(name, userID, "Student") {}
        void borrowBook(){
            if (this->account.borrowedBooks.size() >= 3){
                cout << "Cannot borrow more than 3 books" << endl;
                return;
            }
            if (this->account.fine > 0){
                cout << "You have a fine of " << this->account.fine << " rupees, please pay the fine first." << endl;
                return;
            }
            cout << "Here are the available books: " << endl;
            library.viewAvailableBooks();
            // display the books which were reserved by the user and are now available.
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
        ~Student(){}
};
class Librarian : public User {
    public:
        Librarian(){}
        Librarian(string name, string userID) : User(name, userID, "Librarian") {}
        
        // By default while adding book status will be available only.
        void addBook() {
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
        void addStudent(){
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
        void addFaculty(){
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
        void addLibrarian(){
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
        void removeBook(){
            string ISBN;
            cout << "Enter Book ISBN: ";
            cin >> ISBN;
            library.books.erase(library.bookMap[ISBN]);
            library.bookMap.erase(ISBN);
            History history("Deleted Book", library.bookMap[ISBN].title, ISBN);
            this->account.history.push_back(history);
        }
        void removeStudent(){
            string userID;
            cout << "Enter Student ID: ";
            cin >> userID;
            library.students.erase(library.studentMap[userID]);
            library.studentMap.erase(userID);
            History history("Deleted Student", library.studentMap[userID].name, userID);
            this->account.history.push_back(history);
        }
        void removeFaculty(){
            string userID;
            cout << "Enter Faculty ID: ";
            cin >> userID;
            library.faculties.erase(library.facultyMap[userID]);
            library.facultyMap.erase(userID);
            History history("Deleted Faculty", library.facultyMap[userID].name, userID);
            this->account.history.push_back(history);
        }
        void removeLibrarian(){
            string userID;
            cout << "Enter Librarian ID: ";
            cin >> userID;
            if (userID == "L0001"){
                cout << "Cannot delete root librarian" << endl;
                return;
            }
            if (userID == this->getUserID()){
                cout << "Cannot delete self" << endl;
                return;
            }
            library.librarians.erase(library.librarianMap[userID]);
            library.librarianMap.erase(userID);
            History history("Deleted Librarian", library.librarianMap[userID].name, userID);
            this->account.history.push_back(history);
        }
        void updateBook(){
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
        void updateStudent(){
            string userID;
            cout << "Enter Student ID: ";
            cin >> userID;
            Student student = library.studentMap[userID];
            library.students.erase(student);
            cout << "Enter the field you want to update: " << endl;
            vector<string> menu = {"Name"};
            int choice = printMenu(menu);
            switch(choice){
                case 1:{
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
        void updateFaculty(){
            string userID;
            cout << "Enter Faculty ID: ";
            cin >> userID;
            Faculty faculty = library.facultyMap[userID];
            library.faculties.erase(faculty);
            cout << "Enter the field you want to update: " << endl;
            vector<string> menu = {"Name"};
            int choice = printMenu(menu);
            switch(choice){
                case 1:{
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
        void updateLibrarian(){
            string userID;
            cout << "Enter Librarian ID: ";
            cin >> userID;
            if (userID == "L0001"){
                cout << "Cannot update root librarian" << endl;
                return;
            }
            Librarian librarian = library.librarianMap[userID];
            library.librarians.erase(librarian);
            cout << "Enter the field you want to update: " << endl;
            vector<string> menu = {"Name"};
            int choice = printMenu(menu);
            switch(choice){
                case 1:{
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
        ~Librarian(){}
};

class Faculty : public User {
    public:
        Faculty(){}
        Faculty(string name, string userID) : User(name, userID, "Faculty") {}
        void borrowBook(){
            this->account.calcFine();
            if (this->account.borrowedBooks.size() >= 5){
                cout << "Cannot borrow more than 5 books" << endl;
                return;
            }
            if (this->account.overdueBooks > 0){
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
        ~Faculty(){}
};
// 1. Users
//     • Students:
//         → Maximum borrowing period: 15 days.
//         → Fines: 10 rupees per day for overdue books.

//     • Faculty:
//         → Can borrow up to 5 books at a time.
//         → Maximum borrowing period: 30 days.
//         → Fines: No fine for overdue books.


// 2. Books
// Define a Book class to represent books in the library.
//     Constraints:
//         • Start with at least 5 books in the system.
//         • Books can only be borrowed if their status is ”Available.”
class Book{
    private:
        // Generic details
        string ISBN;
        string title;
        string author;
        string publisher;
        int year;

        // Book status details
        string status; // "Available", "Borrowed", "Reserved"
        string borrowerID;
        time_t borrowedTime = 0;
        bool reserved = false;
        time_t reservedTime = 0;
        string reserverID;
    public:
         // Getter functions
        std::string getISBN() const { return ISBN; }
        std::string getTitle() const { return title; }
        std::string getAuthor() const { return author; }
        std::string getPublisher() const { return publisher; }
        int getYear() const { return year; }
        std::string getStatus() const { return status; }
        std::string getBorrowerID() const { return borrowerID; }
        time_t getBorrowedTime() const { return borrowedTime; }
        bool isReserved() const { return reserved; }
        time_t getReservedTime() const { return reservedTime; }
        std::string getReserverID() const { return reserverID; }

        // Updater (setter) functions
        void updateISBN(const std::string &isbn) { ISBN = isbn; }
        void updateTitle(const std::string &t) { title = t; }
        void updateAuthor(const std::string &a) { author = a; }
        void updatePublisher(const std::string &p) { publisher = p; }
        void updateYear(int y) { year = y; }
        void updateStatus(const std::string &s) { status = s; }
        void updateBorrowerID(const std::string &id) { borrowerID = id; }
        void updateBorrowedTime(time_t t) { borrowedTime = t; }
        void updateReserved(bool r) { reserved = r; }
        void updateReservedTime(time_t t) { reservedTime = t; }
        void updateReserverID(const std::string &id) { reserverID = id; }
        Book(){}
        Book(string ISBN, string title, string author, string publisher, int year, string status){
            this->title = title;
            this->author = author;
            this->publisher = publisher;
            this->year = year;
            this->ISBN = ISBN;
            this->status = status;
        }
        void printBook(){
            cout << left; // Align text to the left
            cout << setw(12) << "Title:"     << title     << endl;
            cout << setw(12) << "Author:"    << author    << endl;
            cout << setw(12) << "Publisher:" << publisher << endl;
            cout << setw(12) << "Year:"      << year      << endl;
            cout << setw(12) << "ISBN:"      << ISBN      << endl;
            cout << setw(12) << "Status:"    << status    << endl;
            cout << endl;
        }
        void borrowBook(){
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
        void returnBook(string userType){
            //         If the book is returned after the borrowing period (15 time units for students, 30 time units for
            //         faculty), the system should:
            //             ∗ Calculate the overdue period.
            //             ∗ Display to User Side
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
        void reseverBook(string userID){
            if (status == "Borrowed"){
                reserved = true;
                reserverID = userID;
            }
            else{
                cout << "Book is currently " << status << endl;
            }
        }
        void unreserveBook(){
            reserved = false;
            reserverID = "";
            if (status == "Reserved"){
                status = "Available";
            }
        }
        ~Book(){}
};
// 4. Rules
// The system should persist its data using files. This ensures that the library’s state (e.g., user
// records, borrowed books, and fines) is retained between program sessions.
//     • Borrowing Rules:
//     • User Account Update:
//         ∗ Remove the book from the current borrow list in the user’s account.
//         ∗ Add the book to the borrowing history.

int main(){
    // Creat the root librarian
    Librarian root("root", "L0001");

    return 0;
}