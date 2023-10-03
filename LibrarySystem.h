#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <iostream>
#include <string> // to access getline() function
#include <fstream>
#include "Book.h"
#include "Customer.h"
#include "Admin.h"
using namespace std;

class LibrarySystem {
    private:
        Book* libraryBooks;
        int maxNumOfBooks;
        int numOfBooks;
    public:
        LibrarySystem(int max = 0);
        int getNumOfBooks();
        Book* getLibraryBooks();
        void addBook(const string &title, const string &author, const string &category);
        void removeBook(int ID);
        void addAdmin(int &numOfAdmins, Admin admins[]);
        void addCustomer(int &numOfCustomers, Customer customers[]);
        void shiftToLeft(Customer customers[], int start, int size); // we use it when we remove a customer
        void removeCustomer(int &numOfCustomers, Customer customers[], int ID);
        void displayBooks();
        Book findByID(int ID);
        Book findByAuthor(const string &author, bool displayOnly); // displayOnly = true ->> Program will display books of a certain category(display IDs and category only) 
        Book findByCategory(const string &category, bool displayOnly); // displayOnly = false ->> Program will display books of a certain category
                                                                    // and ask the user to enter a specific book to display all its info. 
        Book findByTitle(const string &title);
        void displayBorrowedBooks();
        void displayNonBorrowedBooks();
        void saveAdmins(Admin admins[], int numOfAdmins);
        void saveBooks();
        void loadAdmins(Admin admins[], int& numOfAdmins);
        void loadBooks();
        ~LibrarySystem();
};

#endif