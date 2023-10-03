#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include "User.h"
using namespace std;

class Admin : public User {
    private:
        string username, password;
    public:
        Admin();
        Admin(string name_, string username_, string password_);
        void printInfo() override;
        string getUsername();
        string getPassword();
        void setUsername(const string &username_);
        void setPassword(const string &password_);
        friend ostream &operator<<(ostream & os, Admin admin);
};

#endif