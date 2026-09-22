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
