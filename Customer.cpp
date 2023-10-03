#include "Customer.h"

Customer::Customer() {
    //User::User(); the default constructor of the User base class is automatically called before the constructor of the derived class Customer is executed.
    numOfBorrowedBooks = 0;
}
Customer::Customer(string name_) : User(name_) {
    numOfBorrowedBooks = 0;
}
void Customer::borrowBook(Book* libBooks, int numOfBooks, int ID) {
    if (numOfBorrowedBooks == 5) {
        cout << "Sorry, you cannot borrow more than five books!\n\n";
        return;
    }
    for (int i{0}; i < numOfBooks; i++) {
        if (libBooks[i].getID() == ID) {
            libBooks[i].setIsBorrowed(true);
            books[numOfBorrowedBooks++] = libBooks[i];
            return;
        }
    }
    cout << "This book ID does not exist.\n\n";
}
void Customer::returnBook(Book* libBooks, int numOfBooks, int ID) {
    if (numOfBorrowedBooks == 0) {
        cout << "You don't have any books to return!\n\n";
        return;
    }
    for (int i{0}; i < numOfBorrowedBooks; i++) {
        if (books[i].getID() == ID) {
            books[i].shiftToLeft(books, i, 5);  
            numOfBorrowedBooks--;

            for (int j{0}; j < numOfBooks; j++) {
                if (libBooks[i].getID() == ID) {
                    libBooks[i].setIsBorrowed(false);  
                    break;
                }
            }
            return;
        }
    }
    cout << "This ID does not exist in books you borrowed.\n\n";
}
int Customer::getNumOfBorrowedBooks() {
    return numOfBorrowedBooks;
}
Book* Customer::getBorrowedBooks() {
    Book *borrowedBooks = new Book[numOfBorrowedBooks];
    for (int i{0}; i < numOfBorrowedBooks; i++) {
        borrowedBooks[i] = books[i];
    }
    return borrowedBooks;
}
void Customer::printInfo() {
    cout << "Customer " << getID() << " Info. :\n"
        << "Name: " << getName() << endl
        << "Number of Borrowed Books: " << numOfBorrowedBooks << endl
        << "Borrowed Books: ";
        for (int i{0}; i < numOfBorrowedBooks; i++) {
            cout << "Book " << books[i].getID() << " :" << endl
                << "Title: " << books[i].getTitle() << ", Author: " << books[i].getAuthor() << ", Category: " << books[i].getCategory() << endl;  
        }
        cout << endl;
}

ostream &operator<<(ostream &os, Customer customer) {
    os << "Customer " << customer.ID << " : " << customer.name << endl;
    return os;
}
