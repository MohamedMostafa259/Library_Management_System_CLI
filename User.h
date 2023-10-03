#ifndef USER_H // user header guard
#define USER_H

#include <iostream>
using namespace std;

class User { // abstract class that provides a blueprint for creating different types of users in a system
    protected:
        int ID;
        string name;
        static int counter; //the counter value is shared across all User objects, and each new object created increments the counter and gets a unique ID
    public:
        User();
        User(string name_);
        virtual void printInfo() = 0;
        int getID();
        string getName();
        void resetCounter(int counter_);
        void setID(int ID_);
        void setName(string name_);
};

#endif