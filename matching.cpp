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




class DonorNode
{
public:
    Donor data;
    DonorNode* next;

    DonorNode(Donor d)
    {
        data = d;
        next = NULL;
    }
};

class DonorList
{
private:
    DonorNode* head;

public:
    DonorList()
    {
        head = NULL;
    }

    void insert(Donor d)
    {
        DonorNode* newNode = new DonorNode(d);

        if (head == NULL)
        {
            head = newNode;
            return;
        }

        DonorNode* temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    DonorNode* search(int id)
    {
        DonorNode* temp = head;

        while (temp != NULL)
        {
            if (temp->data.getID() == id)
                return temp;

            temp = temp->next;
        }

        return NULL;
    }

    bool remove(int id)
    {
        if (head == NULL)
            return false;

        if (head->data.getID() == id)
        {
            DonorNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        DonorNode* temp = head;

        while (temp->next != NULL)
        {
            if (temp->next->data.getID() == id)
            {
                DonorNode* del = temp->next;
                temp->next = del->next;
                delete del;
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

    int size()
    {
        int count = 0;
        DonorNode* temp = head;

        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }

        return count;
    }

    void display()
    {
        DonorNode* temp = head;

        if (temp == NULL)
        {
            cout << "\nNo donors available.\n";
            return;
        }

        while (temp != NULL)
        {
            temp->data.display();
            temp = temp->next;
        }
    }

    DonorNode* getHead()
    {
        return head;
    }
};

class RecipientNode
{
public:
    Recipient data;
    RecipientNode* next;

    RecipientNode(Recipient r)
    {
        data = r;
        next = NULL;
    }
};

class RecipientList
{
private:
    RecipientNode* head;

public:
    RecipientList()
    {
        head = NULL;
    }

    void insert(Recipient r)
    {
        RecipientNode* newNode = new RecipientNode(r);

        if (head == NULL)
        {
            head = newNode;
            return;
        }

        RecipientNode* temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    RecipientNode* search(int id)
    {
        RecipientNode* temp = head;

        while (temp != NULL)
        {
            if (temp->data.getID() == id)
                return temp;

            temp = temp->next;
        }

        return NULL;
    }

    bool remove(int id)
    {
        if (head == NULL)
            return false;

        if (head->data.getID() == id)
        {
            RecipientNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        RecipientNode* temp = head;

        while (temp->next != NULL)
        {
            if (temp->next->data.getID() == id)
            {
                RecipientNode* del = temp->next;
                temp->next = del->next;
                delete del;
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

    int size()
    {
        int count = 0;
        RecipientNode* temp = head;

        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }

        return count;
    }

    void display()
    {
        RecipientNode* temp = head;

        if (temp == NULL)
        {
            cout << "\nNo recipients available.\n";
            return;
        }

        while (temp != NULL)
        {
            temp->data.display();
            temp = temp->next;
        }
    }

    RecipientNode* getHead()
    {
        return head;
    }
};

/* =========================================================
                         HASH TABLE
   Custom HashMap: ID -> Donor/Recipient
   ========================================================= */

const int HASH_SIZE = 101;

class DonorHashTable
{
private:
    Donor* table[HASH_SIZE];
    bool occupied[HASH_SIZE];

    int hashFunction(int id)
    {
        return id % HASH_SIZE;
    }

public:
    DonorHashTable()
    {
        for (int i = 0; i < HASH_SIZE; i++)
        {
            table[i] = NULL;
            occupied[i] = false;
        }
    }

    bool insert(Donor* d)
    {
        int index = hashFunction(d->getID());

        for (int i = 0; i < HASH_SIZE; i++)
        {
            int pos = (index + i) % HASH_SIZE;

            if (!occupied[pos])
            {
                table[pos] = d;
                occupied[pos] = true;
                return true;
            }

            if (table[pos]->getID() == d->getID())
                return false;
        }

        return false;
    }

    Donor* search(int id)
    {
        int index = hashFunction(id);

        for (int i = 0; i < HASH_SIZE; i++)
        {
            int pos = (index + i) % HASH_SIZE;
            
            if (!occupied[pos])
                return NULL;

            if (table[pos]->getID() == id)
                return table[pos];
        }

        return NULL;
    }

    bool remove(int id)
    {
        int index = hashFunction(id);

        for (int i = 0; i < HASH_SIZE; i++)
        {
            int pos = (index + i) % HASH_SIZE;

            if (!occupied[pos])
                return false;

            if (table[pos]->getID() == id)
            {
                table[pos] = NULL;
                occupied[pos] = false;
                return true;
            }
        }
        
        return false;
    }
};
