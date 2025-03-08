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

// TODO: Use private attributes, and also validate input wherever we are recieving the input.
class Library{
    public:
        // TODO: check if all the data structures are updated carefully or not.
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
            readFromStudents("files\\students.csv");
            readFromFaculties("files\\faculties.csv");
            readFromLibrarians("files\\librarians.csv");
        }
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
                book.ISBN = row[0];
                book.title = row[1];
                book.author = row[2];
                book.publisher = row[3];
                book.year = stoi(row[4]);
                book.status = row[5];
                book.borrowerID = row[6];
                book.borrowedTime = stoi(row[7]);
                book.reserved = (row[8] == "1" ? true : false);
                book.reserverID = row[9];
                books.insert(book);
                bookMap[book.ISBN] = book;
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
                student.userID = row[0];
                student.name = row[1];
                student.account.borrowedBooks.insert(bookMap[row[2]]);
                
                student.account.borrowedBooks.insert(bookMap[row[4]]);
                student.account.borrowedBooks.insert(bookMap[row[6]]);
                students.insert(student);
                studentMap[student.userID] = student;
            }
            file.close();
        }
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
                faculty.name = row[0];
                faculty.userID = row[1];
                faculties.insert(faculty);
                facultyMap[faculty.userID] = faculty;
            }
            file.close();
        }
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
                librarian.name = row[0];
                librarian.userID = row[1];
                librarians.insert(librarian);
                librarianMap[librarian.userID] = librarian;
            }
            file.close();
        }
        void viewAvailableBooks(){
            for(auto book : books){
                if (book.status == "Available"){
                    book.printBook();
                }
            }
        }
        void viewReservableBooks(){
            for(auto book : books){
                if (book.status == "Borrowed" && book.reserved == false){
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
        ~Library(){}
}; 

Library library;

class History {
    public:
        string action; 
        // Borrowed, Returned, Reserved, Unreserved, Fine Paid, Created Book, Updated Book, Deleted Book, 
        // Created Student, Updated Student, Deleted Student, Created Faculty, Updated Faculty, Deleted Faculty, 
        // Created Librarian, Updated Librarian, Deleted Librarian.
        time_t time;
        History(string action){
            this->action = action;
            this->time = std::time(0);
        }
        History(string action, string userID){
            this->action = action;
            this->action += " ";
            this->action += userID;
            this->time = std::time(0);
        }
        void printHistory(){
                cout << left << setw(30) << action  << setw(30) << std::ctime(&time) << endl;
        }
        ~History(){}
};
class Account {
    public:
        string userType; // Student/Faculty/Librarian
        string userID;
        set<Book> reservedBooks;
        set<Book> borrowedBooks;
        vector<History> history;
        int fine;
        // TODO: Overdue books displayed to user and faculty.
        int overdueBooks = 0;
        Account(){}
        Account(string userID){
            this->userID = userID;
            this->fine = 0;
        }
        void checkReservedBooks(){
            for (auto book : reservedBooks){
                if (book.status == "Available"){
                    cout << "Book " << book.title << " is now available." << endl;
                    book.reserved = false;
                    book.reserverID = "";
                    book.status = "Available";
                }
            }
        }
        void calcFine(){
            for (auto book : borrowedBooks){
                time_t currentTime = std::time(0);
                int days = (currentTime - book.borrowedTime) / timeUnit;
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
            fine = 0;
        }
        ~Account(){}
};
class User {
    public:
        string name;
        string userID;
        Account account; // Account class to handle user activity
        User(){}
        User(string name, string userID, string userType){
            this->name = name;
            this->userID = userID;
            this->account.userID = userID;
            this->account.userType = userType;
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
            book.returnBook();
            this->account.borrowedBooks.erase(book);
        }
        void reserveBook(){
            cout << "Here are the books which are not available currently and can be reserved: " << endl;
            library.viewReservableBooks();
            cout << "Enter the ISBN of the book you want to reserve: ";
            cin.ignore();
            string ISBN;
            getline(cin, ISBN);
            Book book = library.bookMap[ISBN];
            book.reseverBook(this->userID);
            this->account.reservedBooks.insert(book);
            cout << "Book reserved successfully, you will be notified when it becomes available." << endl;
        }
        void viewHistory(){
            for (auto history : this->account.history){
                history.printHistory();
            }
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
            cout << "Enter the ISBN of the book you want to borrow: ";
            cin.ignore();
            string ISBN;
            getline(cin, ISBN);
            Book book = library.bookMap[ISBN];
            book.borrowBook();
            this->account.borrowedBooks.insert(book);
        }
        ~Student(){}
};
class Librarian : public User {
    public:
        Librarian(){}
        Librarian(string name, string userID) : User(name, userID, "Librarian") {}
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
            cout << "Enter Book Status: ";
            getline(cin, status); 
            Book book(ISBN, title, author, publisher, year, status);
            library.books.insert(book);
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
        }
        void removeBook(){
            string ISBN;
            cout << "Enter Book ISBN: ";
            cin >> ISBN;
            library.books.erase(library.bookMap[ISBN]);
            library.bookMap.erase(ISBN);
        }
        void removeStudent(){
            string userID;
            cout << "Enter Student ID: ";
            cin >> userID;
            library.students.erase(library.studentMap[userID]);
            library.studentMap.erase(userID);
        }
        void removeFaculty(){
            string userID;
            cout << "Enter Faculty ID: ";
            cin >> userID;
            library.faculties.erase(library.facultyMap[userID]);
            library.facultyMap.erase(userID);
        }
        void removeLibrarian(){
            string userID;
            cout << "Enter Librarian ID: ";
            cin >> userID;
            if (userID == "L0001"){
                cout << "Cannot delete root librarian" << endl;
                return;
            }
            if (userID == this->userID){
                cout << "Cannot delete self" << endl;
                return;
            }
            library.librarians.erase(library.librarianMap[userID]);
            library.librarianMap.erase(userID);
        }
        // TODO: Implement update student, faculty, librarian and books
        // TODO: remember to update the book status carefully.
        // void updateBook(){
        //     string bookID;
        //     cout << "Enter Book ID: ";
        //     cin >> bookID;
        //     library.books.erase(library.bookMap[bookID]);
        //     // library.bookMap.erase(bookID);
        //     cout << "Enter the field you want to update: "  << endl;
        //     int x = printMenu({"Title", "Author", "Publisher", "Year", "Status"});
        //     if (x == 1){
        //         string title;
        //         cout << "Enter new title: ";
        //         cin >> title;
        //         library.bookMap[bookID].title = title;
        //     }
        //     else if (x == 2){
        //         string author;
        //         cout << "Enter new author: ";
        //         cin >> author;
        //         library.bookMap[bookID].author = author;
        //     }
        //     else if (x == 3){
        //         string publisher;
        //         cout << "Enter new publisher: ";
        //         cin >> publisher;
        //         library.bookMap[bookID].publisher = publisher;
        //     }
        //     else if (x == 4){
        //         int year;
        //         cout << "Enter new year: ";
        //         cin >> year;
        //         library.bookMap[bookID].year = year;
        //     }
        //     else if (x == 5){
        //         string old_status = library.bookMap[bookID].status;
        //         int i1 = printMenu({"Available", "Borrowed", "Reserved"});
        //         if (i1 == 1){
        //             if (old_status == "Borrowed"){

        //             }
        //         }
        //         else if (i1 == 2){
        //             library.bookMap[bookID].status = "Borrowed";
        //         }
        //         else if (i1 == 3){
        //             library.bookMap[bookID].status = "Reserved";
        //         }
        //         cin >> status;
                
        //     }
        //     library.books.insert(library.bookMap[bookID]);
        // }
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
            cout << "Enter the ISBN of the book you want to borrow: ";
            cin.ignore();
            string ISBN;
            getline(cin, ISBN);
            Book book = library.bookMap[ISBN];
            book.borrowBook();
            this->account.borrowedBooks.insert(book);
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

//     • Librarian:
//         → Can manage the library, including:
                // • Viewing, Adding, removing, or updating books.
                // • Adding or removing users.

// 2. Books
// Define a Book class to represent books in the library.
//     Constraints:
//         • Start with at least 5 books in the system.
//         • Books can only be borrowed if their status is ”Available.”
class Book{
    public:
        // generic details
        string ISBN;
        string title;
        string author;
        string publisher;
        int year;

        // book status
        string status; // Available, Borrowed, Reserved

        string borrowerID;
        time_t borrowedTime = 0;

        bool reserved = false;
        string reserverID;

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
            if (status == "Available"){
                status = "Borrowed";
                borrowedTime = std::time(0);
            }
            else{
                cout << "Book is currently " << status << endl;
            }
        }
        void returnBook(){
            if (reserved){
                status = "Reserved";
                borrowedTime = 0;
            }
            else if (status == "Borrowed"){
                status = "Available";
                borrowedTime = 0;
            }
            else{
                cout << "Book is currently " << status << endl;
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
        ~Book(){}
};
// 4. Rules
// The system should persist its data using files. This ensures that the library’s state (e.g., user
// records, borrowed books, and fines) is retained between program sessions.
//     • Borrowing Rules:
//     • Overdue Check:
//         If the book is returned after the borrowing period (15 days for students, 30 days for
//         faculty), the system should:
//             ∗ Calculate the overdue period.
//             ∗ Display to User Side
//     • User Account Update:
//         ∗ Remove the book from the current borrow list in the user’s account.
//         ∗ Add the book to the borrowing history.
//     • Borrowing Eligibility:
//         ∗ If fines exist, prevent further borrowing until the fine is cleared.

int main(){
    // Creat the root librarian
    Librarian root("root", "L0001");

    return 0;
}