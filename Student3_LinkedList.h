// STUDENT 3: LINKED LISTS AND LINKED-LIST OPERATIONS
#ifndef STUDENT3_LINKEDLIST_H
#define STUDENT3_LINKEDLIST_H
#include "Student1_DonorRecipient.h"

/* =========================================================
                     DONOR LINKED LIST
   ========================================================= */

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

/* =========================================================
                    RECIPIENT LINKED LIST
   ========================================================= */

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


// Bubble sort donor records by age without changing the list links.
inline void sortDonorsByAge(DonorList& list)
{
    if (list.getHead() == NULL || list.getHead()->next == NULL)
    {
        cout << "Not enough donors to sort.\n";
        return;
    }
    bool swapped;
    do
    {
        swapped = false;
        DonorNode* current = list.getHead();
        while (current != NULL && current->next != NULL)
        {
            if (current->data.getAge() > current->next->data.getAge())
            {
                Donor temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    cout << "Donors sorted by age (ascending).\n";
    list.display();
}

#endif
