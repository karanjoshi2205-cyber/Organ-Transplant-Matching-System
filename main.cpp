#include "Student4_Matching.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

class OrganTransplantSystem
{
private:
    DonorList donorList;
    RecipientList recipientList;
    DonorHashTable donorHash;
    RecipientHashTable recipientHash;
    HospitalManager hospitalManager;
    HospitalGraph hospitalGraph;
    RequestQueue requestQueue;
    PriorityQueue priorityQueue;
    Request requests[200];
    int requestCount;
    int nextRequestID;

public:
    // STUDENT 1: file handling for donor and recipient records.
    // STUDENT 2: hospital and graph persistence.
    // STUDENT 4: request history persistence.
    static vector<string> splitLine(const string& line)
    {
        vector<string> parts;
        string part;
        stringstream ss(line);
        while (getline(ss, part, '|')) parts.push_back(part);
        return parts;
    }

    void saveAll()
    {
        ofstream donorsFile("donors.txt");
        for (DonorNode* n = donorList.getHead(); n != NULL; n = n->next)
        {
            Donor& d = n->data;
            donorsFile << d.getID() << '|' << d.getName() << '|' << d.getGender() << '|'
                       << d.getAge() << '|' << d.getPhone() << '|' << d.getAddress() << '|'
                       << d.getOrgan() << '|' << d.getSize() << '|' << d.getBlood() << '|'
                       << (d.isAvailable() ? 1 : 0) << '\n';
        }

        ofstream recipientsFile("recipients.txt");
        for (RecipientNode* n = recipientList.getHead(); n != NULL; n = n->next)
        {
            Recipient& r = n->data;
            recipientsFile << r.getID() << '|' << r.getName() << '|' << r.getGender() << '|'
                           << r.getAge() << '|' << r.getPhone() << '|' << r.getAddress() << '|'
                           << r.getOrgan() << '|' << r.getSize() << '|' << r.getBlood() << '|'
                           << r.getPriority() << '\n';
        }

        ofstream hospitalsFile("hospitals.txt");
        for (int i = 0; i < hospitalManager.size(); i++)
        {
            Hospital* h = hospitalManager.getAt(i);
            if (h) hospitalsFile << h->getID() << '|' << h->getName() << '|'
                                 << h->getLocation() << '|' << h->getPasswordForFile() << '\n';
        }

        ofstream requestsFile("requests.txt");
        for (int i = 0; i < requestCount; i++)
            requestsFile << requests[i].getID() << '|' << requests[i].getDonorID() << '|'
                         << requests[i].getRecipientID() << '|' << requests[i].getFromHospital() << '|'
                         << requests[i].getToHospital() << '|' << requests[i].getStatus() << '\n';

        ofstream edgesFile("hospital_edges.txt");
        for (int i = 0; i < hospitalGraph.getCount(); i++)
            for (int j = i + 1; j < hospitalGraph.getCount(); j++)
                if (hospitalGraph.isConnected(i, j))
                    edgesFile << hospitalGraph.getHospitalIDAt(i) << '|'
                              << hospitalGraph.getHospitalIDAt(j) << '\n';
    }

