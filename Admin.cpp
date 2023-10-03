#include "Admin.h"

Admin::Admin() {
    username = "";
    password = "";
    //User::User(); the default constructor of the User base class is automatically called before the constructor of the derived class Admin is executed.
}
Admin::Admin(string name_, string username_, string password_) : User(name_)
{
    username = username_;
    password = password_;
}

void Admin::printInfo() {
    cout << "Admin " << ID << " : " << name << endl;
}

string Admin::getUsername() {
    return username;
}

string Admin::getPassword() {
    return password;
}

void Admin::setUsername(const string &username_) {
    username = username_;
}

void Admin::setPassword(const string &password_) {
    password = password_;
}

ostream &operator<<(ostream &os, Admin admin) {
    os << "Admin " << admin.ID << " : " << admin.name << endl;
    return os;    
}
