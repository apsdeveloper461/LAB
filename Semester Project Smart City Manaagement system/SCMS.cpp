// main.cpp
#include <iostream>
#include <fstream>
#include "Citizen.h"
#include "Graph.h"
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include "History.h"
#include "Complaint.h"
#include <windows.h> // Move this line to the end of the includes list

using namespace std;

// Global objects
CitizenBST citizenBST;
Graph graph;
History CitizenPerformOperationHistory;
ComplaintQueue complaintsQueue;

// Function prototypes
void showLoading(int duration);
void pressAnyKeyToContinue();
void displayMainMenu();
// citizen menus:
void adminMenu();
void citizenMenu(const Citizen &citzen);

// admin menus:
bool authenticateAdmin();
void manageStops();
void manageCitizens();
void manageRoads();
void manageComplaints();
int main()
{
    // Load data from files
    citizenBST.loadData();
    graph.loadFromFile();
    complaintsQueue.loadFromFile();
    cout << "------Complaints------" << endl;
    complaintsQueue.display();
    cout << "--- Display Citizens ---" << endl;
    citizenBST.displayCitizens();
    cout << "--- Display Roads ---" << endl;
    graph.displayRoads();

    char choice;
    while (true)
    {
        displayMainMenu();
        cout << "\tEnter your choice: ";
        choice = getche();
        cout << endl;
        if (choice == '1')
        {
            if (authenticateAdmin())
            {
                cout << "Authenticate Successfully! " << endl;
                showLoading(3);
                system("cls");
                adminMenu();
            }
            else
            {
                cout << "Authentication failed. Please try again.\n";
                pressAnyKeyToContinue();
            }
        }
        else if (choice == '2')
        {
            string citizenID, citizenPassword;
            cin.ignore();
            cout << "Enter Citizen ID: ";
            getline(cin, citizenID);
            cout << "Enter Password: ";
            getline(cin, citizenPassword);
            CitizenNode *n = citizenBST.findCitizen(citizenID, citizenPassword);
            if (n != nullptr)
            {
                // n->citizenData.name
                cout << "Login successful. Welcome, " << n->citizenData.name << "!\n";
                showLoading(3);
                system("cls");
                citizenMenu(n->citizenData);
            }
            else
            {
                cout << "Authentication failed. Please try again.\n";
                pressAnyKeyToContinue();
            }
        }
        else if (choice == '3')
        {
            cout << "Exiting the system. Goodbye!\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
            pressAnyKeyToContinue();
        }
    }

    graph.saveToFile();
    citizenBST.saveToFile();
    complaintsQueue.saveToFile();
    return 0;
}

// Function to display the main menu
void displayMainMenu()
{

    cout << endl;
    showLoading(3);
    system("cls");
    cout << "*****************************************************************\n";
    cout << "*                                                               *\n";
    cout << "*                  Welcome to the Smart City                    *\n";
    cout << "*                       Management System                       *\n";
    cout << "*                                                               *\n";
    cout << "*****************************************************************\n";
    cout << "*                                                               *\n";
    cout << "*                       1. Login as Admin                       *\n";
    cout << "*                       2. Login as Citizen                     *\n";
    cout << "*                       3. Exit                                 *\n";
    cout << "*                                                               *\n";
    cout << "*****************************************************************\n";
}

