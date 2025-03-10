#include "library.h"

void Library::readFromBooks(string file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cout << file_path << endl;
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
        book.updateYear(row[4]);
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
    std::ifstream file(file_path);
    // std::cout << "YES" << std::endl;

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        cout << "Please exit as the application wont work properly." << endl;
        return;
    }

    std::string line;
    Student student;

    while (std::getline(file, line)) {
        // If the line is empty, we break out of the loop.
        if (line.empty()) {
            // std::cout << "YES" << std::endl;
            break;
        }

        // Split the line by commas into a vector.
        std::vector<std::string> row;
        std::string cell;
        std::istringstream lineStream(line);
        // std::cout << "YES1" << std::endl;

        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        // std::cout << "YES" << std::endl;

        // Make sure we have at least two elements for userID and name.
        if (row.size() > 0) {
            student.updateUserID(row[0]);
        }
        if (row.size() > 1) {
            student.updateName(row[1]);
        }

        // std::cout << "YES1.2" << std::endl; 

        // Insert Book 1 if row[2] exists and is not empty
        if (row.size() > 2 && !row[2].empty()) {
            student.account.borrowedBooks.insert(bookMap[row[2]]);
        }
        // Insert Book 2 if row[4] exists and is not empty
        if (row.size() > 4 && !row[4].empty()) {
            student.account.borrowedBooks.insert(bookMap[row[4]]);
        }
        // Insert Book 3 if row[6] exists and is not empty
        if (row.size() > 6 && !row[6].empty()) {
            student.account.borrowedBooks.insert(bookMap[row[6]]);
        }

        // std::cout << "YES2" << std::endl;

        // Check for reserved books (row[8])
        if (row.size() > 8 && !row[8].empty()) {
            // std::cout << "YES" << std::endl;
            // Assume 'split' is a helper function that splits by ':'
            for (const std::string& reservedBookID : split(row[8], ':')) {
                // Only insert if reservedBookID is not empty
                if (!reservedBookID.empty()) {
                    student.account.reservedBooks.insert(bookMap[reservedBookID]);
                }
            }
        }

        // Insert the student into the set and map
        students.insert(student);
        studentMap[student.getUserID()] = student;
    }

    file.close();
}

void Library::readFromLibrarians(string file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines instead of breaking, in case there are gaps in the file.
        if (line.empty()) {
            continue;
        }
        
        std::vector<std::string> row;
        std::string cell;
        std::istringstream lineStream(line);
        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        
        // Check if there are at least two columns: userID and Name.
        if (row.size() < 2) {
            std::cerr << "Insufficient data in line, skipping: " << line << std::endl;
            continue;
        }
        
        // Create a new Librarian object for each line.
        Librarian librarian;
        librarian.updateUserID(row[0]);
        librarian.updateName(row[1]);
        
        librarians.insert(librarian);
        librarianMap[librarian.getUserID()] = librarian;
    }
    
    file.close();
}


void Library::readFromFaculties(string file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {
            break;
        }

        std::vector<std::string> row;
        std::string cell;
        std::istringstream lineStream(line);

        // Split CSV line by commas
        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }

        // Create a fresh Faculty object for each line
        Faculty faculty;

        // Safely update userID (row[0]) if available
        if (row.size() > 0 && !row[0].empty()) {
            faculty.updateUserID(row[0]);
        }

        // Safely update Name (row[1]) if available
        if (row.size() > 1 && !row[1].empty()) {
            faculty.updateName(row[1]);
        }

        // Book 1 (ID) at row[2]
        if (row.size() > 2 && !row[2].empty()) {
            faculty.account.borrowedBooks.insert(bookMap[row[2]]);
        }

        // Book 2 (ID) at row[4]
        if (row.size() > 4 && !row[4].empty()) {
            faculty.account.borrowedBooks.insert(bookMap[row[4]]);
        }

        // Book 3 (ID) at row[6]
        if (row.size() > 6 && !row[6].empty()) {
            faculty.account.borrowedBooks.insert(bookMap[row[6]]);
        }

        // Book 4 (ID) at row[8]
        if (row.size() > 8 && !row[8].empty()) {
            faculty.account.borrowedBooks.insert(bookMap[row[8]]);
        }

        // Book 5 (ID) at row[10]
        if (row.size() > 10 && !row[10].empty()) {
            faculty.account.borrowedBooks.insert(bookMap[row[10]]);
        }

        // Reserved Books (IDs) at row[12]
        if (row.size() > 12 && !row[12].empty()) {
            // Assume 'split' is a helper function that splits a string by ':'
            for (const std::string& reservedBookID : split(row[12], ':')) {
                if (!reservedBookID.empty()) {
                    faculty.account.reservedBooks.insert(bookMap[reservedBookID]);
                }
            }
        }

        // Insert into your data structures
        faculties.insert(faculty);
        facultyMap[faculty.getUserID()] = faculty;
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
    readFromBooks("C:\\Users\\vedha\\Library-Management-System\\lms\\files\\books.csv");
    readFromStudents("C:\\Users\\vedha\\Library-Management-System\\lms\\files\\students.csv");
    readFromFaculties("C:\\Users\\vedha\\Library-Management-System\\lms\\files\\faculty.csv");
    readFromLibrarians("C:\\Users\\vedha\\Library-Management-System\\lms\\files\\librarians.csv");
}
void Library::viewAllBooks(){
    for (auto book : books){
        book.printBook();
    }
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
    writeToBooks("C:\\Users\\vedha\\Library-Management-System\\lms\\files\\books.csv");
    writeToStudents("C:\\Users\\vedha\\Library-Management-System\\lms\\files\\students.csv");
    writeToFaculties("C:\\Users\\vedha\\Library-Management-System\\lms\\files\\faculty.csv");
    writeToLibrarians("C:\\Users\\vedha\\Library-Management-System\\lms\\files\\librarians.csv");
}