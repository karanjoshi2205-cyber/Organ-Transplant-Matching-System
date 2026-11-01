#ifndef STUDENT1_DONORRECIPIENT_H
#define STUDENT1_DONORRECIPIENT_H
#include <iostream>
#include <string>
#include <limits>
using namespace std;

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

class Person
{
protected:
    int id;
    string name;
    char gender;
    int age;
    string phone;
    string address;

public:
    Person()
    {
        id = 0;
        gender = 'M';
        age = 0;
    }

    Person(int id, string name, char gender, int age,
           string phone, string address)
    {
        this->id = id;
        this->name = name;
        this->gender = gender;
        this->age = age;
        this->phone = phone;
        this->address = address;
    }

    int getID() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }

    char getGender() const { return gender; }
    string getPhone() const { return phone; }
    string getAddress() const { return address; }

    virtual void display() const = 0;

    virtual ~Person() {}
};