    void loadAll()
    {
        string line;
        ifstream hospitalsFile("hospitals.txt");
        while (getline(hospitalsFile, line))
        {
            vector<string> f = splitLine(line);
            if (f.size() >= 4)
            {
                int id = atoi(f[0].c_str());
                Hospital h(id, f[1], f[2], f[3]);
                if (hospitalManager.add(h)) hospitalGraph.addHospital(id);
            }
        }

        ifstream donorsFile("donors.txt");
        while (getline(donorsFile, line))
        {
            vector<string> f = splitLine(line);
            if (f.size() >= 10)
            {
                Donor d(atoi(f[0].c_str()), f[1], f[2].empty() ? 'M' : f[2][0],
                        atoi(f[3].c_str()), f[4], f[5], f[6], f[7], f[8]);
                d.setAvailable(atoi(f[9].c_str()) != 0);
                donorList.insert(d);
                DonorNode* n = donorList.search(d.getID());
                if (n) donorHash.insert(&n->data);
            }
        }

        ifstream recipientsFile("recipients.txt");
        while (getline(recipientsFile, line))
        {
            vector<string> f = splitLine(line);
            if (f.size() >= 10)
            {
                Recipient r(atoi(f[0].c_str()), f[1], f[2].empty() ? 'M' : f[2][0],
                            atoi(f[3].c_str()), f[4], f[5], f[6], f[7], f[8], atoi(f[9].c_str()));
                recipientList.insert(r);
                RecipientNode* n = recipientList.search(r.getID());
                if (n)
                {
                    recipientHash.insert(&n->data);
                    priorityQueue.push(r.getID(), r.getPriority());
                }
            }
        }

        ifstream edgesFile("hospital_edges.txt");
        while (getline(edgesFile, line))
        {
            vector<string> f = splitLine(line);
            if (f.size() >= 2) hospitalGraph.addConnection(atoi(f[0].c_str()), atoi(f[1].c_str()));
        }

        ifstream requestsFile("requests.txt");
        while (getline(requestsFile, line) && requestCount < 200)
        {
            vector<string> f = splitLine(line);
            if (f.size() >= 6)
            {
                Request req(atoi(f[0].c_str()), atoi(f[1].c_str()), atoi(f[2].c_str()),
                            atoi(f[3].c_str()), atoi(f[4].c_str()));
                req.setStatus(f[5]);
                requests[requestCount++] = req;
                if (req.getStatus() == "PENDING") requestQueue.push(req);
                if (req.getID() >= nextRequestID) nextRequestID = req.getID() + 1;
            }
        }
    }

