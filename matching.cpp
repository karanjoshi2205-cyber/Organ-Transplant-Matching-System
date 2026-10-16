#include <iostream>
#include <string>
#include <limits>
using namespace std;
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
class Person {
protected:
    int id;
    string name;
    char gender;
    int age;
    string phone;
    string address;
public:
    Person() {
        id = 0;
        gender = 'M';
        age = 0;
    }
    Person(int id, string name, char gender, int age, string phone, string address) {
        this->id = id;
        this->name = name;
        this->gender = gender;
        this->age = age;
        this->phone = phone;
        this->address = address;
    }
    int getID() const {
        return id;
    }
    string getName() const {
        return name;
    }
    int getAge() const {
        return age;
    }
    virtual void display() const = 0;
    virtual ~Person() {
    }
}
;
class Donor : public Person {
private:
    string organ;
    string size;
    string blood;
    bool available;
public:
    Donor() {
        available = true;
    }
    Donor(int id, string name, char gender, int age, string phone, string address, string organ, string size, string blood) : Person(id, name, gender, age, phone, address) {
        this->organ = organ;
        this->size = size;
        this->blood = blood;
        available = true;
    }
    string getOrgan() const {
        return organ;
    }
    string getSize() const {
        return size;
    }
    string getBlood() const {
        return blood;
    }
    bool isAvailable() const {
        return available;
    }
    void setAvailable(bool value) {
        available = value;
    }
    void update() {
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
    void display() const override {
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
        cout << "Status       : " << (available ? "Available" : "Reserved") << '\n';
        cout << "--------------------------------\n";
    }
}
;
class Recipient : public Person {
private:
    string organ;
    string size;
    string blood;
    int priority;
public:
    Recipient() {
        priority = 3;
    }
    Recipient(int id, string name, char gender, int age, string phone, string address, string organ, string size, string blood, int priority) : Person(id, name, gender, age, phone, address) {
        this->organ = organ;
        this->size = size;
        this->blood = blood;
        this->priority = priority;
    }
    string getOrgan() const {
        return organ;
    }
    string getSize() const {
        return size;
    }
    string getBlood() const {
        return blood;
    }
    int getPriority() const {
        return priority;
    }
    void update() {
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
        if (priority < 1 || priority > 3) priority = 3;
        cout << "Recipient updated.\n";
    }
    void display() const override {
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
        if (priority == 1) cout << "Emergency";
        else if (priority == 2) cout << "High";
        else cout << "Normal";
        cout << "\n--------------------------------\n";
    }
}
;
/* =========================================================                      DONOR LINKED LIST    ========================================================= */ 
class DonorNode {
public:
    Donor data;
    DonorNode* next;
    DonorNode(Donor d) {
        data = d;
        next = NULL;
    }
}
;
class DonorList {
private:
    DonorNode* head;
public:
    DonorList() {
        head = NULL;
    }
    void insert(Donor d) {
        DonorNode* newNode = new DonorNode(d);
        if (head == NULL) {
            head = newNode;
            return;
        }
        DonorNode* temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
    DonorNode* search(int id) {
        DonorNode* temp = head;
        while (temp != NULL) {
            if (temp->data.getID() == id) return temp;
            temp = temp->next;
        }
        return NULL;
    }
    bool remove(int id) {
        if (head == NULL) return false;
        if (head->data.getID() == id) {
            DonorNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        DonorNode* temp = head;
        while (temp->next != NULL) {
            if (temp->next->data.getID() == id) {
                DonorNode* del = temp->next;
                temp->next = del->next;
                delete del;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    int size() {
        int count = 0;
        DonorNode* temp = head;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    void display() {
        DonorNode* temp = head;
        if (temp == NULL) {
            cout << "\nNo donors available.\n";
            return;
        }
        while (temp != NULL) {
            temp->data.display();
            temp = temp->next;
        }
    }
    DonorNode* getHead() {
        return head;
    }
}
;
/* =========================================================                     RECIPIENT LINKED LIST    ========================================================= */ 
class RecipientNode {
public:
    Recipient data;
    RecipientNode* next;
    RecipientNode(Recipient r) {
        data = r;
        next = NULL;
    }
}
;
class RecipientList {
private:
    RecipientNode* head;
public:
    RecipientList() {
        head = NULL;
    }
    void insert(Recipient r) {
        RecipientNode* newNode = new RecipientNode(r);
        if (head == NULL) {
            head = newNode;
            return;
        }
        RecipientNode* temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
    RecipientNode* search(int id) {
        RecipientNode* temp = head;
        while (temp != NULL) {
            if (temp->data.getID() == id) return temp;
            temp = temp->next;
        }
        return NULL;
    }
    bool remove(int id) {
        if (head == NULL) return false;
        if (head->data.getID() == id) {
            RecipientNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        RecipientNode* temp = head;
        while (temp->next != NULL) {
            if (temp->next->data.getID() == id) {
                RecipientNode* del = temp->next;
                temp->next = del->next;
                delete del;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    int size() {
        int count = 0;
        RecipientNode* temp = head;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    void display() {
        RecipientNode* temp = head;
        if (temp == NULL) {
            cout << "\nNo recipients available.\n";
            return;
        }
        while (temp != NULL) {
            temp->data.display();
            temp = temp->next;
        }
    }
    RecipientNode* getHead() {
        return head;
    }
}
;
/* =========================================================                          HASH TABLE    Custom HashMap: ID -> Donor/Recipient    ========================================================= */ 
const int HASH_SIZE = 101;
class DonorHashTable {
private:
    Donor* table[HASH_SIZE];
    bool occupied[HASH_SIZE];
    int hashFunction(int id) {
        return id % HASH_SIZE;
    }
public:
    DonorHashTable() {
        for (int i = 0;i < HASH_SIZE;i++) {
            table[i] = NULL;
            occupied[i] = false;
        }
    }
    bool insert(Donor* d) {
        int index = hashFunction(d->getID());
        for (int i = 0;
        i < HASH_SIZE;
        i++) {
            int pos = (index + i) % HASH_SIZE;
            if (!occupied[pos]) {
                table[pos] = d;
                occupied[pos] = true;
                return true;
            }
            if (table[pos]->getID() == d->getID()) return false;
        }
        return false;
    }
    Donor* search(int id) {
        int index = hashFunction(id);
        for (int i = 0; i < HASH_SIZE; i++) {
            int pos = (index + i) % HASH_SIZE;
            if (!occupied[pos]) return NULL;
            if (table[pos]->getID() == id) return table[pos];
        }
        return NULL;
    }
    bool remove(int id) {
        int index = hashFunction(id);
        for (int i = 0;
        i < HASH_SIZE;
        i++) {
            int pos = (index + i) % HASH_SIZE;
            if (!occupied[pos]) return false;
            if (table[pos]->getID() == id) {
                table[pos] = NULL;
                occupied[pos] = false;
                int next = (pos + 1) % HASH_SIZE;
                int checked = 0;
                while (occupied[next] && checked < HASH_SIZE) {
                    Donor* displaced = table[next];
                    table[next] = NULL;
                    occupied[next] = false;
                    insert(displaced);
                    next = (next + 1) % HASH_SIZE;
                    checked++;
                }
                return true;
            }
        }
        return false;
    }
}
;
class RecipientHashTable {
private:
    Recipient* table[HASH_SIZE];
    bool occupied[HASH_SIZE];
    int hashFunction(int id) {
        return id % HASH_SIZE;
    }
public:
    RecipientHashTable() {
        for (int i = 0;
        i < HASH_SIZE;
        i++) {
            table[i] = NULL;
            occupied[i] = false;
        }
    }
    bool insert(Recipient* r) {
        int index = hashFunction(r->getID());
        for (int i = 0;
        i < HASH_SIZE;
        i++) {
            int pos = (index + i) % HASH_SIZE;
            if (!occupied[pos]) {
                table[pos] = r;
                occupied[pos] = true;
                return true;
            }
            if (table[pos]->getID() == r->getID()) return false;
        }
        return false;
    }
    Recipient* search(int id) {
        int index = hashFunction(id);
        for (int i = 0;
        i < HASH_SIZE;
        i++) {
            int pos = (index + i) % HASH_SIZE;
            if (!occupied[pos]) return NULL;
            if (table[pos]->getID() == id) return table[pos];
        }
        return NULL;
    }
    bool remove(int id) {
        int index = hashFunction(id);
        for (int i = 0;
        i < HASH_SIZE;
        i++) {
            int pos = (index + i) % HASH_SIZE;
            if (!occupied[pos]) return false;
            if (table[pos]->getID() == id) {
                table[pos] = NULL;
                occupied[pos] = false;
                int next = (pos + 1) % HASH_SIZE;
                int checked = 0;
                while (occupied[next] && checked < HASH_SIZE) {
                    Recipient* displaced = table[next];
                    table[next] = NULL;
                    occupied[next] = false;
                    insert(displaced);
                    next = (next + 1) % HASH_SIZE;
                    checked++;
                }
                return true;
            }
        }
        return false;
    }
}
;
/* =========================================================                            HOSPITAL    ========================================================= */
class Hospital {
private:
    int id;
    string name;
    string location;
    string password;
public:
    Hospital() {
        id = 0;
    }
    Hospital(int id, string name, string location, string password) {
        this->id = id;
        this->name = name;
        this->location = location;
        this->password = password;
    }
    int getID() const {
        return id;
    }
    string getName() const {
        return name;
    }
    bool checkPassword(string p) {
        return p == password;
    }
    void display() {
        cout << "\nHospital ID : " << id;
        cout << "\nName        : " << name;
        cout << "\nLocation    : " << location;
        cout << "\n-------------------------\n";
    }
}
;
/* =========================================================                      HOSPITAL ARRAY    ========================================================= */ 
const int MAX_HOSPITALS = 50;
class HospitalManager {
private:
    Hospital hospitals[MAX_HOSPITALS];
    int count;
public:
    HospitalManager() {
        count = 0;
    }
    bool add(Hospital h) {
        if (count == MAX_HOSPITALS) return false;
        if (search(h.getID()) != NULL) return false;
        hospitals[count++] = h;
        return true;
    }
    Hospital* search(int id) {
        for (int i = 0 ;i < count; i++) {
            if (hospitals[i].getID() == id) return &hospitals[i];
        }
        return NULL;
    }
    void display() {
        if (count == 0) {
            cout << "\nNo hospitals registered.\n";
            return;
        }
        for (int i = 0; i < count; i++) hospitals[i].display();
    }
    int size() {
        return count;
    }
}
;
/* =========================================================                        REQUEST + QUEUE    ========================================================= */ 
class Request {
private:
    int requestID;
    int donorID;
    int recipientID;
    int fromHospital;
    int toHospital;
    string status;
public:
    Request() {
        requestID = donorID = recipientID = 0;
        fromHospital = toHospital = 0;
        status = "PENDING";
    }
    Request(int rid, int did, int recid, int from, int to) {
        requestID = rid;
        donorID = did;
        recipientID = recid;
        fromHospital = from;
        toHospital = to;
        status = "PENDING";
    }
    int getID() const {
        return requestID;
    }
    int getDonorID() const {
        return donorID;
    }
    int getRecipientID() const {
        return recipientID;
    }
    void setStatus(string s) {
        status = s;
    }
    string getStatus() const {
        return status;
    }
    void display() {
        cout << "\nRequest ID    : " << requestID;
        cout << "\nDonor ID      : " << donorID;
        cout << "\nRecipient ID  : " << recipientID;
        cout << "\nFrom Hospital : " << fromHospital;
        cout << "\nTo Hospital   : " << toHospital;
        cout << "\nStatus        : " << status << '\n';
    }
}
;
class RequestNode {
public:
    Request data;
    RequestNode* next;
    RequestNode(Request r) {
        data = r;
        next = NULL;
    }
}
;
class RequestQueue {
private:
    RequestNode* front;
    RequestNode* rear;
public:
    RequestQueue() {
        front = rear = NULL;
    }
    bool empty() {
        return front == NULL;
    }
    void push(Request r) {
        RequestNode* newNode = new RequestNode(r);
        if (rear == NULL) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }
    Request pop() {
        Request temp;
        if (front == NULL) return temp;
        RequestNode* del = front;
        temp = front->data;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete del;
        return temp;
    }
}
;
/* =========================================================                  PRIORITY QUEUE - MAX HEAP    ========================================================= */ 
struct PriorityItem {
    int recipientID;
    int priority;
}
;
const int MAX_PRIORITY = 200;
class PriorityQueue {
private:
    PriorityItem heap[MAX_PRIORITY];
    int size;
    void swapItem(PriorityItem& a, PriorityItem& b) {
        PriorityItem temp = a;
        a = b;
        b = temp;
    }
public:
    PriorityQueue() {
        size = 0;
    }
    bool empty() {
        return size == 0;
    }
    void push(int id, int priority) {
        if (size == MAX_PRIORITY) return;
        heap[size].recipientID = id;
        heap[size].priority = priority;
        int i = size;
        size++;
        while (i != 0) {
            int parent = (i - 1) / 2;
            if (heap[parent].priority <= heap[i].priority) break;
            swapItem(heap[parent], heap[i]);
            i = parent;
        }
    }
    PriorityItem pop() {
        PriorityItem result;
        result.recipientID = -1;
        result.priority = -1;
        if (size == 0) return result;
        result = heap[0];
        heap[0] = heap[size - 1];
        size--;
        int i = 0;
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            if (left < size && heap[left].priority < heap[smallest].priority) smallest = left;
            if (right < size && heap[right].priority < heap[smallest].priority) smallest = right;
            if (smallest == i) break;
            swapItem(heap[i], heap[smallest]);
            i = smallest;
        }
        return result;
    }
}
;
/* =========================================================                      GRAPH    Adjacency Matrix    ========================================================= */ 
/* =========================================================                   MAIN SYSTEM CLASS    ========================================================= */
class OrganTransplantSystem {
private:
    DonorList donorList;
    RecipientList recipientList;
    DonorHashTable donorHash;
    RecipientHashTable recipientHash;
    HospitalManager hospitalManager;
    RequestQueue requestQueue;
    PriorityQueue priorityQueue;
    Request requests[200];
    int requestCount;
    int nextRequestID;
public:
    OrganTransplantSystem() {
        requestCount = 0;
        nextRequestID = 1001;
    }
    string organType() {
        int choice;
        cout << "\n1. Kidney\n";
        cout << "2. Liver\n";
        cout << "3. Heart\n";
        cout << "4. Lung\n";
        cout << "5. Pancreas\n";
        cout << "Enter choice: ";
        cin >> choice;
        clearInput();
        if (choice == 1) return "Kidney";
        if (choice == 2) return "Liver";
        if (choice == 3) return "Heart";
        if (choice == 4) return "Lung";
        if (choice == 5) return "Pancreas";
        cout << "Invalid choice.\n";
        return organType();
    }
    string bloodGroup() {
        string b;
        while (true) {
            cout << "Blood Group: ";
            getline(cin, b);
            if (b == "A+" || b == "A-" || b == "B+" || b == "B-" || b == "AB+" || b == "AB-" || b == "O+" || b == "O-") return b;
            cout << "Invalid blood group.\n";
        }
    }
    string organSize() {
        int choice;
        cout << "\n1. Small\n";
        cout << "2. Medium\n";
        cout << "3. Large\n";
        cout << "Enter choice: ";
        cin >> choice;
        clearInput();
        if (choice == 1) return "Small";
        if (choice == 2) return "Medium";
        if (choice == 3) return "Large";
        cout << "Invalid choice.\n";
        return organSize();
    }
    int priority() {
        int p;
        cout << "\n1. Emergency\n";
        cout << "2. High\n";
        cout << "3. Normal\n";
        cout << "Enter priority: ";
        cin >> p;
        clearInput();
        if (p >= 1 && p <= 3) return p;
        cout << "Invalid priority.\n";
        return priority();
    }
    bool bloodCompatible(string donor, string receiver) {
        if (donor == "O-") return true;
        if (donor == "O+") return receiver == "O+" || receiver == "A+" || receiver == "B+" || receiver == "AB+";
        if (donor == "A-") return receiver == "A-" || receiver == "AB-" || receiver == "A+" || receiver == "AB+";
        if (donor == "A+") return receiver == "A+" || receiver == "AB+";
        if (donor == "B-") return receiver == "B-" || receiver == "AB-" || receiver == "B+" || receiver == "AB+";
        if (donor == "B+") return receiver == "B+" || receiver == "AB+";
        if (donor == "AB-") return receiver == "AB-" || receiver == "AB+";
        if (donor == "AB+") return receiver == "AB+";
        return false;
    }
    bool sizeCompatible(string donor, string receiver) {
        if (donor == receiver) return true;
        if (donor == "Large" && receiver == "Medium") return true;
        if (donor == "Medium" && receiver == "Small") return true;
        return false;
    }
    bool eligible(Donor& d, Recipient& r) {
        if (!d.isAvailable()) return false;
        if (d.getOrgan() != r.getOrgan()) return false;
        if (!bloodCompatible(d.getBlood(), r.getBlood())) return false;
        if (!sizeCompatible(d.getSize(), r.getSize())) return false;
        return true;
    }
    /* ---------------- HOSPITAL ---------------- */ 
    void registerHospital() {
        int id;
        cout << "\nHospital ID: ";
        cin >> id;
        clearInput();
        if (hospitalManager.search(id) != NULL) {
            cout << "Hospital already exists.\n";
            return;
        }
        string name, location, password;
        cout << "Hospital Name: ";
        getline(cin, name);
        cout << "Location: ";
        getline(cin, location);
        cout << "Password: ";
        getline(cin, password);
        Hospital h(id, name, location, password);
        if (hospitalManager.add(h)) {
            cout << "Hospital registered successfully.\n";
        }
    }
    void login() {
        int id;
        string password;
        cout << "\nHospital ID: ";
        cin >> id;
        clearInput();
        cout << "Password: ";
        getline(cin, password);
        Hospital* h = hospitalManager.search(id);
        if (h == NULL) {
            cout << "Hospital not found.\n";
            return;
        }
        if (!h->checkPassword(password)) {
            cout << "Wrong password.\n";
            return;
        }
        cout << "\nWelcome " << h->getName() << "!\n";
        hospitalMenu();
    }
    /* ---------------- DONOR ---------------- */ 
    void addDonor() {
        int id;
        cout << "\nDonor ID: ";
        cin >> id;
        clearInput();
        if (donorHash.search(id) != NULL) {
            cout << "Donor ID already exists.\n";
            return;
        }
        int hospitalID;
        cout << "Hospital ID: ";
        cin >> hospitalID;
        clearInput();
        if (hospitalManager.search(hospitalID) == NULL) {
            cout << "Hospital not found.\n";
            return;
        }
        string name, phone, address;
        char gender;
        int age;
        cout << "Name: ";
        getline(cin, name);
        cout << "Gender (M/F): ";
        cin >> gender;
        clearInput();
        cout << "Age: ";
        cin >> age;
        clearInput();
        cout << "Phone: ";
        getline(cin, phone);
        cout << "Address: ";
        getline(cin, address);
        string organ = organType();
        string size = organSize();
        string blood = bloodGroup();
        Donor* d = new Donor(id, name, gender, age, phone, address, organ, size, blood);
        donorList.insert(*d);
        DonorNode* node = donorList.search(id);
        if (node != NULL) {
            donorHash.insert(&node->data);
            delete d;
        }
        cout << "Donor added successfully.\n";
    }
    void viewDonors() {
        donorList.display();
    }
    void searchDonor() {
        int id;
        cout << "\nDonor ID: ";
        cin >> id;
        clearInput();
        Donor* d = donorHash.search(id);
        if (d == NULL) {
            cout << "Donor not found.\n";
            return;
        }
        d->display();
    }
    void updateDonor() {
        int id;
        cout << "\nDonor ID: ";
        cin >> id;
        clearInput();
        Donor* d = donorHash.search(id);
        if (d == NULL) {
            cout << "Donor not found.\n";
            return;
        }
        d->update();
    }
    void deleteDonor() {
        int id;
        cout << "\nDonor ID: ";
        cin >> id;
        clearInput();
        if (donorHash.search(id) == NULL) {
            cout << "Donor not found.\n";
            return;
        }
        donorHash.remove(id);
        donorList.remove(id);
        cout << "Donor deleted.\n";
    }
    /* ---------------- RECIPIENT ---------------- */ 
    void addRecipient() {
        int id;
        cout << "\nRecipient ID: ";
        cin >> id;
        clearInput();
        if (recipientHash.search(id) != NULL) {
            cout << "Recipient ID already exists.\n";
            return;
        }
        int hospitalID;
        cout << "Hospital ID: ";
        cin >> hospitalID;
        clearInput();
        if (hospitalManager.search(hospitalID) == NULL) {
            cout << "Hospital not found.\n";
            return;
        }
        string name, phone, address;
        char gender;
        int age;
        cout << "Name: ";
        getline(cin, name);
        cout << "Gender (M/F): ";
        cin >> gender;
        clearInput();
        cout << "Age: ";
        cin >> age;
        clearInput();
        cout << "Phone: ";
        getline(cin, phone);
        cout << "Address: ";
        getline(cin, address);
        string organ = organType();
        string size = organSize();
        string blood = bloodGroup();
        int p = priority();
        Recipient* r = new Recipient(id, name, gender, age, phone, address, organ, size, blood, p);
        recipientList.insert(*r);
        RecipientNode* node = recipientList.search(id);
        if (node != NULL) {
            recipientHash.insert(&node->data);
            priorityQueue.push(id, p);
            delete r;
        }
        cout << "Recipient added successfully.\n";
    }
    void viewRecipients() {
        recipientList.display();
    }
    void searchRecipient() {
        int id;
        cout << "\nRecipient ID: ";
        cin >> id;
        clearInput();
        Recipient* r = recipientHash.search(id);
        if (r == NULL) {
            cout << "Recipient not found.\n";
            return;
        }
        r->display();
    }
    void updateRecipient() {
        int id;
        cout << "\nRecipient ID: ";
        cin >> id;
        clearInput();
        Recipient* r = recipientHash.search(id);
        if (r == NULL) {
            cout << "Recipient not found.\n";
            return;
        }
        r->update();
        priorityQueue.push(id, r->getPriority());
    }
    void deleteRecipient() {
        int id;
        cout << "\nRecipient ID: ";
        cin >> id;
        clearInput();
        if (recipientHash.search(id) == NULL) {
            cout << "Recipient not found.\n";
            return;
        }
        recipientHash.remove(id);
        recipientList.remove(id);
        cout << "Recipient deleted.\n";
    }
    /* ---------------- ELIGIBILITY ---------------- */ 
    void findEligible() {
        int recipientID;
        cout << "\nRecipient ID: ";
        cin >> recipientID;
        clearInput();
        Recipient* r = recipientHash.search(recipientID);
        if (r == NULL) {
            cout << "Recipient not found.\n";
            return;
        }
        DonorNode* temp = donorList.getHead();
        int found = 0;
        cout << "\n========== ELIGIBLE DONORS ==========\n";
        while (temp != NULL) {
            if (eligible(temp->data, *r)) {
                temp->data.display();
                found++;
            }
            temp = temp->next;
        }
        if (found == 0) cout << "\nNo eligible donor found.\n";
        else cout << "\nTotal eligible donors: " << found << '\n';
    }
    /* ---------------- REQUEST ---------------- */ 
    void createRequest() {
        int donorID, recipientID;
        int fromHospital, toHospital;
        cout << "\nDonor ID: ";
        cin >> donorID;
        cout << "Recipient ID: ";
        cin >> recipientID;
        cout << "Requesting Hospital ID: ";
        cin >> fromHospital;
        cout << "Donor Hospital ID: ";
        cin >> toHospital;
        clearInput();
        Donor* d = donorHash.search(donorID);
        Recipient* r = recipientHash.search(recipientID);
        if (d == NULL || r == NULL) {
            cout << "Donor or recipient not found.\n";
            return;
        }
        if (hospitalManager.search(fromHospital) == NULL || hospitalManager.search(toHospital) == NULL) {
            cout << "Hospital not found.\n";
            return;
        }
        if (!eligible(*d, *r)) {
            cout << "\nDonor is not eligible for this recipient.\n";
            return;
        }
        if (requestCount >= 200) {
            cout << "Request storage full.\n";
            return;
        }
        Request req(nextRequestID++, donorID, recipientID, fromHospital, toHospital);
        requests[requestCount++] = req;
        requestQueue.push(req);
        d->setAvailable(false);
        cout << "\nRequest created successfully.\n";
        cout << "Request ID: " << req.getID() << '\n';
    }
    void viewRequests() {
        if (requestCount == 0) {
            cout << "\nNo requests.\n";
            return;
        }
        cout << "\n========== REQUESTS ==========\n";
        for (int i = 0;
        i < requestCount;
        i++) {
            requests[i].display();
            cout << "-------------------------\n";
        }
    }
    void processRequest() {
        if (requestQueue.empty()) {
            cout << "\nNo pending request.\n";
            return;
        }
        Request req = requestQueue.pop();
        cout << "\n========== PROCESS REQUEST ==========\n";
        req.display();
        int choice;
        cout << "\n1. Accept\n";
        cout << "2. Reject\n";
        cout << "Choice: ";
        cin >> choice;
        clearInput();
        for (int i = 0;
        i < requestCount;
        i++) {
            if (requests[i].getID() == req.getID()) {
                if (choice == 1) {
                    requests[i].setStatus("ACCEPTED");
                    cout << "Request accepted.\n";
                }
                else {
                    requests[i].setStatus("REJECTED");
                    Donor* d = donorHash.search(req.getDonorID());
                    if (d != NULL) d->setAvailable(true);
                    cout << "Request rejected.\n";
                }
                return;
            }
        }
    }
    /* ---------------- PRIORITY QUEUE ---------------- */
    void nextPriorityRecipient() {
        while (!priorityQueue.empty()) {
            PriorityItem item = priorityQueue.pop();
            Recipient* r = recipientHash.search(item.recipientID);
            if (r != NULL) {
                cout << "\n========== NEXT PRIORITY RECIPIENT ==========\n";
                r->display();
                return;
            }
        }
        cout << "\nPriority queue empty.\n";
    }
    /* ---------------- STATISTICS ---------------- */ 
    void statistics() {
        int available = 0;
        DonorNode* d = donorList.getHead();
        while (d != NULL) {
            if (d->data.isAvailable()) available++;
            d = d->next;
        }
        cout << "\n========== SYSTEM STATISTICS ==========\n";
        cout << "Hospitals        : " << hospitalManager.size() << '\n';
        cout << "Donors           : " << donorList.size() << '\n';
        cout << "Recipients       : " << recipientList.size() << '\n';
        cout << "Available Donors : " << available << '\n';
        cout << "Requests         : " << requestCount << '\n';
    }
    /* ---------------- MENUS ---------------- */ void donorMenu() {
        int choice;
        do {
            cout << "\n========== DONOR MENU ==========\n";
            cout << "1. Add Donor\n";
            cout << "2. View Donors\n";
            cout << "3. Search Donor\n";
            cout << "4. Update Donor\n";
            cout << "5. Delete Donor\n";
            cout << "0. Back\n";
            cout << "Choice: ";
            cin >> choice;
            clearInput();
            if (choice == 1) addDonor();
            else if (choice == 2) viewDonors();
            else if (choice == 3) searchDonor();
            else if (choice == 4) updateDonor();
            else if (choice == 5) deleteDonor();
        }
        while (choice != 0);
    }
    void recipientMenu() {
        int choice;
        do {
            cout << "\n========== RECIPIENT MENU ==========\n";
            cout << "1. Add Recipient\n";
            cout << "2. View Recipients\n";
            cout << "3. Search Recipient\n";
            cout << "4. Update Recipient\n";
            cout << "5. Delete Recipient\n";
            cout << "6. Next Priority Recipient\n";
            cout << "0. Back\n";
            cout << "Choice: ";
            cin >> choice;
            clearInput();
            if (choice == 1) addRecipient();
            else if (choice == 2) viewRecipients();
            else if (choice == 3) searchRecipient();
            else if (choice == 4) updateRecipient();
            else if (choice == 5) deleteRecipient();
            else if (choice == 6) nextPriorityRecipient();
        }
        while (choice != 0);
    }
    void hospitalMenu() {
        int choice;
        do {
            cout << "\n========== HOSPITAL MENU ==========\n";
            cout << "1. Donor Management\n";
            cout << "2. Recipient Management\n";
            cout << "3. Find Eligible Donors\n";
            cout << "4. Create Transplant Request\n";
            cout << "5. View Requests\n";
            cout << "6. Process Request Queue\n";
            cout << "0. Logout\n";
            cout << "Choice: ";
            cin >> choice;
            clearInput();
            if (choice == 1) donorMenu();
            else if (choice == 2) recipientMenu();
            else if (choice == 3) findEligible();
            else if (choice == 4) createRequest();
            else if (choice == 5) viewRequests();
            else if (choice == 6) processRequest();
        }
        while (choice != 0);
    }
    void adminMenu() {
        int choice;
        do {
            cout << "\n========== ADMIN PANEL ==========\n";
            cout << "1. View Hospitals\n";
            cout << "2. View Donors\n";
            cout << "3. View Recipients\n";
            cout << "4. View Requests\n";
            cout << "5. Statistics\n";
            cout << "0. Logout\n";
            cout << "Choice: ";
            cin >> choice;
            clearInput();
            if (choice == 1) hospitalManager.display();
            else if (choice == 2) viewDonors();
            else if (choice == 3) viewRecipients();
            else if (choice == 4) viewRequests();
            else if (choice == 5) statistics();
        }
        while (choice != 0);
    }
    void adminLogin() {
        string username, password;
        cout << "\nUsername: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        clearInput();
        if (username == "admin" && password == "admin123") adminMenu();
        else cout << "Invalid admin credentials.\n";
    }
public:
    void run() {
        int choice;
        do {
            cout << "\n\n============================================\n";
            cout << "      ORGAN TRANSPLANT MANAGEMENT SYSTEM\n";
            cout << "============================================\n";
            cout << "          OOP + DSA PROJECT\n";
            cout << "--------------------------------------------\n";
            cout << "1. Admin Login\n";
            cout << "2. Hospital Login\n";
            cout << "3. Register Hospital\n";
            cout << "4. Statistics\n";
            cout << "0. Exit\n";
            cout << "Choice: ";
            cin >> choice;
            clearInput();
            if (choice == 1) adminLogin();
            else if (choice == 2) login();
            else if (choice == 3) registerHospital();
            else if (choice == 4) statistics();
            else if (choice == 0) cout << "\nThank you!\n";
            else cout << "Invalid choice.\n";
        }
        while (choice != 0);
    }
}
;
int main() {
    OrganTransplantSystem system;
    system.run();
    return 0;
}
