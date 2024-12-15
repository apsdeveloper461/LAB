#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include "Citizen.h"
using namespace std;

// Types of changes we can track
enum ChangeType
{
    ADD_HISTORY,
    DELETE_HISTORY,
    UPDATE_HISTORY
};

// Class to store change data
class ChangeData
{
public:
    ChangeType type;
    string id;
    Citizen oldData;
    Citizen newData;

    ChangeData(ChangeType type, const string &id, const Citizen &oldData, const Citizen &newData) : type(type), id(id), oldData(oldData), newData(newData) {}
    // Change(ChangeType type, const string& id, const Citizen& newData): type(type), id(id),oldData(newData),newData(newData){}
};

// Node class for the stack
class Node
{
public:
    ChangeData data;
    Node *next;

    Node(const ChangeData &data) : data(data), next(nullptr) {}
};

// Stack class to keep history of changes
class History
{
private:
    Node *top;

public:
    // Constructor
    History() : top(nullptr) {}

    // Destructor
    ~History()
    {
        while (top != nullptr)
        {
            Node *temp = top;
            top = top->next;
            delete temp;
        }
    }

    // Function to push new change to the stack
    void push(const ChangeData &ChangeData)
    {
        Node *newNode = new Node(ChangeData);
        newNode->next = top;
        top = newNode;
        top->data.newData.display(); // Show new data
    }

    // Function to undo last change
    ChangeData* undoChange(CitizenBST &bst)
    {
        if (top == nullptr)
        {
            cout << "No previous History" << endl;
            return nullptr;// Return default change
        }
        Node *temp = top;
        ChangeData lastChange = top->data;
     

        // Undo the last change in the BST
        switch (lastChange.type)
        {
        case ADD_HISTORY:
        {
            char ch;
            cout << "\nDo you want to ADD operation for  citizenID: " << lastChange.id << " ('y 'for yes)" << endl;
            ch = getche();
            cout << endl;
            if (ch == 'Y' || ch == 'y')
            {
                bst.deleteCitizen(lastChange.id);
                cout << "Undo ADD operation for ID: " << lastChange.id << endl;
            }
            else
            {
                cout << "Undo ADD operation for ID: " << lastChange.id << " not performed" << endl;
                 return nullptr;
            }
            break;
        }
        case DELETE_HISTORY:
        {
            char ch;
            cout << "\nDo you want to DELETE operation for  citizenID: " << lastChange.id << " ('y 'for yes)" << endl;
            ch = getche();
            cout << endl;
            if (ch == 'Y' || ch == 'y')
            {
                bst.insert(lastChange.oldData);
                cout << "Undo DELETE operation for ID: " << lastChange.id << endl;
            }
            else
            {
                cout << "Undo DELETE operation for ID: " << lastChange.id << " not performed" << endl;
                return nullptr;
            }
            break;
        }
        case UPDATE_HISTORY:
        {
            char ch;
            cout << "\nDo you want to UPDATE operation for  citizenID: " << lastChange.id << " ('y 'for yes)" << endl;
            ch = getche();
            cout << endl;
            if (ch == 'Y' || ch == 'y')
            {

                bst.updateCitizen(bst.findCitizenWithId(lastChange.id), lastChange.oldData);
                cout << "Undo UPDATE operation for ID: " << lastChange.id << endl;
            }
            else
            {
                cout << "Undo UPDATE operation for ID: " << lastChange.id << " not performed" << endl;
                 return nullptr;
            }
            break;
        }
        }
         top = top->next;
        delete temp;
        return &lastChange;
    }

    // Function to check if stack is empty
    bool
    isEmpty() const
    {
        return top == nullptr;
    }
};

#endif // STACK_H