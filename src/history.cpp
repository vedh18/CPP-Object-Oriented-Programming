#include "history.h"

History::History(string action) {
    this->action = action;
    this->time = std::time(0);
}

History::History(string action, string name, string ID) {
    this->action = action + " " + name + "(" + ID + ")";
    this->time = std::time(0);
}

void History::printHistory() {
    cout << left << setw(30) << action << setw(30) << std::ctime(&time) << endl;
}

History::~History() {
    // No resources to free
}