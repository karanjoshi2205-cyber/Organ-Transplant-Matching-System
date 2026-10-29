SMART ORGAN TRANSPLANT MANAGEMENT SYSTEM
Student-level C++ OOP + DSA project

FILES
1. main.cpp
   - Preserves the original main menu: Admin Login, Hospital Login, Register Hospital, Statistics, Exit.
   - Integrates the four student modules and automatically saves/loads data.

2. Student1_DonorRecipient.h (Student 1 - Donor/Recipient data and file handling)
   - Person, Donor and Recipient classes; data display/update; donor availability.
   - In main.cpp, load/save donor and recipient records, duplicate ID checks and input validation flow.

3. Student2_HashingHospital.h (Student 2 - Karan: hashing + hospital graph)
   - Donor/recipient hash tables; hospital registration and search.
   - Hospital graph using adjacency matrix, connections, matrix display and BFS.
   - Graph and hospital data are saved to files.

4. Student3_LinkedList.h (Student 3 - Linked list)
   - Donor and recipient linked lists; insert, search, delete, display, size.
   - Donor age sorting using bubble sort.

5. Student4_Matching.h (Student 4 - matching and allocation)
   - Blood/organ/size compatibility helper; FIFO request queue; priority queue.
   - Request processing and saved request history are integrated in main.cpp.

DATA FILES CREATED AUTOMATICALLY
- donors.txt
- recipients.txt
- hospitals.txt
- requests.txt
- hospital_edges.txt

The data files are created in the same working directory as the program. Keep them beside the executable and run the program from that folder to retain data between sessions. Records use the | character as a separator, so do not type | inside a field.

BUILD (Windows / VS Code terminal with g++)
    g++ -std=c++17 -Wall -Wextra main.cpp -o main.exe
    .\main.exe

ADMIN DEMO LOGIN
    Username: admin
    Password: admin123

QUICK TEST
1. Register two hospitals from the main menu.
2. Exit and start the program again; hospital records should still exist.
3. Login as admin and choose Hospital Graph.
4. Connect the two hospital IDs, display the adjacency matrix and run BFS.
5. Add donor/recipient records; exit and restart to check persistence.

ACADEMIC DEMO NOTE
This is a classroom OOP/DSA demonstration, not a real medical allocation system. Clinical transplant eligibility requires qualified medical professionals and formal protocols. Hospital passwords are stored in plain text for this simple local demo; do not use real passwords or real patient information.
