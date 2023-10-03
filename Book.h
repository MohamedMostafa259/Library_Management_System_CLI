#ifndef BOOK_H
#define BOOK_H

#include <iostream>
using namespace std;

class Book {
    private:
        int ID;
        static int counter;
        string title, author, category;
        bool isBorrowed;
    public:
        Book();
        Book(const string &title_, const string &author_, const string &category_);
        int getID();
        string getTitle();
        string getAuthor();
        string getCategory();
        bool getIsBorrowed();
        void resetCounter(int counter_);
        void setID(int ID_);
        void setTitle(string title_);
        void setAuthor(string author_);
        void setCategory(string category_);
        void setIsBorrowed(bool);
        void printInfo();
        void shiftToLeft(Book* books, int start, int size);
        bool subStr(const string &str, const string &sub); // This function is case in-sensitive
        friend ostream &operator<<(ostream & os, Book book);
};

#endif