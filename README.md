# Library Management System (LMS)

## Overview

This project implements a Library Management System (LMS) in C++ using Object-Oriented Programming (OOP) concepts. The system is designed to manage library operations effectively and demonstrates key OOP principles such as **abstraction**, **inheritance**, **polymorphism**, and **encapsulation**.

The LMS allows different user roles to interact with the library:
- **Students**: Can borrow up to 3 books at a time, with a maximum borrowing period of 15 days and fines incurred for overdue books.
- **Faculty**: Can borrow up to 5 books with a borrowing period of 30 days, with no fines for overdue books (though restrictions apply if a book is overdue for more than 60 days).
- **Librarians**: Manage library operations, including adding, removing, and updating books as well as managing users. Librarians do not borrow books.

## Features

- **Role-Based Access**:  
  - **Students**: Can borrow, reserve unavailable books, return books, view their history, pay fines, and search for books.
  - **Faculty**: Can borrow, reserve unavailable books, return books, view their history, and search for books.
  - **Librarians**: Can add, remove, update books, manage users, and view user history.
  
- *Reserve System*
  - A user can only reserve a book for a max of 5 time units.
  - Users can reserve books that are currently unavailable.
  - Whenever a user begins a reservation, the system checks if the reserved book is now available. If so, the system displays the reserved book along with other available books.

- **Book Management**:
  - Each book has attributes such as title, author, publisher, year, and ISBN.
  - Book statuses include "Available," "Borrowed," and "Reserved".
  - The Book class also stores information regarding the borrowedTime, borrowerID, reservedTime and reserverID,

- **Account Handling**:
  - Each user has an associated Account that tracks:
    - Current borrowed books.
    - Current Reserved books.
    - Borrowing history.
    - Overdue fines (calculated based on user role).

- **File Persistence**:
  - The system saves its state (user records, book records, borrowing transactions) into csv files.
  - On startup, data is loaded from files to maintain continuity between sessions.
  - On exit, any changes made during the session are saved back to the files.

- **OOP Principles**:
  - **Encapsulation**: Private attributes with public getter and setter methods.
  - **Inheritance**: Derived classes (Student, Faculty, Librarian) extend the base `User` class.
  - **Polymorphism**: Overridden methods such as `borrowBook()` and `returnBook()` in derived classes to handle role-specific rules.
  - **Abstraction**: Clear separation of concerns between classes like `User`, `Book`, `Account`, and `Library`.

## Instructions to run

1. Clone the repository to your local machine.
2. Open the project in your preferred IDE (e.g., Visual Studio Code).
3. In classes.h go to lines 1433-1436 and 1497-1500 and change the string to your local path of the csv files.
4. Adjust the time unit on line 16 in classes.h to your preferred time unit.
5. First to initialize the database run initialization.cpp
6. Then open terminal and run these two commands:
    g++ -std=c++11 lms\implementaion.cpp -o main.exe
    .\main.exe
7. Follow the prompts to interact with the Library Management System.


