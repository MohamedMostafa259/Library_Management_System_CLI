#include "Book.h"

int Book::counter = 100; // the 1st book ID in our library will be 101
Book::Book() {
    ID = -1;
    title = author = category = "";
    isBorrowed = false;
}
Book::Book(const string &title_, const string &author_, const string &category_) {
    ID = ++counter;
    title = title_;
    author = author_;
    category = category_;
    isBorrowed = false;
}
string Book::getAuthor() {
    return author;
}
string Book::getTitle() {
    return title;
}
string Book::getCategory() {
    return category;
}
int Book::getID() {
    return ID;
}
bool Book::getIsBorrowed() {
    return isBorrowed;
}
void Book::resetCounter(int counter_) {
    counter = counter_;   
}
void Book::setID(int ID_) {
    ID = ID_;
}
void Book::setTitle(string title_) {
    title = title_;
}
void Book::setAuthor(string author_) {
    author = author_;
}
void Book::setCategory(string category_) {
    category = category_;
}
void Book::setIsBorrowed(bool is_borrowed)
{
    isBorrowed = is_borrowed;
}
void Book::printInfo() {
    cout << "Book " << ID << " Info. :" << endl
        << "Title: " << title << endl
        << "Author: " << author << endl
        << "Category: " << category << endl;
        if (isBorrowed) cout << "This Book is not borrowable\n" << endl;
        else            cout << "This Book is borrowable\n" << endl;
}

void Book::shiftToLeft(Book* books, int start, int size) {
    for (int i{start}; i < size-1; i++) {
        books[i] = books[i+1];
    }
    // After shifting to the books array to left, books[size-1] = books[size-2]. consequently, the last cell is repeated.
    books[size-1] = Book();
}
bool Book::subStr(const string &str, const string &sub) {
    if (str.size() < sub.size()) return false;
    
    //bool isSubStr{false};

    for (int i{0}; i <= str.size()-sub.size(); i++) {
        bool isSubStr{true};
        for (int j{i}; j < sub.size()+i; j++) {
            if ('A' <= sub[j-i] && sub[j-i] <= 'Z') {// capital letter
                if (str[j] != sub[j-i] && str[j] != (char)(sub[j-i] + ('a'-'A'))) {
                    isSubStr = false;
                    break;
                }
            }
            else if ('a' <= sub[j-i] && sub[j-i] <= 'z') {// small letter
                if (str[j] != sub[j-i] && str[j] != (char)(sub[j-i] - ('a'-'A'))) {
                    isSubStr = false;
                    break;
                }
            }
            else {// spcial character
                if (str[j] != sub[j-i]) {
                    isSubStr = false;
                    break;
                }
            }
        }
        if (isSubStr) return true;
    }
    return false;
}
ostream &operator<<(ostream &os, Book book) {
    os << "Book " << book.getID() << " :" << endl
        << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() 
        << ", Category: " << book.getCategory() << endl;
    return os;     
}
