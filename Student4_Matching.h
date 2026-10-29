// STUDENT 4: MATCHING, REQUEST QUEUE, PRIORITY QUEUE AND SHARED HELPERS
#ifndef STUDENT4_MATCHING_H
#define STUDENT4_MATCHING_H
#include <iostream>
#include <string>
#include "Student2_HashingHospital.h"
#include "Student3_LinkedList.h"
using namespace std;

inline string organType()
{
    int c;
    cout << "\nOrgan Type:\n1. Kidney\n2. Liver\n3. Heart\n4. Lung\n5. Pancreas\nChoice: ";
    cin >> c; clearInput();
    if (c == 1) return "Kidney";
    if (c == 2) return "Liver";
    if (c == 3) return "Heart";
    if (c == 4) return "Lung";
    if (c == 5) return "Pancreas";
    cout << "Invalid choice; Kidney selected by default.\n";
    return "Kidney";
}

inline string organSize()
{
    int c;
    cout << "Organ Size:\n1. Small\n2. Medium\n3. Large\nChoice: ";
    cin >> c; clearInput();
    if (c == 1) return "Small";
    if (c == 3) return "Large";
    return "Medium";
}

inline int priority()
{
    int p;
    cout << "Priority (1-Emergency, 2-High, 3-Normal): ";
    cin >> p; clearInput();
    if (p < 1 || p > 3) { cout << "Invalid priority; Normal selected.\n"; return 3; }
    return p;
}

inline string bloodGroup()
{
    int c;
    cout << "Blood Group:\n1. O-\n2. O+\n3. A-\n4. A+\n5. B-\n6. B+\n7. AB-\n8. AB+\nChoice: ";
    cin >> c; clearInput();
    const string groups[] = {"O-", "O+", "A-", "A+", "B-", "B+", "AB-", "AB+"};
    if (c < 1 || c > 8) { cout << "Invalid choice; O- selected by default.\n"; return "O-"; }
    return groups[c - 1];
}

inline bool bloodCompatible(const string& donor, const string& recipient)
{
    if (donor == "O-") return true;
    if (donor == "O+") return recipient == "O+" || recipient == "A+" || recipient == "B+" || recipient == "AB+";
    if (donor == "A-") return recipient == "A-" || recipient == "A+" || recipient == "AB-" || recipient == "AB+";
    if (donor == "A+") return recipient == "A+" || recipient == "AB+";
    if (donor == "B-") return recipient == "B-" || recipient == "B+" || recipient == "AB-" || recipient == "AB+";
    if (donor == "B+") return recipient == "B+" || recipient == "AB+";
    if (donor == "AB-") return recipient == "AB-" || recipient == "AB+";
    return donor == "AB+" && recipient == "AB+";
}

inline bool sizeCompatible(const string& donor, const string& recipient)
{
    return donor == recipient || donor == "Large" || recipient == "Medium";
}

inline bool eligible(const Donor& donor, const Recipient& recipient)
{
    return donor.isAvailable() && donor.getOrgan() == recipient.getOrgan()
        && bloodCompatible(donor.getBlood(), recipient.getBlood())
        && sizeCompatible(donor.getSize(), recipient.getSize());
}

class Request
{
private:
    int id, donorID, recipientID, fromHospital, toHospital;
    string status;
public:
    Request() : id(0), donorID(0), recipientID(0), fromHospital(0), toHospital(0), status("PENDING") {}
    Request(int requestID, int dID, int rID, int fromID, int toID)
        : id(requestID), donorID(dID), recipientID(rID), fromHospital(fromID), toHospital(toID), status("PENDING") {}
    int getID() const { return id; }
    int getDonorID() const { return donorID; }
    int getRecipientID() const { return recipientID; }
    int getFromHospital() const { return fromHospital; }
    int getToHospital() const { return toHospital; }
    void setStatus(const string& value) { status = value; }
    string getStatus() const { return status; }
    void display() const
    {
        cout << "Request ID       : " << id << "\nDonor ID         : " << donorID
             << "\nRecipient ID     : " << recipientID << "\nRequesting Hosp. : " << fromHospital
             << "\nDonor Hospital   : " << toHospital << "\nStatus           : " << status << "\n";
    }
};

class RequestQueue
{
private:
    Request items[200];
    int front, rear, count;
public:
    RequestQueue() : front(0), rear(0), count(0) {}
    bool empty() const { return count == 0; }
    bool push(const Request& request)
    {
        if (count == 200) { cout << "Request queue is full.\n"; return false; }
        items[rear] = request; rear = (rear + 1) % 200; count++; return true;
    }
    Request pop()
    {
        if (empty()) return Request();
        Request result = items[front]; front = (front + 1) % 200; count--; return result;
    }
};

struct PriorityItem
{
    int recipientID;
    int priority;
};

class PriorityQueue
{
private:
    PriorityItem items[200];
    int count;
public:
    PriorityQueue() : count(0) {}
    bool empty() const { return count == 0; }
    void push(int id, int priority)
    {
        if (count == 200) { cout << "Priority queue is full.\n"; return; }
        int i = count++;
        while (i > 0 && items[i - 1].priority > priority)
        { items[i] = items[i - 1]; i--; }
        items[i].recipientID = id; items[i].priority = priority;
    }
    PriorityItem pop()
    {
        if (empty()) return PriorityItem{0, 0};
        PriorityItem result = items[0];
        for (int i = 1; i < count; i++) items[i - 1] = items[i];
        count--; return result;
    }
};

inline void showStatistics(HospitalManager& hospitals, DonorList& donors, RecipientList& recipients, int requestCount)
{
    cout << "\n========== SYSTEM STATISTICS ==========\n";
    cout << "Registered hospitals : " << hospitals.size() << "\n";
    cout << "Donor records        : " << donors.size() << "\n";
    cout << "Recipient records    : " << recipients.size() << "\n";
    cout << "Requests created     : " << requestCount << "\n";
}

#endif
