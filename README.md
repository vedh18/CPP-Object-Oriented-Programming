# Library Management System (LMS)

## Overview

This project implements a Library Management System (LMS) in C++ using Object-Oriented Programming (OOP) concepts. The system is designed to manage library operations effectively and demonstrates key OOP principles such as **abstraction**, **inheritance**, **polymorphism**, and **encapsulation**.

## Features

- **Role-Based Access**:  
  - **Students**: Can view all the books in the ibrary and check their status, borrow available books, reserve unavailable books, unreserve unwanted reserved books, return books, view their history, pay fines.
  - **Faculty**: Can view all the books in the ibrary and check their status, borrow available books, reserve unavailable books, unreserve unwanted reserved books, return books, view their history.
  - **Librarians**: Can add, remove, update books, manage users/books and view user history.
  
- **Reserve System**
  - A user can reserve any unavailable/borrowed book so that when it becomes available it isn't borrowed by anyone else.
  - Users can reserve a maximum of 3 books.
  - Whenever a user begins a reservation, the system checks if the reserved book is now available. If so, the system displays the reserved book along with other available books.
  - If the reserved book becomes available for more than 5 days and the user hasn't borrowed it yet, the book becomes unreservd automatically and is available for the general public to borrow.

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
    - Number of books overdue

- **File Persistence**:
  - The system saves its state (user records, book records, borrowing transactions) into csv files.
  - On startup, data is loaded from files to maintain continuity between sessions.
  - On exit, any changes made during the session are saved back to the files.
  - The files used are:
    - books.csv: contains the following attributes:
        - ISBN
        - Title
        - Author
        - Publisher
        - Year
        - Status
        - BorrowerID
        - BorrowedTime
        - isReserved
        - ReserverID
    - students.csv:
        - UserID
        - Name
        - Borrowed Book 1 (ISBN)
        - Borrowed Book 1 Time
        - Borrowed Book 2 (ISBN)
        - Borrowed Book 2 Time
        - Borrowed Book 3 (ISBN)
        - Borrowed Book 3 Time
        - Reserved Books(ISBNs) separated by ':'
    - faculty.csv
        - UserID
        - Name
        - Borrowed Book 1 (ISBN)
        - Borrowed Book 1 Time
        - Borrowed Book 2 (ISBN)
        - Borrowed Book 2 Time
        - Borrowed Book 3 (ISBN)
        - Borrowed Book 3 Time
        - Borrowed Book 4 (ISBN)
        - Borrowed Book 4 Time
        - Borrowed Book 5 (ISBN)
        - Borrowed Book 5 Time
        - Reserved Books(ISBNs) separated by ':'
    - librarians.csv
        - UserID
        - Name
## File Structure and Architecture

### File Structure
  ```bash
  Library Management System
    |   .gitignore
    |   README.md
    |
    +---.vscode
    |       settings.json
    |       tasks.json
    |       
    +---files
    |       books.csv
    |       faculty.csv
    |       librarians.csv
    |       students.csv
    |       
    +---include
    |       account.h
    |       book.h
    |       faculty.h
    |       global.h
    |       history.h
    |       librarian.h
    |       library.h
    |       misc_functions.h
    |       student.h
    |       user.h
    |       
    +---main
    |       implementaion.cpp
    |       initialization.cpp
    |       
    +---src
    |       account.cpp
    |       book.cpp
    |       faculty.cpp
    |       global.cpp
    |       history.cpp
    |       librarian.cpp
    |       library.cpp
    |       misc_functions.cpp
    |       student.cpp
    |       user.cpp
    |       
    +---temp
            classes.h
            oops.cpp
```
        

### Class Structure
- **Individual Class Files:**
  - Each class (e.g., `Book`, `User`, `Student`, `Faculty`, `Librarian`, `Account`, `History`, `Library`) has its own header (`.h`) file for declarations [(include)](https://github.com/vedh18/Library-Management-System/tree/main/include) and a corresponding source (`.cpp`) file for implementations[(src)](https://github.com/vedh18/Library-Management-System/tree/main/src).

### Global Object
- **Global Library Instance:**
  - Declared in `global.h` and defined in `global.cpp`.
- **Purpose:**
  - Ensures a single, consistent instance of the `Library` class is available across the entire application.
  - This global object contains the information which is loaded from the files on startup.
  - Every time this information is required we use this object.

### Main Files and Initialization
- **Entry Points:**
  - `initialization.cpp` is too initialize the data in the files.
  - `implementaion.cpp` is the code for the overall system run.

## Instructions to run

1. Clone the repository to your local machine.
2. Open the project in your preferred IDE (e.g., Visual Studio Code).
3. Adjust the time unit on line 5 in [classes.h]([https://github.com/vedh18/CPP-Object-Oriented-Programming/blob/main/lms/classes.h](https://github.com/vedh18/Library-Management-System/blob/main/src/global.cpp)) to your preferred time unit.
4. First to initialize the database run the following two commands:
   ```bash
   
   g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude src\account.cpp src\book.cpp src\faculty.cpp src\global.cpp src\history.cpp src\librarian.cpp src\library.cpp src\misc_functions.cpp src\student.cpp src\user.cpp main\initialization.cpp -o lms.exe
   
   ```
   ```bash
   .\lms.exe
   ```
   Basically just compiling and executing the initialization.cpp file.
6. Then open terminal and run these two commands to actually run the software:
    ```bash
   
   g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude src\account.cpp src\book.cpp src\faculty.cpp src\global.cpp src\history.cpp src\librarian.cpp src\library.cpp src\misc_functions.cpp src\student.cpp src\user.cpp main\implementaion.cpp.cpp -o lms.exe
   
   ```
   ```bash
   .\lms.exe
   ```
7. Follow the prompts to interact with the Library Management System.

## Improvements in the future:
- Implement User Authentication while logging in the users
- Allow multiple copies of the same book(ISBN)
- Privatize data structures
- Make a verification function for the librarian to verify weather the book is actually returned or weather the fine is actually paid.
- Make the UI better.