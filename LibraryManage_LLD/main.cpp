#include<iostream>
#include<vector>
#include<unordered_map>
#include<ctime>

using namespace std;

class Book {
// Book class follows the Single Responsibility Principle (SRP)
// It is responsible only for managing the details of a book (OOP: Encapsulation)

public:
     
     int bookId;
     string title;
     string author;
     bool isAvailable;

    // Constructor: Encapsulation is used to initialize attributes
     Book(int id, string t, string a): bookId(id),title(t),author(a),isAvailable(true) {};

     // Method to display book details: Follows SRP (Single Responsibility)
     void displayBooKDetails(){
           cout << "Book ID: " << bookId << endl;
           cout<< "Title: " << title <<endl;
           cout<<" Author: " << author<<endl;
           cout<<"Available: " << (isAvailable ? "Yes" : "No") << endl;
     }
};



class User {

public:
     // It also follows SRP
     int userId;
     string name;
     vector<int> borrowedBooks; // Keeps track of borrowed books 


    User(int id, string n): userId(id),name(n){};  // constructor


   // Follows SRP: Managing borrowed books (OOP: Encapsulation)
    void borrowBook(int bookId){
        borrowedBooks.push_back(bookId);
        cout << name << " borrowed book with ID: " << bookId << endl;
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






int main(){

    return 0;
}
