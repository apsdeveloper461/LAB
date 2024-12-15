#ifndef COMPLAINT_H
#define COMPLAINT_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


//////////////////////////////
// Queue Data Structures
//////////////////////////////

class Complaint
{
public:
    static int nextComplaintId; // Ye line add karo
    string complaintId;         // Ye line add karo
    string citizenId;
    string location;
    string description;
    string status;
    bool isResolved;

    // Constructor jo ek naya complaint unique ID ke sath initialize karta hai
    Complaint(string id = "", string loc = "", string desc = "", string stat = "", bool resolved = false)
        : complaintId("C" + to_string(nextComplaintId++)), citizenId(id), location(loc), description(desc), status(stat), isResolved(resolved) {} // Ye line modify karo
};

// Initialize the static member, on each new commplaint register assign a new id automatically
int Complaint::nextComplaintId = 1; // Add this line

class ComplaintNode
{
public:
    Complaint data;
    ComplaintNode *next;

    ComplaintNode(const Complaint &complaint) : data(complaint), next(nullptr) {}
};

class ComplaintQueue
{
private:
    ComplaintNode *front;
    ComplaintNode *rear;

public:
    ComplaintQueue() : front(nullptr), rear(nullptr) {}

    ~ComplaintQueue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    // Add a new complaint to the queue
    void enqueue(const Complaint &c)
    {
        ComplaintNode *newNode = new ComplaintNode(c);
        if (rear == nullptr)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Remove a complaint from the queue
    bool dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty.\n";
            return false;
        }
        ComplaintNode *temp = front;
        front = front->next;
        if (front == nullptr)
        {
            rear = nullptr;
        }
        delete temp;
        return true;
    }

    // Check if the queue is empty
    bool isEmpty() const
    {
        return front == nullptr;
    }

    // Find and display complaints by citizen ID
    void findAndDisplayByCitizenId(const string &id)
    {
        ComplaintNode *current = front;
        bool found = false;
        // Print the sorted complaints in tabular format
        cout << "\n--- Display Complaints ---\n";
        cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "| Complaint ID | Citizen ID | Location      | Description                                                  | Status     | Resolved |\n";
        cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
        while (current != nullptr)
        {
            if (current->data.citizenId == id)
            {
                found = true;
                cout << "| " << setw(12) << current->data.complaintId
                     << " | " << setw(10) << current->data.citizenId
                     << " | " << setw(13) << current->data.location
                     << " | " << setw(60) << current->data.description
                     << " | " << setw(10) << current->data.status
                     << " | " << setw(8) << (current->data.isResolved ? "Yes" : "No") << " |\n";
            }
            current = current->next;
        }
        if (!found)
        {
            cout << "No complaints found for Citizen ID: " << id << "\n";
        }
        cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
    }

    // Save the complaints to a file
    void saveToFile() const
    {
        ofstream file("files/complaints.txt");
        if (!file)
        {
            cout << "Error opening file for writing.\n";
            return;
        }
        ComplaintNode *current = front;
        while (current != nullptr)
        {
            file << current->data.complaintId << "," << current->data.citizenId << "," << current->data.location << "," << current->data.description << ","
                 << current->data.status << "," << (current->data.isResolved ? "1" : "0") << "\n"; // Modify this line
            current = current->next;
        }
        file.close();
    }

    // Load the complaints from a file
    void loadFromFile()
    {
        ifstream file("files/complaints.txt");
        if (!file)
        {
            cout << "File reading ke liye open karte waqt error.\n";
            return;
        }
        string complaintId, citizenId, location, description, status;
        bool isResolved;
        while (getline(file, complaintId, ',') &&
               getline(file, citizenId, ',') &&
               getline(file, location, ',') &&
               getline(file, description, ',') &&
               getline(file, status, ',') &&
               file >> isResolved)
        {
            file.ignore(); // Newline ko skip karo
            Complaint complaint(citizenId, location, description, status, isResolved);
            complaint.complaintId = complaintId; // File se complaint ID set karo
            enqueue(complaint);
        }
        file.close();
    }

    // Display all complaints in the queue
    bool display() const
    {
        if (isEmpty())
        {
            cout << "No complaints in the queue.\n";
            return false;
        }
        ComplaintNode *sortedList = nullptr;
        // Traverse the original linked list and insert each complaint in sorted order
        ComplaintNode *current = front;
        while (current != nullptr)
        {
            ComplaintNode *nextNode = current->next;
            current->next = nullptr;
            // Insert `current` into `sortedList` in priority order
            if (sortedList == nullptr || compareComplaints(current->data, sortedList->data))
            {
                current->next = sortedList;
                sortedList = current;
            }
            else
            {
                ComplaintNode *temp = sortedList;
                while (temp->next != nullptr && !compareComplaints(current->data, temp->next->data))
                {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = nextNode;
        }
        // Print the sorted complaints in tabular format
        cout << "\n--- Display Complaints ---\n";
        cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "| Complaint ID | Citizen ID | Location      | Description                                                  | Status     | Resolved |\n";
        cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
        ComplaintNode *displayNode = sortedList;
        while (displayNode != nullptr)
        {
            cout << "| " << setw(12) << displayNode->data.complaintId
                 << " | " << setw(10) << displayNode->data.citizenId
                 << " | " << setw(13) << displayNode->data.location
                 << " | " << setw(60) << displayNode->data.description
                 << " | " << setw(10) << displayNode->data.status
                 << " | " << setw(8) << (displayNode->data.isResolved ? "Yes" : "No") << " |\n";
            displayNode = displayNode->next;
        }
        cout << "------------------------------------------------------------------------------------------------------------------------------------\n";
        return true;
    }

    // Comparison function to determine priority
    bool compareComplaints(const Complaint &a, const Complaint &b) const
    {
        int statusPriorityA = (a.status == "Critical") ? 3 : (a.status == "Alert" ? 2 : 1);
        int statusPriorityB = (b.status == "Critical") ? 3 : (b.status == "Alert" ? 2 : 1);
        if (statusPriorityA != statusPriorityB)
            return statusPriorityA > statusPriorityB;

        return a.isResolved == false && b.isResolved == true;
    }

    // Update the resolved status of a complaint by its ID
    void updateIsResolvedByComplaintId(const string &complaintId)
    {
        ComplaintNode *current = front;
        bool found = false;
        while (current != nullptr)
        {
            if (current->data.complaintId == complaintId)
            {
                current->data.isResolved = !current->data.isResolved;
                found = true;
                cout << "Complaint ID: " << complaintId << " resolved status updated to "
                     << (current->data.isResolved ? "true" : "false") << ".\n";
                break;
            }
            current = current->next;
        }
        if (!found)
        {
            cout << "Complaint with ID: " << complaintId << " not found.\n";
        }
    }
};

#endif // COMPLAINT_H