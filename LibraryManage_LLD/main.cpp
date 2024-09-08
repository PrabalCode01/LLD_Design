#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>

using namespace std;

// Book class follows the Single Responsibility Principle (SRP)
// It is responsible only for managing the details of a book (OOP: Encapsulation)
class Book {
public:
    int bookID;
    string title;
    string author;
    bool isAvailable;

    // Constructor: Encapsulation is used to initialize attributes
    Book(int id, string t, string a) : bookID(id), title(t), author(a), isAvailable(true) {}

    // Method to display book details: Follows SRP (Single Responsibility)
    void displayBook() {
        cout << "Book ID: " << bookID << ", Title: " << title << ", Author: " << author
             << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

// User class also follows SRP, responsible for managing user-related data
class User {
public:
    int userID;
    string name;
    vector<int> borrowedBooks; // Keeps track of borrowed books (Encapsulation)

    // Constructor
    User(int id, string n) : userID(id), name(n) {}

    // Follows SRP: Managing borrowed books (OOP: Encapsulation)
    void borrowBook(int bookID) {
        borrowedBooks.push_back(bookID);
        cout << name << " borrowed book with ID: " << bookID << endl;
    }

    // Follows SRP: Responsible for returning books
    void returnBook(int bookID) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == bookID) {
                borrowedBooks.erase(it); // Encapsulation in action here
                cout << name << " returned book with ID: " << bookID << endl;
                return;
            }
        }
        cout << "No such book borrowed." << endl;
    }
};

// Transaction class follows SRP: Responsible for managing transactions
// Open/Closed Principle (OCP): Can extend without modifying the class itself (e.g., different types of transactions)
class Transaction {
public:
    int transactionID;
    int bookID;
    int userID;
    time_t borrowDate;
    time_t returnDate;
    bool isReturned;

    // Constructor initializes the transaction attributes
    Transaction(int tID, int bID, int uID, time_t bDate) 
        : transactionID(tID), bookID(bID), userID(uID), borrowDate(bDate), isReturned(false) {}

    // Follows SRP: Returning a book and recording the return date
    void returnBook(time_t rDate) {
        returnDate = rDate;
        isReturned = true;
    }

    // Fine calculation is a specific responsibility: Follows SRP
    // It uses Encapsulation by keeping calculation details inside the class
    int calculateFine() {
        if (!isReturned) return 0;
        int daysLate = difftime(returnDate, borrowDate) / (60 * 60 * 24);
        int fine = max(0, daysLate - 14) * 5; // 14 days allowed, $5/day fine after
        return fine;
    }
};

// Library class follows the Dependency Inversion Principle (DIP)
// It manages high-level operations by relying on low-level classes like Book, User, Transaction
class Library {
public:
    unordered_map<int, Book> books;  // Storing books
    unordered_map<int, User> users;  // Storing users
    vector<Transaction> transactions; // List of transactions
    int transactionCounter = 0;

    // SRP: Library manages only books, users, and transactions
    // OCP: Can extend functionality (e.g., notifications) without modifying core operations

    // Adds a book to the library inventory: Follows SRP
    void addBook(int bookID, string title, string author) {
        books[bookID] = Book(bookID, title, author);
    }

    // Adds a user to the library system: Follows SRP
    void addUser(int userID, string name) {
        users[userID] = User(userID, name);
    }

    // Borrowing logic: Combines the responsibilities of different classes (Book, User, Transaction)
    void borrowBook(int userID, int bookID) {
        if (books[bookID].isAvailable) {
            books[bookID].isAvailable = false;  // Managing book's availability
            users[userID].borrowBook(bookID);   // Delegating borrow responsibility to User class
            transactions.push_back(Transaction(transactionCounter++, bookID, userID, time(0)));
        } else {
            cout << "Book is not available." << endl;
        }
    }

    // Return logic: Combines responsibilities and calculates fine (SRP)
    void returnBook(int userID, int bookID) {
        books[bookID].isAvailable = true;  // Book is now available again
        users[userID].returnBook(bookID);  // Delegating return responsibility to User class
        for (auto &trans : transactions) {
            if (trans.bookID == bookID && trans.userID == userID && !trans.isReturned) {
                trans.returnBook(time(0));  // Mark the book as returned
                int fine = trans.calculateFine();  // Fine calculation follows SRP
                if (fine > 0) {
                    cout << "Fine for late return: $" << fine << endl;
                } else {
                    cout << "Book returned on time. No fine." << endl;
                }
                break;
            }
        }
    }

    // Display books in the library: SRP
    void displayBooks() {
        for (auto &book : books) {
            book.second.displayBook();
        }
    }
};

int main() {
    Library lib;  // High-level module that depends on low-level components

    // Adding books
    lib.addBook(1, "The Great Gatsby", "F. Scott Fitzgerald");
    lib.addBook(2, "1984", "George Orwell");
    lib.addBook(3, "To Kill a Mockingbird", "Harper Lee");

    // Adding users
    lib.addUser(1, "Alice");
    lib.addUser(2, "Bob");

    // Display available books
    lib.displayBooks();

    // Borrow books
    lib.borrowBook(1, 1); // Alice borrows book ID 1
    lib.borrowBook(2, 2); // Bob borrows book ID 2

    // Display books after borrowing
    lib.displayBooks();

    // Returning books
    lib.returnBook(1, 1); // Alice returns book ID 1
    lib.returnBook(2, 2); // Bob returns book ID 2

    // Display books after returning
    lib.displayBooks();

    return 0;
}
