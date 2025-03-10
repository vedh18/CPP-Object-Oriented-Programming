#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <ctime>
#include "Book.h"
#include "student.h"
#include "faculty.h"
#include "librarian.h"

using namespace std;
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
        void viewAllBooks();
        void viewAvailableBooks();
        void viewReservableBooks();
        void viewStudents();
        void viewFaculties();
        void viewLibrarians();
        ~Library();
    };

#endif