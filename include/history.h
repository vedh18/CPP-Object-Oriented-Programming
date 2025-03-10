#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>  // For cout
#include <string>    // For string
#include <iomanip>     // For setw
#include <ctime>     // For time_t
using namespace std;

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

#endif
