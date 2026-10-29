// STUDENT 1: PERSON, DONOR AND RECIPIENT DATA CLASSES
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

class Donor : public Person
{
private:
    string organ;
    string size;
    string blood;
    bool available;

public:
    Donor()
    {
        available = true;
    }

    Donor(int id, string name, char gender, int age,
          string phone, string address,
          string organ, string size, string blood)
        : Person(id, name, gender, age, phone, address)
    {
        this->organ = organ;
        this->size = size;
        this->blood = blood;
        available = true;
    }

    string getOrgan() const
    {
        return organ;
    }

    string getSize() const
    {
        return size;
    }

    string getBlood() const
    {
        return blood;
    }

    bool isAvailable() const
    {
        return available;
    }

    void setAvailable(bool value)
    {
        available = value;
    }

    void update()
    {
        cout << "\nNew Name: ";
        getline(cin, name);

        cout << "New Phone: ";
        getline(cin, phone);

        cout << "New Address: ";
        getline(cin, address);

        cout << "New Age: ";
        cin >> age;
        clearInput();

        cout << "Donor updated.\n";
    }

    void display() const override
    {
        cout << "\n--------------------------------\n";
        cout << "Donor ID     : " << id << '\n';
        cout << "Name         : " << name << '\n';
        cout << "Gender       : " << gender << '\n';
        cout << "Age          : " << age << '\n';
        cout << "Phone        : " << phone << '\n';
        cout << "Address      : " << address << '\n';
        cout << "Organ        : " << organ << '\n';
        cout << "Organ Size   : " << size << '\n';
        cout << "Blood Group  : " << blood << '\n';
        cout << "Status       : "
             << (available ? "Available" : "Reserved") << '\n';
        cout << "--------------------------------\n";
    }
};

class Recipient : public Person
{
private:
    string organ;
    string size;
    string blood;
    int priority;

public:
    Recipient()
    {
        priority = 3;
    }

    Recipient(int id, string name, char gender, int age,
              string phone, string address,
              string organ, string size, string blood,
              int priority)
        : Person(id, name, gender, age, phone, address)
    {
        this->organ = organ;
        this->size = size;
        this->blood = blood;
        this->priority = priority;
    }

    string getOrgan() const
    {
        return organ;
    }

    string getSize() const
    {
        return size;
    }

    string getBlood() const
    {
        return blood;
    }

    int getPriority() const
    {
        return priority;
    }

    void update()
    {
        cout << "\nNew Name: ";
        getline(cin, name);

        cout << "New Phone: ";
        getline(cin, phone);

        cout << "New Address: ";
        getline(cin, address);

        cout << "New Age: ";
        cin >> age;

        cout << "Priority (1-Emergency, 2-High, 3-Normal): ";
        cin >> priority;
        clearInput();

        if (priority < 1 || priority > 3)
            priority = 3;

        cout << "Recipient updated.\n";
    }

    void display() const override
    {
        cout << "\n--------------------------------\n";
        cout << "Recipient ID  : " << id << '\n';
        cout << "Name          : " << name << '\n';
        cout << "Gender        : " << gender << '\n';
        cout << "Age           : " << age << '\n';
        cout << "Phone         : " << phone << '\n';
        cout << "Address       : " << address << '\n';
        cout << "Required Organ: " << organ << '\n';
        cout << "Organ Size    : " << size << '\n';
        cout << "Blood Group   : " << blood << '\n';
        cout << "Priority      : ";

        if (priority == 1)
            cout << "Emergency";
        else if (priority == 2)
            cout << "High";
        else
            cout << "Normal";

        cout << "\n--------------------------------\n";
    }
};


#endif
