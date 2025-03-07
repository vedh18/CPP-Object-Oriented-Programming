#include <bits/stdc++.h>
#include <ctime>
using namespace std;
// LIBRARY MANAGEMENT SYSTEM:

// - Students and Faculty: Can borrow books, return them, and view their borrowing history.
// - Users should be able to borrow and return books within specified limits
// - Students will incur fines for overdue returns, while faculty members will have extended borrowing privileges without fines. Librarians will have the authority to add, remove, and update both books and users in the system.
// - The system will provide a clean and user-friendly interface to perform operations such as borrowing, returning, and viewing details of books and users. 
// - It will also demonstrate the implementation of OOP concepts like inheritance, abstraction, and polymorphism through its class structure.

// Lets say we have a unit of time in terms of seconds.
// 1 day = 86400 seconds
// 1 minute = 60 seconds
int timeUnit = 86400; // 1 day
class Library{
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
            

        }
        void viewBooks(){
            for(auto book : books){
                book.printBook();
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
        string userID = "NA"; 
        time_t time;
        History(string action){
            this->action = action;
            this->time = std::time(0);
        }
        History(string action, string userID){
            this->action = action;
            this->userID = userID;
            this->time = std::time(0);
        }
        void printHistory(){
            if (userID == "NA"){
                cout << left << setw(15) << action  << setw(15) << userID << setw(30) << std::ctime(&time) << endl;
            }
            else
                cout << left << setw(15) << action  << setw(30) << std::ctime(&time) << endl;
        }
        ~History(){}
};
class Account {
    public:
        string userID;
        set<Book> reservedBooks;
        set<Book> borrowedBooks;
        vector<History> history;
        int fine;
        Account(){}
        Account(string userID){
            this->userID = userID;
            this->fine = 0;
        }
        ~Account(){}
};
class User {
    public:
        string name;
        string userID;
        Account account; // Account class to handle user activity
        User(string name, string userID){
            this->name = name;
            this->userID = userID;
            this->account.userID = userID;
        }
        void printUser(){
            cout << left;
            cout << setw(12) << "Name: " << name << endl;
            cout << setw(12) << "ID: " << userID << endl;
            cout << endl;
        }   
        void borrowBook(){
            if (this->account.borrowedBooks.size() >= 3){
                cout << "Cannot borrow more than 3 books" << endl;
                return;
            }
            cout << "Here are the available books: " << endl;
            library.viewBooks();
            cout << "Enter the ISBN of the book you want to borrow: ";
            cin.ignore();
            string ISBN;
            getline(cin, ISBN);
            Book book = library.bookMap[ISBN];
            this->account.borrowedBooks.insert(book);
            book.borrowBook();
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
        ~User(){}
    };


class Student : public User {
    public:
        Student(string name, string userID) : User(name, userID) {}
        ~Student(){}
};
class Librarian : public User {
    public:
        Librarian(string name, string userID) : User(name, userID) {}
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
        ~Librarian(){}
};

class Faculty : public User {
    public:
        Faculty(string name, string userID) : User(name, userID) {}
        ~Faculty(){}
};
// 1. Users
//     • Students:
//         → Can only view all the books which are available in the library.
//         → Can borrow up to 3 books at a time.
//         → Maximum borrowing period: 15 days.
//         → Fines: 10 rupees per day for overdue books.

//     • Faculty:
//         → Can only view all the books which are available in the library.
//         → Can borrow up to 5 books at a time.
//         → Maximum borrowing period: 30 days.
//         → Fines: No fine for overdue books.

//     • Librarian:
//         → Can manage the library, including:
                // • Viewing, Adding, removing, or updating books.
                // • Adding or removing users.

// 2. Books
// Define a Book class to represent books in the library.
//     Attributes:
//         • title, author, publisher, year, and ISBN.
//         • Status: Tracks whether the book is available, borrowed, or reserved.

//     Constraints:
//         • Start with at least 5 books in the system.
//         • Books can only be borrowed if their status is ”Available.”
class Book{
    public:
        string ISBN;
        string title;
        string author;
        string publisher;
        int year;
        string status;
        time_t borrowedTime = 0;
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
            if (status == "Borrowed"){
                status = "Available";
                borrowedTime = 0;
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
//         • Students and faculty can borrow books based on their role constraints.
//         • If a user tries to borrow more than the allowed number of books, the system should
//         deny the request.
//         • If a user has unpaid fines, borrowing new books should not be allowed until the fines
//         are cleared.
//         • The system should provide an option for users to simulate payment of fines.
//         • Users can view their total outstanding fines and mark them as paid through a dedicated menu option.
//         • Once the payment is made, the fine amount should reset to zero, and borrowing
//         restrictions should be lifted.
//         • Returning and Updating Rules:
//     • Update Book Status:
//         Upon the return of a book, its status should be updated to “Available” in the system.
//         • Fine Calculation:
//             ∗ For Students:
//                Fine = Days Overdue × 10 rupees/day. 
//             ∗ For Faculty:
//                 · No fine for overdue books.
//                 · Faculty members cannot borrow additional books if they (a) Have already reached
//                 the limit of 5 borrowed books, or (b) Have an overdue book for more than 60
//                 days.
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