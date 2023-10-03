// VS Code -> Write this on console to link these files together : g++ -o Main.exe Main.cpp User.cpp Admin.cpp Customer.cpp Book.cpp LibrarySystem.cpp
// Then Write to run the code : ./Main.exe

#include "LibrarySystem.h"

int menu();

int main() {
    cout << "                                  Loading, please wait...\n\n";
    cout << "--------------------------------Welcome to CODE HORSES Company--------------------------------\n";
    cout << "----------------------------------Library Management System----------------------------------\n";
    
    Admin admins[10]; // we will suppose the maximum number of admins is 10, and the 1st admin we know their name, username & password
    admins[0] = Admin("mohamed", "mohamed", "123");
    Customer customers[100]; // // we will suppose the maximum number of customers is 100
    int numOfAdmins{1}, numOfCustomers{0};
    
    string username, password;
    int attempts{3}; // the maximum number of allowed attempts to enter username & password is 3
    bool login{false};
    
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    while (attempts--) {
        for (int i{0}; i < 10; i++) {
            if (admins[i].getName() == "") // Empty cell
                break;
            else if (admins[i].getUsername() == username && admins[i].getPassword() == password) {
                login = true;
                break;
            }
        }
        if (login || attempts == 0) break;
        else {
            cout << "Invalid username OR password! .. Try again(" << attempts << " remaining attempts)\n";
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);
        }
    }
    if (!login) {
        cout << "You don't have more attempts! .. Try to login tomorrow!";
        return 0; // exit
    }

    int maxNumOfBooks;
    cout << "What is the maximum number of books you want to put in your library?  ";
    cin >> maxNumOfBooks;
    LibrarySystem librarySystem(maxNumOfBooks);

    char loadOption;
    cout << "Do you want to load existing admins and books from files? (Y/N): ";
    cin >> loadOption;

    if (loadOption == 'Y' || loadOption == 'y') {
        librarySystem.loadAdmins(admins, numOfAdmins);
        librarySystem.loadBooks();
    }

    while (true) {
        int choice{menu()};

        if (choice == 1) {
            int adminORcustomer;
            cout << "1. Admin\n2. Customer\nEnter choice [1-2]: ";
            cin >> adminORcustomer;
            if (adminORcustomer == 1)
                librarySystem.addAdmin(numOfAdmins, admins);
            else if (adminORcustomer == 2)
                librarySystem.addCustomer(numOfCustomers, customers);
            else {
                cout << "Wrong choice!!\n\n";
            }
        }   
        else if (choice == 2) {
            cout << "Admins:\n";
            for (int i{0}; i < numOfAdmins; i++)
               cout << admins[i];
            if (numOfCustomers) {
                cout << "\nCustomers:\n";
                for (int i{0}; i < numOfCustomers; i++)
                    cout << customers[i];
            }
        }
        else if (choice == 3) {
            if (numOfCustomers == 0) {
                cout << "No customers in the library to remove\n\n";
                continue;
            }
            cout << "Customers:\n";
            for (int i{0}; i < numOfCustomers; i++)
                cout << customers[i];
            
            int id;
            cout << "Choose a customer ID: ";
            cin >> id;
            librarySystem.removeCustomer(numOfCustomers, customers, id);
        }
        else if (choice == 4) {
            if (librarySystem.getNumOfBooks() == maxNumOfBooks) {
                cout << "You cannot add more than " << maxNumOfBooks << " books\n\n";
                continue;
            }
            string title, author, category;
            cin.ignore(); // to discard the remaining newline character (\n) and ensure that the getline() function will not receive an empty line as input
            cout << "Enter title: ";
            getline(cin, title);
            cout << "Author: ";
            getline(cin, author);
            cout << "Category: ";
            getline(cin, category);
            
            librarySystem.addBook(title, author, category);
        }
        else if (choice == 5) {
            if (librarySystem.getNumOfBooks() == 0) {
                cout << "No books in the library to remove\n\n";
                continue;
            }
            librarySystem.displayBooks();
            int id;
            cout << "Enter a book ID:  ";
            cin >> id;
            librarySystem.removeBook(id);
        }
        else if (choice == 6) {
            if (librarySystem.getNumOfBooks() == 0) {
                cout << "No non-borrowed books in the library to borrow!!\n\n";
                continue;
            }
            cout << "Customers:\n";
            for (int i{0}; i < numOfCustomers; i++)
                cout << customers[i];
            
            int id;
            cout << "Choose a customer ID: ";
            cin >> id;  
            bool isExist{false};
            
            for (int i{0}; i < numOfCustomers; i++) {
                if (customers[i].getID() == id) {
                    librarySystem.displayNonBorrowedBooks();
                    int id_book;
                    cout << "Enter a book ID:  ";
                    cin >> id_book;
                    customers[i].borrowBook(librarySystem.getLibraryBooks(), librarySystem.getNumOfBooks(), id_book);
                    isExist = true;
                    break;
                }
            }
            if (!isExist) {
                cout << "There is no such customer id in our system\n\n";
                continue;
            }
        }
        else if (choice == 7) {
            cout << "Customers who have borrowed books:\n";
            for (int i{0}; i < numOfCustomers; i++) {
                if (customers[i].getNumOfBorrowedBooks() > 0) {
                    cout << customers[i];
                }
            }
            
            int id;
            cout << "Choose a customer ID: ";
            cin >> id;  
            bool isExist{false};
            
            for (int i{0}; i < numOfCustomers; i++) {
                if (customers[i].getID() == id && customers[i].getNumOfBorrowedBooks() > 0) {
                    int numOfBorrowedBooks{customers[i].getNumOfBorrowedBooks()};
                    for (int j{0}; j < numOfBorrowedBooks; j++) {
                        cout << customers[i].getBorrowedBooks()[j];
                    }
                    int id_book;
                    cout << "Enter a book ID:  ";
                    cin >> id_book;
                    customers[i].returnBook(librarySystem.getLibraryBooks(), librarySystem.getNumOfBooks(), id_book);      
                    isExist = true;
                    break;
                }
            }
            if (!isExist) {
                cout << "There is no such customer id in our previous list\n\n";
                continue;
            }
        }
        else if (choice == 8) {
            cout << "Borrowed Books:\n";
            librarySystem.displayBorrowedBooks();
            cout << "Non-borrowed Books:\n";
            librarySystem.displayNonBorrowedBooks();
        }
        else if (choice == 9) {
            string title;
            cin.ignore();
            cout << "Enter a book title: ";
            getline(cin, title);
            
            Book book{librarySystem.findByTitle(title)};
            if (book.getID() == -1) {continue;} // the title or the id is not found
            cout << book << endl;
        }
        else if (choice == 10 || choice == 12) {
            string category;
            cin.ignore();
            cout << "Enter a book category (Fiction, Romance, Children, Non-fiction, Horror & History): ";
            getline(cin, category);
            
            if (choice == 10) {
                Book book{librarySystem.findByCategory(category, false)};
                if (book.getID() == -1) {continue;} // the category or the id is not found
                cout << book << endl;
            }
            else { // choice = 12
                Book book{librarySystem.findByCategory(category, true)};
            }
        }
        else if (choice == 11 || choice == 13) {
            string author;
            cin.ignore();
            cout << "Enter an author name: ";
            getline(cin, author);
            
            if (choice == 11) {
                Book book{librarySystem.findByAuthor(author, false)};
                if (book.getID() == -1) {continue;} // the author or the id is not found
                cout << book << endl;
            } 
            else { // choice = 13
                Book book{librarySystem.findByAuthor(author, true)};
            }
        }
        else if (choice == 14) {
            cout << "Thank You For Using Our Application!";
            librarySystem.saveAdmins(admins, numOfAdmins);
            librarySystem.saveBooks();
            librarySystem.~LibrarySystem();
            break;
        }
    }
    return 0;
}

int menu() {
    int choice{-1};
    while (choice == -1) {
        cout << "1- Create a new user" << endl
            << "2- Display existing users by id and name" << endl
            << "3- Remove a customer by ID" << endl
            << "4- Add a book to the library" << endl
            << "5- Remove a book from the library by ID" << endl
            << "6- Allow a customer to borrow a book by choosing customer ID and book ID" << endl
            << "7- Allow a customer to return a book by choosing customer ID and book ID" << endl
            << "8- Display all books classified as borrowed and non-borrowed" << endl
            << "9- Display a book info by title" << endl
            << "10- Display a book info by category" << endl
            << "11- Display a book info by author" << endl
            << "12- Display books of a certain category (display IDs and category only)" << endl
            << "13- Display books of a certain author (display IDs and author only)" << endl
            << "14- Exit" << endl << endl
            << "Enter choice [1 - 14]:  ";
        cin >> choice;
        if (!(1 <= choice && choice <= 14)) {
            cout << "Invalid Choice! .. Try again:\n";
            choice = -1;
        }
    }
    return choice;
}