// Function to display the citizen menu
void citizenMenu(const Citizen &citizen)
{
    char choice;

    while (true)
    {
        cout << "\n*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                  Welcome, " << citizen.name << "!                             *\n";
        cout << "*                                                               *\n";
        cout << "*                  Enjoy your experience in the                 *\n";
        cout << "*                  Smart City Management System                 *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                1. Submit a Complaint                          *\n";
        cout << "*                2. Display all Complaint                       *\n";
        cout << "*                3. Display all Stops                           *\n";
        cout << "*                4. Display all Roads b/w stops                 *\n";
        cout << "*                5. Find the shortest path b/w two stops        *\n";
        cout << "*                6. Save Complaints to File                     *\n";
        cout << "*                7. Logout                                      *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";
        cout << "Enter choice: ";
        choice = getche();

        cout << endl;
        if (choice == '1')
        {
            string location, description, status;
            cout << "Enter Location: ";
            // cin.ignore();
            getline(cin, location);
            cout << "Enter Description: ";
            getline(cin, description);
            char s;
            cout << "Enter Status('C' for Critical message/report ,  'A' for Alert message , 'S' for simple): ";
            s = getche();
            cout << endl;
            if (s == 'C' || s == 'c')
            {
                status = "Critical";
            }
            else if (s == 'A' || s == 'a')
            {
                status = "Alert";
            }
            else
            {
                status = "Simple";
            }
            complaintsQueue.enqueue(Complaint(citizen.citizenID, location, description, status));
            showLoading(2);
            cout << "Complaint submitted successfully.\n";
        }
        else if (choice == '2')
        {
            showLoading(2);
            complaintsQueue.findAndDisplayByCitizenId(citizen.citizenID);
        }
        else if (choice == '3')
        {
            graph.displayStops();
        }
        else if (choice == '4')
        {
            cout << "\n--- Display Roads ---" << endl;
            graph.displayRoads();
        }
        else if (choice == '5')
        {
            showLoading(2);
            graph.displayStops();
            cout << endl
                 << endl;
            string startStopID, endStopID;
            cout << "Enter Start Stop ID: ";
            cin >> startStopID;
            cin.ignore(10000, '\n'); // Add this line
            cout << "Enter End Stop ID: ";
            cin >> endStopID;
            cin.ignore(10000, '\n');
            graph.dijkstra(startStopID, endStopID);
        }
        else if (choice == '6')
        {
            complaintsQueue.saveToFile();
            cout << "Complaints saved to file.\n";
        }
        else if (choice == '7')
        {
            return;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
        cout << endl;
        pressAnyKeyToContinue();
    }
}

// Function to display the admin menu
void adminMenu()
{
    char choice;

    while (true)
    {
        cout << "*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                  Welcome to the Admin Panel                   *\n";
        cout << "*                                                               *\n";
        cout << "*                  Manage the Smart City with                   *\n";
        cout << "*                  Efficiency and Ease                          *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                       1. Manage Stops                         *\n";
        cout << "*                       2. Manage Citizens                      *\n";
        cout << "*                       3. Manage Roads                         *\n";
        cout << "*                       4. Handle Complaints                    *\n";
        cout << "*                       5. Find Minimum Distance Between Stops  *\n";
        cout << "*                       6. Save To files                        *\n";
        cout << "*                       7. Logout                               *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";
        cout << "\tEnter choice: ";
        choice = getche();
        cout << endl;
        if (choice == '1')
        {
            showLoading(2);
            system("cls");
            manageStops();
        }
        else if (choice == '2')
        {
            showLoading(2);
            system("cls");
            manageCitizens();
        }
        else if (choice == '3')
        {
            showLoading(2);
            system("cls");
            manageRoads();
        }
        else if (choice == '4')
        {
            showLoading(2);
            system("cls");
            manageComplaints();
        }
        else if (choice == '5')
        {
            showLoading(2);
            graph.displayStops();
            cout << endl
                 << endl;
            string startStopID, endStopID;
            cout << "Enter Start Stop ID: ";
            cin >> startStopID;
            cin.ignore(10000, '\n');
            cout << "Enter End Stop ID: ";
            cin >> endStopID;
            cin.ignore(10000, '\n');
            graph.dijkstra(startStopID, endStopID);
        }
        else if (choice == '6')
        {
            citizenBST.saveToFile();
            graph.saveToFile();
            complaintsQueue.saveToFile();
            cout << "Data saved to files.\n";
        }
        else if (choice == '7')
        {
            system("cls");
            return;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
        pressAnyKeyToContinue();
    }
}

// Function to authenticate admin
bool authenticateAdmin()
{
    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;

    // Replace with actual admin credentials check
    return (username == "admin" && password == "password");
}

// Function to manage stops
void manageStops()
{
    char choice;
    while (true)
    {
        cout << "\n*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                        Manage Stops                           *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                       1. Add a Stop                           *\n";
        cout << "*                       2. View All Stops                       *\n";
        cout << "*                       3. Delete a Stop                        *\n";
        cout << "*                       4. Back to Admin Menu                   *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";
        cout << "\tEnter choice: ";
        choice = getche();
        cout << endl;
        if (choice == '1')
        {
            // showLoading(2);
            string stopID, name, location;
            cout << "Enter Stop ID: ";
            cin >> stopID;
            cin.ignore(10000, '\n');
            cout << "Enter Stop Name: ";
            getline(cin, name);
            cout << "Enter Stop Location: ";
            getline(cin, location);
            showLoading(2);
            graph.addStop(stopID, name, location);
            // cout << "Stop added successfully.\n";
        }
        else if (choice == '2')
        {
            showLoading(2);
            // cout << "--- Display Stops ---" << endl;
            graph.displayStops();
        }
        else if (choice == '3')
        {
            showLoading(2);
            // cout << "--- Display Stops ---" << endl;
            graph.displayStops();
            cout << endl;
            string stopID;
            cout << "Enter Stop ID to delete: ";
            cin >> stopID;
            cin.ignore(10000, '\n');
            showLoading(2);
            graph.deleteStop(stopID);
        }
        else if (choice == '4')
        {
            system("cls");
            return;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
        pressAnyKeyToContinue();
    }
}

// Function to manage roads
void manageRoads()
{
    char choice;
    while (true)
    {
        cout << "\n*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                        Manage Roads                           *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                       1. Add a Road                           *\n";
        cout << "*                       2. View All Roads                       *\n";
        cout << "*                       3. Delete a Road                        *\n";
        cout << "*                       4. Back to Admin Menu                   *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";
        cout << "\tEnter choice: ";
        choice = getche();
        cout << endl;
        if (choice == '1')
        {
                    cout << "----- Select Stops frome here : ";
            graph.displayStops();
            string startStopID, endStopID;
            float distance;
            cin.ignore(10000, '\n');
            cout << "Enter Start Stop ID: ";
            getline(cin, startStopID);
            cout << "Enter End Stop ID: ";
            getline(cin, endStopID);
            cin.ignore(10000, '\n');
            cout << "Enter Distance: ";
            cin >> distance;
            // cin.ignore(10000, '\n');
            showLoading(2);
            graph.addRoad(startStopID, endStopID, distance);
        }
        else if (choice == '2')
        {
            showLoading(2);
            cout << "\n\t\t\t------ Display Roads -------\n";
            graph.displayRoads();
        }
        else if (choice == '3')
        {

            string startStopID, endStopID;
            cout << "----- Select Stops frome here : \n";
            graph.displayStops();
            cin.ignore(10000, '\n');
            cout << "Enter Start Stop ID: ";
            getline(cin, startStopID);
            cout << "Enter End Stop ID: ";
            getline(cin, endStopID);
            // cin.ignore(10000, '\n');
            showLoading(2);
            graph.deleteRoad(startStopID, endStopID);
        }
        else if (choice == '4')
        {
            system("cls");
            return;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
        pressAnyKeyToContinue();
    }
}

// Function to manage citizens
void manageCitizens()
{
    char choice;
    while (true)
    {
        cout << "\n*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                       Manage Citizens                         *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                       1. Add Citizen                          *\n";
        cout << "*                       2. Update Citizen Data                  *\n";
        cout << "*                       3. View All Citizens                    *\n";
        cout << "*                       4. Delete Citizen                       *\n";
        cout << "*                       5. Undo Last Change in citizens data    *\n";
        cout << "*                       6. Back to Admin Menu                   *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";
        cout << "\tEnter choice: ";
        choice = getche();
        cout << endl;
        if (choice == '1')
        {
            string name, id, password;
            float age;
            cin.ignore(10000, '\n');
            cout << "Enter Citizen ID: ";
            getline(cin, id);
            cout << "Enter Citizen Name: ";
            getline(cin, name);
            cout << "Enter Citizen Password: ";
            getline(cin, password);
            cout << "Enter Citizen Age: ";
            cin >> age;
            cin.ignore(10000, '\n');
            showLoading(2);
            Citizen CD(id, name, age, password);
            if (citizenBST.insert(CD))
            {
                cout << "Citizen added successfully.\n";
                CitizenPerformOperationHistory.push(ChangeData(ADD_HISTORY, id, Citizen(), CD));
                cout << "History is empty" << CitizenPerformOperationHistory.isEmpty() << endl;
            }
        }
        else if (choice == '2')
        {
            string citizenID;
            cout << "Enter Citizen ID: ";
            cin >> citizenID;
            cin.ignore(10000, '\n');
            showLoading(2);
            CitizenNode *node = citizenBST.findCitizenWithId(citizenID);
            if (node != nullptr)
            {
                Citizen OldDataOfCitizen = node->citizenData;
                char ch;
                cout << "Do you want to change the name? (y/n): ";
                ch = getche();
                cin.ignore(10000, '\n');
                if (ch == 'y' || choice == 'Y')
                {
                    cout << "Enter new name: ";
                    getline(cin, node->citizenData.name);
                }
                cout << "Do you want to change the age? (y/n): ";
                ch = getche();
                cin.ignore(10000, '\n');
                if (ch == 'y' || ch == 'Y')
                {
                    cout << "Enter new age: ";
                    cin >> node->citizenData.age;
                    cin.ignore(10000, '\n');
                }

                cout << "Do you want to change the password? (y/n): ";
                ch = getche();
                cin.ignore(10000, '\n');
                if (ch == 'y' || ch == 'Y')
                {
                    cin.ignore();
                    cout << "Enter new password: ";
                    getline(cin, node->citizenData.password);
                }
                showLoading(2);
                CitizenPerformOperationHistory.push(ChangeData(UPDATE_HISTORY, citizenID, OldDataOfCitizen, node->citizenData));
                cout << "Citizen update successfully.\n";
            }
            else
            {
                cout << "Citizen not found.\n";
            }
        }
        else if (choice == '3')
        {
            showLoading(2);
            // cout << "--- Display Citizens ---" << endl;
            citizenBST.displayCitizens();
        }
        else if (choice == '4')
        {
            //    showLoading(2);
            // cout << "--- Display Citizens ---" << endl;
            citizenBST.displayCitizens();
            string id;
            cin.ignore(10000, '\n');
            cout << "Enter Citizen ID to delete: ";
            getline(cin, id);
            showLoading(2);
            const CitizenNode *n = citizenBST.findCitizenWithId(id);
            if (n != nullptr)
            {
                cout << "Citizen found.\n";
                Citizen c = n->citizenData;
                citizenBST.deleteCitizen(id);
                cout << "goinf to store data.\n";
                CitizenPerformOperationHistory.push(ChangeData(DELETE_HISTORY, id, c, c));
                cout << "Citizen deleted successfully.\n";
            }
            else
            {
                cout << "Citizen not found.\n";
            }
        }
        else if (choice == '5')
        {
            showLoading(2);
            CitizenPerformOperationHistory.undoChange(citizenBST);
        }
        else if (choice == '6')
        {
            system("cls");
            return;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
        pressAnyKeyToContinue();
    }
}

// Function to manage complaints
void manageComplaints()
{
    char choice;
    while (true)
    {
        cout << "\n*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                       Manage Complaints                       *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";
        cout << "*                                                               *\n";
        cout << "*                       1. Update Complaint resolved Status     *\n";
        cout << "*                       2. View All Complaints                  *\n";
        cout << "*                       3. View Complaints by Citizen ID        *\n";
        cout << "*                       4. Back to Admin Menu                   *\n";
        cout << "*                                                               *\n";
        cout << "*****************************************************************\n";
        cout << "\tEnter choice: ";
        choice = getche();
        cout << endl;
        if (choice == '1')
        {
            showLoading(2);
            if(complaintsQueue.display()){  // if data in queue means there is some data , then only we can update

            string complaintId;
            cin.ignore(10000, '\n'); // Add this line
            cout << "Enter Complaint ID: ";
            getline(cin, complaintId);
            cout << "You enter this :" << complaintId << endl;
            showLoading(2);
            complaintsQueue.updateIsResolvedByComplaintId(complaintId);
            }
        }
        else if (choice == '2')
        {
            showLoading(2);
            // cout << "--- Display Complaints ---" << endl;
            complaintsQueue.display();
        }
        else if (choice == '3')
        {
            showLoading(2);
            citizenBST.displayCitizens();
            string id;
            cin.ignore(10000, '\n'); // Uncomment this line
            cout << "Enter Citizen ID: ";
          getline(cin, id);
            showLoading(2);
            complaintsQueue.findAndDisplayByCitizenId(id);
        }
        else if (choice == '4')
        {
            system("cls");
            return;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
        pressAnyKeyToContinue();
    }
}

// Function to show loading animation
void showLoading(int duration)
{
    for (int i = 0; i < duration; ++i)
    {
        cout << "Loading";
        for (int j = 0; j < 3; ++j)
        {
            cout << ".";
            Sleep(333); // Sleep for 333 milliseconds
        }
        cout << "\r"; // Return to the beginning of the line
        cout.flush(); // Ensure the output is flushed
    }
    cout << endl;
}

// Function to prompt user to press any key to continue
void pressAnyKeyToContinue()
{
    cout << "Press any key to continue...";
    getch();
    cout << endl;
    system("cls");
}