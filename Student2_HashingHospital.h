
#ifndef STUDENT2_HASHHOSPITAL_H
#define STUDENT2_HASHHOSPITAL_H
#include "Student3_LinkedList.h"

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
class RecipientHashTable
{
private:
    Recipient* table[HASH_SIZE];
    bool occupied[HASH_SIZE];

    int hashFunction(int id)
    {
        return id % HASH_SIZE;
    }

public:
    RecipientHashTable()
    {
        for (int i = 0; i < HASH_SIZE; i++)
        {
            table[i] = NULL;
            occupied[i] = false;
        }
    }

    bool insert(Recipient* r)
    {
        int index = hashFunction(r->getID());

        for (int i = 0; i < HASH_SIZE; i++)
        {
            int pos = (index + i) % HASH_SIZE;

            if (!occupied[pos])
            {
                table[pos] = r;
                occupied[pos] = true;
                return true;
            }

            if (table[pos]->getID() == r->getID())
                return false;
        }

        return false;
    }

    Recipient* search(int id)
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

/* =========================================================
                           HOSPITAL
   ========================================================= */

class Hospital
{
private:
    int id;
    string name;
    string location;
    string password;

public:
    Hospital()
    {
        id = 0;
    }

    Hospital(int id, string name, string location, string password)
    {
        this->id = id;
        this->name = name;
        this->location = location;
        this->password = password;
    }

    int getID() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    string getLocation() const { return location; }
    string getPasswordForFile() const { return password; }

    bool checkPassword(string p)
    {
        return p == password;
    }

    void display()
    {
        cout << "\nHospital ID : " << id;
        cout << "\nName        : " << name;
        cout << "\nLocation    : " << location;
        cout << "\n-------------------------\n";
    }
};

/* =========================================================
                     HOSPITAL ARRAY
   ========================================================= */

const int MAX_HOSPITALS = 50;

class HospitalManager
{
private:
    Hospital hospitals[MAX_HOSPITALS];
    int count;

public:
    HospitalManager()
    {
        count = 0;
    }

    bool add(Hospital h)
    {
        if (count == MAX_HOSPITALS)
            return false;

        if (search(h.getID()) != NULL)
            return false;

        hospitals[count++] = h;
        return true;
    }

    Hospital* search(int id)
    {
        for (int i = 0; i < count; i++)
        {
            if (hospitals[i].getID() == id)
                return &hospitals[i];
        }

        return NULL;
    }

    void display()
    {
        if (count == 0)
        {
            cout << "\nNo hospitals registered.\n";
            return;
        }

        for (int i = 0; i < count; i++)
            hospitals[i].display();
    }

    int size()
    {
        return count;
    }

    Hospital* getAt(int index)
    {
        if (index < 0 || index >= count) return NULL;
        return &hospitals[index];
    }
};


