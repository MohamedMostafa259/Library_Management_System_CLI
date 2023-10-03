#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Book.h"
#include <iostream>
using namespace std;

class Customer: public User {
    private:
        Book books[5];
        int numOfBorrowedBooks;
    public:
        Customer();
        Customer(string name_);
        void borrowBook(Book* libBooks, int numOfBooks, int ID);
        void returnBook(Book* libBooks, int numOfBooks, int ID);
        int getNumOfBorrowedBooks();
        Book* getBorrowedBooks();
        void printInfo() override;
        friend ostream &operator<<(ostream & os, Customer customer);
};

#endif