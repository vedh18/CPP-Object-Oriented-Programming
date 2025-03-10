#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "global.h"     // Declares the global Library object 'library'
#include "library.h"    // Definition of the Library class
#include "book.h"       // Book class
#include "student.h"    // Student class
#include "faculty.h"    // Faculty class
#include "librarian.h"  // Librarian class
#include "user.h"       // Base User class
#include "history.h"    // History class
#include "account.h"    // Account class

// If you have utility functions like printMenu, include their header as well
#include "misc_functions.h"      // For functions like printMenu or split (if defined here)

using namespace std;

void studentHomePage(Student student){
    cout << "Welcome " << student.getName() << endl;
    cout << "What do you want to do?" << endl;
    int i1 = printMenu({"Borrow a book", "Return a book", "Reserve a book", "Unreserve a book", "View history", "Pay Fine", "View All books", "Go back"});
    switch(i1){
        case 1:
            student.borrowBook();
            studentHomePage(student);
            break;
        case 2:
            student.returnBook();
            studentHomePage(student);
            break;
        case 3:
            student.reserveBook();
            studentHomePage(student);
            break;
        case 4:
            student.unreserveBook();
            studentHomePage(student);
            break;
        case 5:
            student.account.viewHistory();
            studentHomePage(student);
            break;
        case 6:
            library.students.erase(student);
            student.account.payFine();
            library.students.insert(student);
            library.studentMap[student.getUserID()] = student;
            studentHomePage(student);
            break;
        case 7:
            library.viewAllBooks();
            studentHomePage(student);
            break;
        case 8:
            return;
        default:
            cout << "Invalid choice" << endl;
            studentHomePage(student);
            break;
    }
}
void studentLoginPage(){
    cout << "Welcome to the student login page" << endl;
    cout << "Enter your student ID: ";
    string studentID;
    cin >> studentID;
    if (library.studentMap.find(studentID) == library.studentMap.end()){
        cout << "Student not found" << endl;
        studentLoginPage();
        return;
    }
    Student student = library.studentMap[studentID];
    studentHomePage(student);
}
void facultyHomePage(Faculty& faculty){
    cout << "Welcome to the faculty home page" << endl;
    cout << "Please select an option: " << endl;
    int i2 = printMenu({"Borrow a book", "Return a book", "Reserve a book", "Unreserve a book", "View history", "View All Books", "Go back"});
    switch (i2){
        case 1:
            faculty.borrowBook();
            facultyHomePage(faculty);
            break;
        case 2:
            faculty.returnBook();
            facultyHomePage(faculty);
            break;
        case 3:
            faculty.reserveBook();
            facultyHomePage(faculty);
            break;
        case 4:
            faculty.unreserveBook();
            facultyHomePage(faculty);
            break;
        case 5:
            faculty.account.viewHistory();
            facultyHomePage(faculty);
            break;
        case 6:
            library.viewAllBooks();
            facultyHomePage(faculty);
            break;
        case 7:
            return;
        default:
            cout << "Invalid choice" << endl;
            facultyHomePage(faculty);
            break;
    }
}
void facultyLoginPage(){
    cout << "Welcome to the faculty login page" << endl;
    cout << "Enter your faculty ID: ";
    string facultyID;
    cin >> facultyID;
    if (library.facultyMap.find(facultyID) == library.facultyMap.end()){
        cout << "Faculty not found" << endl;
        facultyLoginPage();
        return;
    }
    Faculty faculty = library.facultyMap[facultyID];
    facultyHomePage(faculty);
}
void librarianHomePage(Librarian librarian){
    cout << "Welcome to the librarian home page" << endl;
    cout << "Please select an option: " << endl;
    int i3 = printMenu({"Create a new student", "Create a new faculty", "Create a new librarian", "Create a new book",
        "Remove a student", "Remove a faculty", "Remove a librarian", "Remove a book", "Update a student", "Update a faculty",
        "Update a librarian", "Update a book", "View history", "View all Books", "View all students", "View all faculty", "View all librarians", "Go back"});
    switch(i3){
        case 1:
            librarian.addStudent();
            librarianHomePage(librarian);
            break;
        case 2:
            librarian.addFaculty();
            librarianHomePage(librarian);
            break;
        case 3:
            librarian.addLibrarian();
            librarianHomePage(librarian);
            break;
        case 4:
            librarian.addBook();
            librarianHomePage(librarian);
            break;
        case 5:
            librarian.removeStudent();
            librarianHomePage(librarian);
            break;
        case 6:
            librarian.removeFaculty();
            librarianHomePage(librarian);
            break;
        case 7:
            librarian.removeLibrarian();
            librarianHomePage(librarian);
            break;
        case 8:
            librarian.removeBook();
            librarianHomePage(librarian);
            break;
        case 9:
            librarian.updateStudent();
            librarianHomePage(librarian);
            break;
        case 10:
            librarian.updateFaculty();
            librarianHomePage(librarian);
            break;
        case 11:
            librarian.updateLibrarian();
            librarianHomePage(librarian);
            break;
        case 12:
            librarian.updateBook();
            librarianHomePage(librarian);
            break;
        case 13:
            librarian.account.viewHistory();
            librarianHomePage(librarian);
            break;
        case 14:
            library.viewAllBooks();
            librarianHomePage(librarian);
            break;
        case 15:
            library.viewStudents();
            librarianHomePage(librarian);
            break;
        case 16:
            library.viewFaculties();
            librarianHomePage(librarian);
            break;
        case 17:
            library.viewLibrarians();
            librarianHomePage(librarian);
            break;
        case 18:
            return;
    }
}
void librarianLoginPage(){
    cout << "Welcome to the librarian login page" << endl;
    cout << "Enter your librarian ID: ";
    string librarianID;
    cin >> librarianID;
    if (library.librarianMap.find(librarianID) == library.librarianMap.end()){
        cout << "Librarian not found" << endl;
        librarianLoginPage();
        return;
    }
    Librarian librarian = library.librarianMap[librarianID];
    librarianHomePage(librarian);
}

int main(){
    cout << "Hello welcome to the library management system" << endl;
    cout << "Please select your role: " << endl;
    int x = printMenu({"Student", "Faculty", "Librarian", "Exit"});
    if (x == 1){
        studentLoginPage();
    }
    else if (x == 2){
        facultyLoginPage();
    }
    else if (x == 3){
        librarianLoginPage();
    }
    return 0;
}