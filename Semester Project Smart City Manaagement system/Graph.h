#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits> // Add this line
#include <cstring> // For memset
#include <set>
// #include <cfloat> // Add this line
#include <iomanip> 

using namespace std;

//////////////////////////////
// Graph Data Structures
//////////////////////////////

class RoadNode
{
public:
    string destinationStopID;
    float distance;
    RoadNode *next;
    RoadNode(string stopID, float dist) : destinationStopID(stopID), distance(dist), next(nullptr) {}
};

class StopNode
{
public:
    string stopID;
    string name;
    string location;
    RoadNode *roadList;
    StopNode *next; // Add a next pointer for StopNode traversal

    StopNode(string id, string stopName, string loc)
        : stopID(id), name(stopName), location(loc), roadList(nullptr), next(nullptr) {}
    void display() const
    {
        cout << "\nstopID:  " << stopID << ", Name:  " << name << ", location: " << location;
    }
};

class Graph
{
private:
    StopNode *head;
    StopNode* getStopNode(const string& stopID) const {
        StopNode* node = head;
        while (node) {
            if (node->stopID == stopID) {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }
    bool stopExists(const string &stopID) const
    {
        StopNode *temp = head;
        while (temp)
        {
            if (temp->stopID == stopID)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // bool roadExists(const string &startStopID, const string &endStopID) const
    // {
    //     StopNode *temp = head;
    //     while (temp)
    //     {
    //         if (temp->stopID == startStopID)
    //         {
    //             RoadNode *roadTemp = temp->roadList;
    //             while (roadTemp)
    //             {
    //                 if (roadTemp->destinationStopID == endStopID)
    //                 {
    //                     return true;
    //                 }
    //                 roadTemp = roadTemp->next;
    //             }
    //         }
    //         temp = temp->next;
    //     }
    //     return false;
    // }

public:
    Graph() : head(nullptr) {}

    // Add a road between two stops with a given distance
    void addRoad(const string &startStopID, const string &endStopID, float distance)
    {
        if (!stopExists(startStopID) || !stopExists(endStopID))
        {
            cout << "One or both stop IDs do not exist. Please check and try again.\n";
            return;
        }
        RoadNode *newConnection1 = new RoadNode(endStopID, distance);
        RoadNode *newConnection2 = new RoadNode(startStopID, distance);

        StopNode *temp = head;
        while (temp)
        {
            if (temp->stopID == startStopID)
            {
                newConnection1->next = temp->roadList;
                temp->roadList = newConnection1;
            }
            else if (temp->stopID == endStopID)
            {
                newConnection2->next = temp->roadList;
                temp->roadList = newConnection2;
            }
            temp = temp->next; // Use next pointer for traversal
        }
        cout << "Road added successfully.\n";
    }

    // Delete a road between two stops
    void deleteRoad(const string &startStopID, const string &endStopID)
    {
        StopNode *temp = head;

        // Delete road from startStopID to endStopID
        while (temp != nullptr)
        {
            if (temp->stopID == startStopID)
            {
                RoadNode *roadTemp = temp->roadList;
                RoadNode *prevRoad = nullptr;

                while (roadTemp != nullptr)
                {
                    if (roadTemp->destinationStopID == endStopID)
                    {
                        if (prevRoad == nullptr)
                        {
                            temp->roadList = roadTemp->next;
                        }
                        else
                        {
                            prevRoad->next = roadTemp->next;
                        }
                        delete roadTemp;
                        break;
                    }
                    prevRoad = roadTemp;
                    roadTemp = roadTemp->next;
                }
            }
            temp = temp->next;
        }

        // Reset temp to head to delete road from endStopID to startStopID
        temp = head;

        // Delete road from endStopID to startStopID
        while (temp != nullptr)
        {
            if (temp->stopID == endStopID)
            {
                RoadNode *roadTemp = temp->roadList;
                RoadNode *prevRoad = nullptr;

                while (roadTemp != nullptr)
                {
                    if (roadTemp->destinationStopID == startStopID)
                    {
                        if (prevRoad == nullptr)
                        {
                            temp->roadList = roadTemp->next;
                        }
                        else
                        {
                            prevRoad->next = roadTemp->next;
                        }
                        delete roadTemp;
                        break;
                    }
                    prevRoad = roadTemp;
                    roadTemp = roadTemp->next;
                }
            }
            temp = temp->next;
        }

        cout << "Done.\n";
    }

    // Display all roads in the graph
    void displayRoads() const
    {
        StopNode *node = head;

        while (node)
        {
            cout << "Stop " << node->stopID << ": ";
            RoadNode *connection = node->roadList;
            while (connection)
            {
                cout << "(Connected to " << connection->destinationStopID << " with Distance " << connection->distance << " km) -> ";
                connection = connection->next;
            }
            cout << endl;
            node = node->next; // Use next pointer for traversal
        }
    }
   
    // Add a new stop to the graph
    void addStop(const string &stopID, const string &name, const string &location)
    {
        StopNode *newNode = new StopNode(stopID, name, location);

        if (!head)
        {
            head = newNode;
            return;
        }

        StopNode *temp = head;
        while (temp->next)
        { // Use next pointer for traversa
        if(temp->stopID == stopID){
            cout << "Stop already exists.\n";
            return;
        }
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Delete a stop and all associated roads from the graph
    void deleteStop(const string &stopID)
    {
        StopNode *temp = head;
        StopNode *prev = nullptr;

        // Find the stop to delete
        while (temp != nullptr && temp->stopID != stopID)
        {
            prev = temp;
            temp = temp->next;
        }

        // If stop not found
        if (temp == nullptr)
        {
            cout << "Stop not found.\n";
            return;
        }

        // Remove the stop from the list
        if (prev == nullptr)
        {
            head = temp->next;
        }
        else
        {
            prev->next = temp->next;
        }

        // Delete all roads connected to this stop
        RoadNode *roadTemp = temp->roadList;
        while (roadTemp != nullptr)
        {
            RoadNode *nextRoad = roadTemp->next;
            delete roadTemp;
            roadTemp = nextRoad;
        }

        delete temp;

        // Remove all roads pointing to this stop
        temp = head;
        while (temp != nullptr)
        {
            RoadNode *roadTemp = temp->roadList;
            RoadNode *prevRoad = nullptr;
            while (roadTemp != nullptr)
            {
                if (roadTemp->destinationStopID == stopID)
                {
                    if (prevRoad == nullptr)
                    {
                        temp->roadList = roadTemp->next;
                    }
                    else
                    {
                        prevRoad->next = roadTemp->next;
                    }
                    delete roadTemp;
                    break;
                }
                prevRoad = roadTemp;
                roadTemp = roadTemp->next;
            }
            temp = temp->next;
        }

        cout << "Stop and all associated roads deleted successfully.\n";
    }

    // Display all stops in the graph
    void displayStops() const
    {
        cout << "\n\t\t--- Display Stops ---" << endl;
        cout << "------------------------------------------------------\n";
        cout << "| Stop ID | Name                   | Location       |\n";
        cout << "------------------------------------------------------\n";
        StopNode *node = head;
        while (node)
        {
            cout << "| " << setw(7) << node->stopID << " | " << setw(22) << node->name << " | " << setw(14) << node->location << " |\n";
            node = node->next;
        }
        cout << "------------------------------------------------------\n";
    }

    // Save the graph data to files
    void saveToFile() 
    {
        // Save stops
        ofstream stopsFile("files/stops.txt");
        if (stopsFile.is_open())
        {
            StopNode *node = head;
            while (node)
            {
                stopsFile << node->stopID << "," << node->name << "," << node->location << endl;
                node = node->next; // Use next pointer for traversal
            }
            stopsFile.close();
        }

        // Save roads
        ofstream roadsFile("files/roads.txt");
        if (roadsFile.is_open())
        {
            set<pair<string, string>> savedRoads; // To track saved roads
            StopNode *node = head;
            while (node)
            {
                RoadNode *connection = node->roadList;
                while (connection)
                {
                    pair<string, string> road1 = make_pair(node->stopID, connection->destinationStopID);
                    pair<string, string> road2 = make_pair(connection->destinationStopID, node->stopID);

                    // Check if the road has already been saved
                    if (savedRoads.find(road1) == savedRoads.end() && savedRoads.find(road2) == savedRoads.end())
                    {
                        roadsFile << node->stopID << "," << connection->destinationStopID << "," << connection->distance << endl;
                        savedRoads.insert(road1);
                    }

                    connection = connection->next;
                }
                node = node->next; // Use next pointer for traversal
            }
            roadsFile.close();
        }
    }
   
    // Load the graph data from files
    void loadFromFile()
    {
        ifstream stopsFile("files/stops.txt");
        if (stopsFile.is_open())
        {
            string stopID, name, location;

            // Read stops
            while (getline(stopsFile, stopID, ',') && getline(stopsFile, name, ',') && getline(stopsFile, location))
            {
                addStop(stopID, name, location);
            }
            stopsFile.close();
        }

        ifstream roadsFile("files/roads.txt");
        if (roadsFile.is_open())
        {
            string startStopID, destinationStopID;
            float distance;

            // Read roads
            while (getline(roadsFile, startStopID, ',') && getline(roadsFile, destinationStopID, ',') && roadsFile >> distance)
            {
                addRoad(startStopID, destinationStopID, distance);
                roadsFile.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            roadsFile.close();
        }
    }

    // Find the shortest path between two stops using Dijkstra's algorithm
    void dijkstra(const string& start, const string& end) const {
        // Check karo agar start ya end stop exist karta hai
        if (!stopExists(start) || !stopExists(end)) {
            cout << "Start ya end stop exist nahi karta. Barae meherbani check karo aur dobara try karo.\n";
            return;
        }

        const int MAX_STOPS = 100; // Isay zarurat ke mutabiq adjust karo
        float distances[MAX_STOPS];
        bool visited[MAX_STOPS];
        string stopIDs[MAX_STOPS];
        int stopCount = 0;

        // Arrays ko initialize karo
        StopNode* node = head;
        while (node) {
            stopIDs[stopCount] = node->stopID;
            distances[stopCount] = (node->stopID == start) ? 0 : 999999; // FLT_MAX
            visited[stopCount] = false;
            stopCount++;
            node = node->next;
        }

        // Dijkstra ka algorithm
        for (int i = 0; i < stopCount; ++i) {
            // Unvisited stop ko dhundo jo sabse choti distance rakhta ho
            int minIndex = -1;
            for (int j = 0; j < stopCount; ++j) {
                if (!visited[j] && (minIndex == -1 || distances[j] < distances[minIndex])) {
                    minIndex = j;
                }
            }

            if (minIndex == -1) break; // Sab reachable stops visit ho chuke hain

            visited[minIndex] = true;
            string currentStopID = stopIDs[minIndex];
            StopNode* currentNode = getStopNode(currentStopID);

            // Adjacent stops ke distances ko update karo
            RoadNode* connection = currentNode->roadList;
            while (connection) {
                for (int j = 0; j < stopCount; ++j) {
                    if (stopIDs[j] == connection->destinationStopID) {
                        float newDist = distances[minIndex] + connection->distance;
                        if (newDist < distances[j]) {
                            distances[j] = newDist;
                        }
                        break;
                    }
                }
                connection = connection->next;
            }
        }

        // Shortest distances ko display karo
        cout << "Shortest distances from " << start << ":\n";
        for (int i = 0; i < stopCount; ++i) {
            if (stopIDs[i] == end) {
                cout << "To " << stopIDs[i] << ": " << distances[i] << " km\n";
            }
        }
    }

};

#endif // GRAPH_H
