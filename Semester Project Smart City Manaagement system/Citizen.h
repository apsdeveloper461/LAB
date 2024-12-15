#ifndef CITIZEN_H
#define CITIZEN_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits> 
#include <algorithm>
#include <cctype>
#include <locale>
#include <iomanip>
using namespace std;

class Citizen
{
public:
    string citizenID;
    string name;
    float age;
    string password;
    // Citizen(const Citi)
    Citizen(){}
    Citizen(string cid, string name, float age, string pass) : citizenID(cid), name(name), age(age), password(pass) {}
    void display() const
    {
cout << "| " << left << setw(15) << citizenID << "| " << setw(27) << name << "| " << setw(10) << age << "| " << setw(20) << password << "|\n";

    }
};

class CitizenNode
{
public:
    Citizen citizenData;
    CitizenNode *left;
    CitizenNode *right;

    CitizenNode(const Citizen &data) : citizenData(data), left(nullptr), right(nullptr) {}
};

class CitizenBST
{
private:
    CitizenNode *root;
    string &ltrim(string &s) {
    s.erase(s.begin(),find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return s;
}

    CitizenNode* findCitizenWithRoot(CitizenNode *node, const string &citizenID) const
    {
    
        if (node == nullptr)
        {
            // cout << "Citizen not found beacuse nullptr" << endl;
            return nullptr;
        }

        // node->citizenData.display();
    //   cout  << ":"<< node->citizenData.citizenID << ":" << citizenID << ":" << (node->citizenData.citizenID==citizenID)<< endl;
        if (node->citizenData.citizenID == citizenID)
        {
            // cout << "Match found" << endl;
            return node;
        }
        if (citizenID < node->citizenData.citizenID)
        {
            return findCitizenWithRoot(node->left, citizenID);
        }
        else
        {
            return findCitizenWithRoot(node->right, citizenID);
        }
    }

    bool insert(CitizenNode *&node, const Citizen &citizenData)
    {
        if (node == nullptr){
            node = new CitizenNode(citizenData);
            return true;
        }
        else if (citizenData.citizenID < node->citizenData.citizenID)
            insert(node->left, citizenData);
        else if (citizenData.citizenID > node->citizenData.citizenID)
            insert(node->right, citizenData);
        else{
            cout << "Citizen already exists." << endl;
            return false;
        }
        
    }

    void display(CitizenNode *node) const
    {
        if (node)
        {
            display(node->left);
            node->citizenData.display();
            display(node->right);
        }
    }

    CitizenNode* deleteCitizenWithRoot(CitizenNode* node, const string& citizenID) {
        if (!node) return nullptr;
        if (citizenID < node->citizenData.citizenID) {
            node->left = deleteCitizenWithRoot(node->left, citizenID);
        } else if (citizenID > node->citizenData.citizenID) {
            node->right = deleteCitizenWithRoot(node->right, citizenID);
        } else {
            if (!node->left) {
                CitizenNode* rightChild = node->right;
                delete node;
                return rightChild;
            } else if (!node->right) {
                CitizenNode* leftChild = node->left;
                delete node;
                return leftChild;
            } else {
                CitizenNode* minNode = findMin(node->right);
                node->citizenData = minNode->citizenData;
                node->right = deleteCitizenWithRoot(node->right, minNode->citizenData.citizenID);
            }
        }
        return node;
    }

      CitizenNode* findMin(CitizenNode* node) const {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

public:
CitizenBST() : root(nullptr) {}

    CitizenNode *findCitizen(const string &citizenID, const string &password) const
    {
        CitizenNode *n = findCitizenWithRoot(root, citizenID);
        if (n != nullptr && n->citizenData.password == password)
        {
            return n;
        }
        return nullptr;
    }
     CitizenNode *findCitizenWithId(const string &citizenID) const
    {
        return findCitizenWithRoot(root, citizenID);
    }


     void deleteCitizen(const string& citizenID) {
            root = deleteCitizenWithRoot(root, citizenID);
    }

    bool insert(const Citizen &citizenData)
    {
        return insert(root, citizenData);
    }
   

        
    void updateCitizen(CitizenNode* node, const Citizen& newData) {
        if (node) {
            node->citizenData = newData;
        }
    }

    void displayCitizens() const
    {
        cout << "\n---  Display Citizens ---" << endl;
        cout << "---------------------------------------------------------------------------------\n";
cout << "| Citizen ID     | Name                       | Age       | Password            |\n";
cout << "---------------------------------------------------------------------------------\n";
        display(root);
        
cout << "---------------------------------------------------------------------------------\n";
    }

    void save(CitizenNode *node, ofstream &file) const
    {
        if (node)
        {
            save(node->left, file);
            file << node->citizenData.citizenID << "," << node->citizenData.name<< "," << node->citizenData.password << "," << node->citizenData.age << endl;
            save(node->right, file);
        }
    }

    
    void saveToFile() const
    {
        ofstream file("files/citizens.txt");
        if (file.is_open())
        {
            save(root, file);
            file.close();
        }
    }

    void loadData()
    {
        ifstream citizensFile("files/citizens.txt");
        if (citizensFile.is_open())
        {
            cout << "read data from file" << endl;  
            string citizenID, name, password;
            float age;
            // citizensFile.ignore();
            while (getline(citizensFile, citizenID, ',') &&
                   getline(citizensFile, name, ',') &&
                   getline(citizensFile, password, ',') &&
                   citizensFile >> age)
            {
                // if(cite)
                citizenID = ltrim(citizenID);
                cout << citizenID << "   " << name << "   " << age << "   " << password << endl;
                Citizen citizen(citizenID, name, age, password);
                this->insert(citizen);
            }
            citizensFile.close();
        }
        else
        {
            cout << "error : in opening file citizens";
        }
    }
};

#endif