    OrganTransplantSystem()
    {
        requestCount = 0;
        nextRequestID = 1001;
        loadAll();
    }

void registerHospital()
{
    int id;

    cout << "\nHospital ID: ";
    cin >> id;
    clearInput();

    if (hospitalManager.search(id) != NULL)
    {
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

    if (hospitalManager.add(h))
    {
cout << "Hospital registered successfully.\n";
        hospitalGraph.addHospital(id);
        saveAll();
    }
}

void login()
{
    int id;
    string password;

    cout << "\nHospital ID: ";
    cin >> id;
    clearInput();

    cout << "Password: ";
    getline(cin, password);

    Hospital* h = hospitalManager.search(id);

    if (h == NULL)
    {
        cout << "Hospital not found.\n";
        return;
    }

    if (!h->checkPassword(password))
    {
        cout << "Wrong password.\n";
        return;
    }

    cout << "\nWelcome " << h->getName() << "!\n";
    hospitalMenu();
}

/* ---------------- DONOR ---------------- */

void addDonor()
{
    int id;

    cout << "\nDonor ID: ";
    cin >> id;
    clearInput();

    if (donorHash.search(id) != NULL)
    {
        cout << "Donor ID already exists.\n";
        return;
    }

    int hospitalID;

    cout << "Hospital ID: ";
    cin >> hospitalID;
    clearInput();

    if (hospitalManager.search(hospitalID) == NULL)
    {
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

    Donor* d = new Donor(id, name, gender, age,
                          phone, address,
                          organ, size, blood);

    donorList.insert(*d);

    DonorNode* node = donorList.search(id);

    if (node != NULL)
    {
        donorHash.insert(&node->data);
        delete d;
    }

    cout << "Donor added successfully.\n";
    saveAll();
}

void viewDonors()
{
    donorList.display();
}

void searchDonor()
{
    int id;

    cout << "\nDonor ID: ";
    cin >> id;
    clearInput();

    Donor* d = donorHash.search(id);

    if (d == NULL)
    {
        cout << "Donor not found.\n";
        return;
    }

    d->display();
}

void updateDonor()
{
    int id;

    cout << "\nDonor ID: ";
    cin >> id;
    clearInput();

    Donor* d = donorHash.search(id);

    if (d == NULL)
    {
        cout << "Donor not found.\n";
        return;
    }

    d->update();
    saveAll();
}

void deleteDonor()
{
    int id;

    cout << "\nDonor ID: ";
    cin >> id;
    clearInput();

    if (donorHash.search(id) == NULL)
    {
        cout << "Donor not found.\n";
        return;
    }

    donorHash.remove(id);
    donorList.remove(id);

    cout << "Donor deleted.\n";
    saveAll();
}

/* ---------------- RECIPIENT ---------------- */

void addRecipient()
{
    int id;

    cout << "\nRecipient ID: ";
    cin >> id;
    clearInput();

    if (recipientHash.search(id) != NULL)
    {
        cout << "Recipient ID already exists.\n";
        return;
    }

    int hospitalID;

    cout << "Hospital ID: ";
    cin >> hospitalID;
    clearInput();

    if (hospitalManager.search(hospitalID) == NULL)
    {
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

    Recipient* r = new Recipient(id, name, gender, age,
                                 phone, address,
                                 organ, size, blood, p);

    recipientList.insert(*r);

    RecipientNode* node = recipientList.search(id);

    if (node != NULL)
    {
        recipientHash.insert(&node->data);
        priorityQueue.push(id, p);
        delete r;
    }

    cout << "Recipient added successfully.\n";
    saveAll();
}

void viewRecipients()
{
    recipientList.display();
}

void searchRecipient()
{
    int id;

    cout << "\nRecipient ID: ";
    cin >> id;
    clearInput();

    Recipient* r = recipientHash.search(id);

    if (r == NULL)
    {
        cout << "Recipient not found.\n";
        return;
    }

    r->display();
}

void updateRecipient()
{
    int id;

    cout << "\nRecipient ID: ";
    cin >> id;
    clearInput();

    Recipient* r = recipientHash.search(id);

    if (r == NULL)
    {
        cout << "Recipient not found.\n";
        return;
    }

    r->update();
    priorityQueue.push(id, r->getPriority());
    saveAll();
}

void deleteRecipient()
{
    int id;

    cout << "\nRecipient ID: ";
    cin >> id;
    clearInput();

    if (recipientHash.search(id) == NULL)
    {
        cout << "Recipient not found.\n";
        return;
    }

    recipientHash.remove(id);
    recipientList.remove(id);

    cout << "Recipient deleted.\n";
    saveAll();
}

/* ---------------- ELIGIBILITY ---------------- */

void findEligible()
{
    int recipientID;

    cout << "\nRecipient ID: ";
    cin >> recipientID;
    clearInput();

    Recipient* r = recipientHash.search(recipientID);

    if (r == NULL)
    {
        cout << "Recipient not found.\n";
        return;
    }

    DonorNode* temp = donorList.getHead();
    int found = 0;

    cout << "\n========== ELIGIBLE DONORS ==========\n";

    while (temp != NULL)
    {
        if (eligible(temp->data, *r))
        {
            temp->data.display();
            found++;
        }

        temp = temp->next;
    }

    if (found == 0)
        cout << "\nNo eligible donor found.\n";
    else
        cout << "\nTotal eligible donors: " << found << '\n';
}

/* ---------------- REQUEST ---------------- */

void createRequest()
{
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

    if (d == NULL || r == NULL)
    {
        cout << "Donor or recipient not found.\n";
        return;
    }

    if (hospitalManager.search(fromHospital) == NULL ||
        hospitalManager.search(toHospital) == NULL)
    {
        cout << "Hospital not found.\n";
        return;
    }

    if (!eligible(*d, *r))
    {
        cout << "\nDonor is not eligible for this recipient.\n";
        return;
    }

    if (requestCount >= 200)
    {
        cout << "Request storage full.\n";
        return;
    }

    Request req(nextRequestID++,
                 donorID,
                 recipientID,
                 fromHospital,
                 toHospital);

    requests[requestCount++] = req;
    requestQueue.push(req);

    d->setAvailable(false);

    cout << "\nRequest created successfully.\n";
    cout << "Request ID: " << req.getID() << '\n';
    saveAll();
}

void viewRequests()
{
    if (requestCount == 0)
    {
        cout << "\nNo requests.\n";
        return;
    }

    cout << "\n========== REQUESTS ==========\n";

    for (int i = 0; i < requestCount; i++)
    {
        requests[i].display();
        cout << "-------------------------\n";
    }
}

void processRequest()
{
    if (requestQueue.empty())
    {
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

    for (int i = 0; i < requestCount; i++)
    {
        if (requests[i].getID() == req.getID())
        {
            if (choice == 1)
            {
                requests[i].setStatus("ACCEPTED");
                cout << "Request accepted.\n";
            }
            else
            {
                requests[i].setStatus("REJECTED");

                Donor* d = donorHash.search(req.getDonorID());

                if (d != NULL)
                    d->setAvailable(true);

                cout << "Request rejected.\n";
            }

            saveAll();
            return;
        }
    }
}

/* ---------------- PRIORITY QUEUE ---------------- */

void nextPriorityRecipient()
{
    while (!priorityQueue.empty())
    {
        PriorityItem item = priorityQueue.pop();

        Recipient* r = recipientHash.search(item.recipientID);

        if (r != NULL)
        {
            cout << "\n========== NEXT PRIORITY RECIPIENT ==========\n";
            r->display();
            return;
        }
    }

    cout << "\nPriority queue empty.\n";
}
/* ---------------- SORTING ---------------- */


void donorMenu()
{
    int choice;

    do
    {
        cout << "\n========== DONOR MENU ==========\n";
        cout << "1. Add Donor\n";
        cout << "2. View Donors\n";
        cout << "3. Search Donor\n";
        cout << "4. Update Donor\n";
        cout << "5. Delete Donor\n";
        cout << "6. Sort Donors By Age\n";
        cout << "0. Back\n";
        cout << "Choice: ";

        cin >> choice;
        clearInput();

        if (choice == 1) addDonor();
        else if (choice == 2) viewDonors();
        else if (choice == 3) searchDonor();
        else if (choice == 4) updateDonor();
        else if (choice == 5) deleteDonor();
        else if (choice == 6) sortDonorsByAge(donorList);

    } while (choice != 0);
}

void recipientMenu()
{
    int choice;

    do
    {
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

    } while (choice != 0);
}

void hospitalMenu()
{
    int choice;

    do
    {
        cout << "\n========== HOSPITAL MENU ==========\n";
        cout << "1. Donor Management\n";
        cout << "2. Recipient Management\n";
        cout << "3. Find Eligible Donors\n";
        cout << "4. Create Transplant Request\n";
        cout << "5. View Requests\n";
        cout << "6. Process Request Queue\n";
cout << "7. Sort Donors By Age\n";
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
        else if (choice == 7) sortDonorsByAge(donorList);

    } while (choice != 0);
}

void graphMenu()
{
    int choice, id1, id2;
    do
    {
        cout << "\n========== HOSPITAL GRAPH MENU ==========\n";
        cout << "1. Connect Hospitals\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. BFS Traversal\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        clearInput();

        if (choice == 1)
        {
            cout << "First Hospital ID: "; cin >> id1;
            cout << "Second Hospital ID: "; cin >> id2;
            clearInput();
            hospitalGraph.addConnection(id1, id2);
            saveAll();
        }
        else if (choice == 2) hospitalGraph.displayGraph();
        else if (choice == 3)
        {
            cout << "Starting Hospital ID: "; cin >> id1;
            clearInput();
            hospitalGraph.BFS(id1);
        }
        else if (choice != 0) cout << "Invalid choice.\n";
    } while (choice != 0);
}

void adminMenu()
{
    int choice;

    do
    {
        cout << "\n========== ADMIN PANEL ==========\n";
        cout << "1. View Hospitals\n";
        cout << "2. View Donors\n";
        cout << "3. View Recipients\n";
        cout << "4. View Requests\n";
        cout << "5. Statistics\n";
        cout << "6. Hospital Graph (Adjacency Matrix + BFS)\n";
cout << "0. Logout\n";
        cout << "Choice: ";

        cin >> choice;
        clearInput();

        if (choice == 1) hospitalManager.display();
        else if (choice == 2) viewDonors();
        else if (choice == 3) viewRecipients();
        else if (choice == 4) viewRequests();
        else if (choice == 5) showStatistics(hospitalManager, donorList, recipientList, requestCount);
        else if (choice == 6) graphMenu();
} while (choice != 0);
}

void adminLogin()
{
    string username, password;

    cout << "\nUsername: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;
    clearInput();

    if (username == "admin" && password == "admin123")
        adminMenu();
    else
        cout << "Invalid admin credentials.\n";
}

public:

void run()
{
    int choice;

    do
    {
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

        if (choice == 1)
            adminLogin();

        else if (choice == 2)
            login();

        else if (choice == 3)
            registerHospital();

        else if (choice == 4)
            showStatistics(hospitalManager, donorList, recipientList, requestCount);

        else if (choice == 0)
        {
            saveAll();
            cout << "\nData saved. Thank you!\n";
        }

        else
            cout << "Invalid choice.\n";

    } while (choice != 0);
}
};

int main()
{
    OrganTransplantSystem system;
    system.run();
    return 0;
}
