
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
