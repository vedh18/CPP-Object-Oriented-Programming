#include "account.h"
string Account::getUserID(){
    return this->userID;
}

void Account::updateUserID(string newUserID){
    this->userID = newUserID;
}

Account::Account() : fine(0), overdueBooks(0) {
    // Default constructor
}

Account::Account(string userID) : userID(userID), fine(0), overdueBooks(0) {
    // Parameterized constructor
}

void Account::checkReservedBooks(){
    cout << "These are the books which you had reserved and are now available: " << endl;
    for (Book book : reservedBooks){
        if (book.getStatus() == "Reserved" && book.getReserverID() == userID){
            book.printBook();
        }
    }
}

void Account::calcFine(){
    for (auto book : borrowedBooks){
        time_t currentTime = std::time(0);
        int days = (currentTime - book.getBorrowedTime()) / timeUnit;
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

void Account::payFine(){
    calcFine();
    cout << "You have a fine of " << fine << " rupees, do you want to pay it? (Y/N): ";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y'){
        cout << "Fine paid successfully!" << endl;
        fine = 0;
        History history("Fine Paid");
        this->history.push_back(history);
    }
    else if (choice == 'N' || choice == 'n'){
        cout << "Fine not paid :(" << endl;
        return;
    }
    else{
        cout << "Invalid choice. Please try again" << endl;
        payFine();
    }

}

void Account::viewHistory(){
    for (auto curr_history : history){
        curr_history.printHistory();
    }
}

Account::~Account(){
    // Destructor: No dynamic memory to free.
}