#include <bits/stdc++.h>
using namespace std;
// LIBRARY MANAGEMENT SYSTEM:

// - Students and Faculty: Can borrow books, return them, and view their borrowing history.
// - Librarians: Can manage books and users.
// - Each user and book will have unique id
// - Users should be able to borrow and return books within specified limits
// - Students will incur fines for overdue returns, while faculty members will have extended borrowing privileges without fines. Librarians will have the authority to add, remove, and update both books and users in the system.
// - The system will provide a clean and user-friendly interface to perform operations such as borrowing, returning, and viewing details of books and users. 
// - It will also demonstrate the implementation of OOP concepts like inheritance, abstraction, and polymorphism through its class structure.

// 1. Users
//     • Students:
//         → Can only view all the books which are available in the library.
//         → Can borrow up to 3 books at a time.
//         → Maximum borrowing period: 15 days.
//         → Fines: 10 rupees per day for overdue books.
//         → Cannot manage books or other users.

//     • Faculty:
//         → Can only view all the books which are available in the library.
//         → Can borrow up to 5 books at a time.
//         → Maximum borrowing period: 30 days.
//         → Fines: No fine for overdue books.
//         → Cannot manage books or other users.

//     • Librarian:
//         → Can manage the library, including:
                // • Viewing, Adding, removing, or updating books.
                // • Adding or removing users.
//         → Can not borrow books

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
        string title;
        string author;
        string publisher;
        int year;
        string ISBN;
        string status;
}
// 3. Accounts
// Create an Account class to track user activity. Each user has one account. The account must:
//     • Maintain a record of currently borrowed books.
//     • Track overdue books and calculate fines

class Account {
protected:
    string userID;
    vector<Book> reservedBooks;
    vector<Book> borrowedBooks;
public:
    
}
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
//                 Fine = Days Overdue × 10 rupees/day.
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

    return 0;
}