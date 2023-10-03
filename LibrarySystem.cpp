#include "LibrarySystem.h"

LibrarySystem::LibrarySystem(int max) {
    maxNumOfBooks = max;
    libraryBooks = new Book[max];
    numOfBooks = 0;
}
int LibrarySystem::getNumOfBooks() {
    return numOfBooks;
}
Book* LibrarySystem::getLibraryBooks() {
    return  libraryBooks;
}
void LibrarySystem::addBook(const string &title, const string &author, const string &category) {
    if (numOfBooks == maxNumOfBooks) {
        cout << "There is No place to add another book\n\n";
        return;
    }
    libraryBooks[numOfBooks++] = Book(title, author, category);
}
void LibrarySystem::removeBook(int ID) {
    for (int i{0}; i < numOfBooks; i++) {
        if (ID == libraryBooks[i].getID()) {
            libraryBooks[i].shiftToLeft(libraryBooks, i, maxNumOfBooks);
            numOfBooks--;      
            return;
        }
    }
    cout << "This ID does not exist.\n\n";
}
void LibrarySystem::addAdmin(int &numOfAdmins, Admin admins[]) {
    if (numOfAdmins == 10) {
        cout << "Sorry, you cannot add more the ten admins\n\n";
        return;
    }
    string name, username, password;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    admins[numOfAdmins++] = Admin(name, username, password);
}
void LibrarySystem::addCustomer(int &numOfCustomers, Customer customers[]) {
    if (numOfCustomers == 100) {
        cout << "Sorry, you cannot add more the one hundred customers\n\n";
        return;
    }
    string name;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, name);
    customers[numOfCustomers++] = Customer(name);
}
void LibrarySystem::shiftToLeft(Customer customers[], int start, int size) {
    for (int i{start}; i < size-1; i++) {
        customers[i] = customers[i+1];
    }
    // After shifting to the books array to left, customers[size-1] = customers[size-2]. consequently, the last cell is repeated.
    customers[size-1] = Customer();
}
void LibrarySystem::removeCustomer(int &numOfCustomers, Customer customers[], int ID) {
    for (int i{0}; i < numOfCustomers; i++) {
        if (ID == customers[i].getID()) {
            
            int num{customers[i].getNumOfBorrowedBooks()};
            Book *borrowedBooks = new Book[num];
            for (int j{0}; j < num; j++) {
                borrowedBooks[j] = customers[i].getBorrowedBooks()[j];
            }
            for (int p1{0}; p1 < num; p1++) {
                for (int p2{0}; p2 < numOfBooks; p2++) {
                    if (borrowedBooks[p1].getID() == libraryBooks[p2].getID()) {
                        libraryBooks[p2].setIsBorrowed(false);
                        break;
                    }
                }
            }
            delete[] borrowedBooks;

            shiftToLeft(customers, i, 100);
            numOfCustomers--;     
            return;
        }
    }
    cout << "This ID does not exist.\n\n";
}
void LibrarySystem::displayBooks()
{
    for (int i{0}; i < numOfBooks; i++) {
        cout << libraryBooks[i] << endl;
    }
    cout << endl;
}
Book LibrarySystem::findByID(int ID) {
    for (int i{0}; i < numOfBooks; i++) {
        if (libraryBooks[i].getID() == ID) {
            return libraryBooks[i];
        }
    }
    cout << "This book ID does not exist.\n\n";
    return Book();
}
Book LibrarySystem::findByAuthor(const string &author, bool displayOnly)
{
    bool isExist{false}; // check if there is a book author like the one user entered
    for (int i{0}; i < numOfBooks; i++) {
        if (libraryBooks[i].subStr(libraryBooks[i].getAuthor(), author)) {
            isExist = true;
            cout << "Book " << libraryBooks[i].getID() << " , Author: " << libraryBooks[i].getAuthor() << endl;
        }
    }
    if (!isExist) {
        cout << "This author name you entered does not exist\n\n";
        return Book();
    }
    if (displayOnly) return Book();
    int ID;
    cout << "Enter the ID of the book you want to display all its info. : ";
    cin >> ID;
    return findByID(ID);
}
Book LibrarySystem::findByCategory(const string &category, bool displayOnly) {
    bool isExist{false}; // check if there is a book category like the one user entered
    for (int i{0}; i < numOfBooks; i++) {
        if (libraryBooks[i].subStr(libraryBooks[i].getCategory(), category)) {
            isExist = true;
            cout << "Book " << libraryBooks[i].getID() << " , Category: " << libraryBooks[i].getCategory() << endl;
        }
    }
    if (!isExist) {
        cout << "This Category you entered does not exist\n\n";
        return Book();
    }
    if (displayOnly) return Book();
    int ID;
    cout << "Enter the ID of the book you want to display all its info. : ";
    cin >> ID;
    return findByID(ID);
}
Book LibrarySystem::findByTitle(const string &title) {
    bool isExist{false}; // check if there is a book title like the one user entered
    for (int i{0}; i < numOfBooks; i++) {
        if (libraryBooks[i].subStr(libraryBooks[i].getTitle(), title)) {
            isExist = true;
            cout << "Book " << libraryBooks[i].getID() << " , Title: " << libraryBooks[i].getTitle() << endl;
        }
    }
    if (!isExist) {
        cout << "This title you entered does not exist\n\n";
        return Book();
    }
    int ID;
    cout << "Enter the ID of the book you want to display all its info. : ";
    cin >> ID;
    return findByID(ID);
}
void LibrarySystem::displayBorrowedBooks() {
    for (int i{0}; i < numOfBooks; i++) {
        if (libraryBooks[i].getIsBorrowed()) {
            cout << libraryBooks[i] << endl;
        }
    }
    cout << endl;    
}
void LibrarySystem::displayNonBorrowedBooks() {
    for (int i{0}; i < numOfBooks; i++) {
        if (!libraryBooks[i].getIsBorrowed()) {
            cout << libraryBooks[i];
        }
    }
    cout << endl;
}
void LibrarySystem::saveAdmins(Admin admins[], int numOfAdmins) {
    ofstream outFile("admins.txt");
    if (!outFile) {
        cout << "Error opening file admins.txt for writing\n";
        return;
    }
    for (int i = 0; i < numOfAdmins; i++) {
        outFile << admins[i].getID() << "," << admins[i].getName() << "," << admins[i].getUsername() << "," << admins[i].getPassword() << endl;
    }
    outFile.close();
}
void LibrarySystem::saveBooks() {
    ofstream outFile("books.txt");
    if (!outFile) {
        cout << "Error opening file books.txt for writing\n";
        return;
    }
    for (int i = 0; i < numOfBooks; i++) {
        outFile << libraryBooks[i].getID() << "," << libraryBooks[i].getTitle() << "," << libraryBooks[i].getAuthor() << "," << libraryBooks[i].getCategory() << endl;
    }
    outFile.close();
}
void LibrarySystem::loadAdmins(Admin admins[], int &numOfAdmins) {
    ifstream inFile("admins.txt");
    if (!inFile) {
        cout << "No admins file found. Skipping loading admins.\n";
        return;
    }
    string line;
    while (getline(inFile, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);
        size_t pos4 = line.find(",", pos3 + 1);

        int ID = stoi(line.substr(0, pos1));
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string username = line.substr(pos2 + 1, pos3 - pos2 - 1);
        string password = line.substr(pos3 + 1, pos4 - pos3 - 1);

        admins[numOfAdmins].setID(ID);
        admins[numOfAdmins].setName(name);
        admins[numOfAdmins].setUsername(username);
        admins[numOfAdmins].setPassword(password);
        numOfAdmins++;
    }
    int highestID{admins[numOfAdmins-1].getID()};
    admins[numOfAdmins-1].resetCounter(highestID); // to make the counter, which is responsible for customers and admins IDs, start from the highest admin ID
    inFile.close();
}
void LibrarySystem::loadBooks() {
    ifstream inFile("books.txt");
    if (!inFile) {
        cout << "No books file found. Skipping loading books.\n";
        return;
    }
    string line;
    while (getline(inFile, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);
        size_t pos4 = line.find(",", pos3 + 1);

        int ID = stoi(line.substr(0, pos1));
        string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string author = line.substr(pos2 + 1, pos3 - pos2 - 1);
        string category = line.substr(pos3 + 1, pos4 - pos3 - 1);

        libraryBooks[numOfBooks].setTitle(title);
        libraryBooks[numOfBooks].setAuthor(author);
        libraryBooks[numOfBooks].setCategory(category);
        libraryBooks[numOfBooks].setID(ID);
        libraryBooks[numOfBooks].setIsBorrowed(false);
        numOfBooks++;
    }
    int highestID{libraryBooks[numOfBooks-1].getID()};
    libraryBooks[numOfBooks-1].resetCounter(highestID); // to make the counter, which is responsible for books IDs, start from the highest book ID 
    inFile.close();
}
LibrarySystem::~LibrarySystem() {
    delete[] libraryBooks;
}