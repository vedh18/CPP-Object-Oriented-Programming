#include <iostream>
#include <string>
#include "book.h"        // For Book
#include "history.h"     // For History records
#include "account.h"     // For Account
#include "user.h"        // For User base class
#include "student.h"     // For Student
#include "faculty.h"     // For Faculty
#include "librarian.h"   // For Librarian
#include "global.h"      // For the global Library object 'library'

using namespace std;

int main(){
    // Creat the root librarian
    cout << "Initializing the library management system" << endl;
    Librarian root("root", "L0001");
    library.librarians.insert(root);
    library.librarianMap["L0001"] = root;

   // 10 books, 5 students, 3 faculty and 1 librarian
    Book book1("978-0131103627", "The C Programming Language", 
        "Brian W. Kernighan, Dennis M. Ritchie", "Prentice Hall", "1988", "Available");
    library.books.insert(book1);
    library.bookMap["978-0131103627"] = book1;

    Book book2("978-0201633610", "Design Patterns: Elements of Reusable Object-Oriented Software", 
        "Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides", "Addison-Wesley Professional", "1994", "Available");
    library.books.insert(book2);
    library.bookMap["978-0201633610"] = book2;

    Book book3("978-0132350884", "Clean Code: A Handbook of Agile Software Craftsmanship", 
        "Robert C. Martin", "Prentice Hall", "2008", "Available");
    library.books.insert(book3);
    library.bookMap["978-0132350884"] = book3;

    Book book4("978-0137081073", "Effective C++", 
        "Scott Meyers", "Addison-Wesley Professional", "2005", "Available");
    library.books.insert(book4);
    library.bookMap["978-0137081073"] = book4;

    Book book5("978-0134494166", "Effective Modern C++", 
        "Scott Meyers", "O'Reilly Media", "2014", "Available");
    library.books.insert(book5);
    library.bookMap["978-0134494166"] = book5;

    Book book6("978-0262033848", "Introduction to Algorithms", 
        "Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein", "MIT Press", "2009", "Available");
    library.books.insert(book6);
    library.bookMap["978-0262033848"] = book6;

    Book book7("978-0131101630", "Structure and Interpretation of Computer Programs", 
        "Harold Abelson, Gerald Jay Sussman, Julie Sussman", "MIT Press", "1996", "Available");
    library.books.insert(book7);
    library.bookMap["978-0131101630"] = book7;

    Book book8("978-0134757599", "Clean Architecture", 
        "Robert C. Martin", "Prentice Hall", "2017", "Available");
    library.books.insert(book8);
    library.bookMap["978-0134757599"] = book8;

    Book book9("978-0596007126", "Head First Design Patterns", 
        "Eric Freeman, Elisabeth Robson, Bert Bates, Kathy Sierra", "O'Reilly Media", "2004", "Available");
    library.books.insert(book9);
    library.bookMap["978-0596007126"] = book9;

    Book book10("978-1491950357", "Effective Java", 
        "Joshua Bloch", "Addison-Wesley Professional", "2018", "Available");
    library.books.insert(book10);
    library.bookMap["978-1491950357"] = book10;

    Student student1("Alice Johnson", "S1001");
    library.students.insert(student1);
    library.studentMap["S1001"] = student1;

    Student student2("Brian Smith", "S1002");
    library.students.insert(student2);
    library.studentMap["S1002"] = student2;

    Student student3("Catherine Lee", "S1003");
    library.students.insert(student3);
    library.studentMap["S1003"] = student3;

    Student student4("David Kim", "S1004");
    library.students.insert(student4);
    library.studentMap["S1004"] = student4;

    Student student5("Emily Davis", "S1005");
    library.students.insert(student5);
    library.studentMap["S1005"] = student5;

    Faculty faculty1("Dr. Michael Brown", "F2001");
    library.faculties.insert(faculty1);
    library.facultyMap["F2001"] = faculty1;

    Faculty faculty2("Dr. Sarah Wilson", "F2002");
    library.faculties.insert(faculty2);
    library.facultyMap["F2002"] = faculty2;

    Faculty faculty3("Dr. Robert Miller", "F2003");
    library.faculties.insert(faculty3);
    library.facultyMap["F2003"] = faculty3;
    cout << "library management system successfully initialized!!" << endl;
    return 0;
}