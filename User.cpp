#include "User.h"

int User::counter = 100; // static is defined outside the class, and we will initialize it to 100.
User::User() {
    ID = -1;
    name = "";
}
User::User(string name_) {
    ID = ++counter;
    name = name_;
}
int User::getID() {
    return ID;
}
string User::getName() {
    return name;
}
void User::resetCounter(int counter_) {
    counter = counter_;
}
void User::setID(int ID_) {
    ID = ID_;
}
void User::setName(string name_) {
    name = name_;
}