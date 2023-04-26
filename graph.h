// Timer: https://cplusplus.com/reference/chrono/steady_clock/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <valarray>
#include <chrono>
#include <unordered_map>

using namespace std;

class Graph {
public:
    Graph();
    void addEdge(int u, int v);
    void createEdges();
    void DFS(string county, string state, int userOption);
    void DFSUtil(int u, vector<bool> &visited);
    void otherCountiesDFS(int u, vector<bool> &visited);
    void BFS(string county, string state, int userOption);
    void otherCountiesBFS(queue<int>q, vector<bool> &visited);
    bool checkInput(string county, string, bool check);

    // create a map to store node indices for each county
    unordered_map<string, int> countyIndices;
    vector<pair<string,string>> counties;
    vector<vector<string>> data;
    unordered_map<string, vector<int>> stateMap;
    vector<string> dataLabels;


private:
    // Adjacency list representation of the graph
    vector<vector<int>> adjList;
};


Graph::Graph() {
    // read file to count number of counties
    ifstream file("Project3/county_demographics.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    // ignore first line with titles
    string line;
    getline(file, line);

    // initialize count to number of counties already added to graph
    int count = 0;
    string prevState = "";  // new variable to keep track of previous state

    string valueStr;
    string key;

    // iterate through file and add data to graph
    while (getline(file, line)) {
        // extract data from line
        stringstream ss(line);
        string countyName, stateName;
        getline(ss, countyName, ',');
        getline(ss, stateName, ',');
        key = countyName + ", " + stateName;

        // add county to graph if not already added
        if (countyIndices.find(key) == countyIndices.end()) {
            // reset count for new state
            if (stateName != prevState) {
                prevState = stateName;
            }
            countyIndices[key] = count++;
            counties.push_back({countyName,stateName});
            data.push_back(vector<string>());
            stateMap[stateName].push_back(count - 1);
        }

        // add demographic data to graph

        while (getline(ss, valueStr, ',')) {
            data[count - 1].push_back(valueStr);
        }
    }

    // initialize data labels
    dataLabels.push_back("Age.Percent 65 and Older");
    dataLabels.push_back("Age.Percent Under 18 Years");
    dataLabels.push_back("Age.Percent Under 5 Years");
    dataLabels.push_back("Education.Bachelor's Degree or Higher");
    dataLabels.push_back("Education.High School or Higher");
    dataLabels.push_back("Employment.Nonemployer Establishments");
    dataLabels.push_back("Ethnicities.American Indian and Alaska Native Alone");
    dataLabels.push_back("Ethnicities.Asian Alone");
    dataLabels.push_back("Ethnicities.Black Alone");
    dataLabels.push_back("Ethnicities.Hispanic or Latino");
    dataLabels.push_back("Ethnicities.Native Hawaiian and Other Pacific Islander Alone");
    dataLabels.push_back("Ethnicities.Two or More Races");
    dataLabels.push_back("Ethnicities.White Alone");
    dataLabels.push_back("Ethnicities.White Alone not Hispanic or Latino");
    dataLabels.push_back("Housing.Homeownership Rate");
    dataLabels.push_back("Housing.Households");
    dataLabels.push_back("Housing.Housing Units");
    dataLabels.push_back("Housing.Median Value of Owner-Occupied Units");
    dataLabels.push_back("Housing.Persons per Household");
    dataLabels.push_back("Income.Median Houseold Income");
    dataLabels.push_back("Income.Per Capita Income");
    dataLabels.push_back("Miscellaneous.Foreign Born");
    dataLabels.push_back("Miscellaneous.Land Area");
    dataLabels.push_back("Miscellaneous.Language Other than English at Home");
    dataLabels.push_back("Miscellaneous.Living in Same House +1 Years");
    dataLabels.push_back("Miscellaneous.Manufacturers Shipments");
    dataLabels.push_back("Miscellaneous.Mean Travel Time to Work");
    dataLabels.push_back("Miscellaneous.Percent Female");
    dataLabels.push_back("Miscellaneous.Veterans");
    dataLabels.push_back("Population.2020 Population");
    dataLabels.push_back("Population.2010 Population");
    dataLabels.push_back("Population.Population per Square Mile");
    dataLabels.push_back("Sales.Accommodation and Food Services Sales");
    dataLabels.push_back("Sales.Retail Sales");
    dataLabels.push_back("Employment.Firms.Total");
    dataLabels.push_back("Employment.Firms.Women-Owned");
    dataLabels.push_back("Employment.Firms.Men-Owned");
    dataLabels.push_back("Employment.Firms.Minority-Owned");
    dataLabels.push_back("Employment.Firms.Nonminority-Owned");
    dataLabels.push_back("Employment.Firms.Veteran-Owned");
    dataLabels.push_back("Employment.Firms.Nonveteran-Owned");

// initialize adjacency list with empty vectors for each county
    adjList.resize(count);
}

void Graph::addEdge(int u, int v) {
    adjList[u].push_back(v);
}
void Graph::createEdges() {
    // iterate over all counties
    for (int i = 0; i < counties.size(); i++) {
        // get the state of the current county
        string state = counties[i].second;

        // iterate over all counties in the same state
        for (int j : stateMap[state]) {
            // add an edge between the current county and all other counties in the same state
            if (i != j) {
                addEdge(i, j);
            }
        }
    }
}

void Graph::DFS(string county, string state, int userOption) {
    auto t1 = std::chrono::steady_clock::now();

// find index of county
    string key = "\"" + county + "\", \"" + state + "\"";
    int index = countyIndices[key];

// initialize visited vector and call DFSUtil
    vector<bool> visited(adjList.size(), false);
    visited[index] = true;

    // print demographic data for visited nodes
    for (int i = index; i < visited.size(); i++) {
        if (visited[i]) {
            //Age
            if(userOption == 1){
                for (int j = 0; j < 3; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
               // cout << endl;
            }
                //Education
            else if(userOption == 2){
                for (int j = 3; j < 5; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Employment
            else if(userOption == 3){
                for (int j = 5; j < 6; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
               // cout << endl;
            }
                //Ethnicities
            else if(userOption == 4){
                for (int j = 6; j < 14; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
               // cout << endl;
            }
                //Housing
            else if(userOption == 5){
                for (int j = 14; j < 19; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Income
            else if(userOption == 6){
                for (int j = 19; j < 21; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
               // cout << endl;
            }
                //Miscellaneous
            else if(userOption == 7){
                for (int j = 21; j < 29; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Population
            else if(userOption == 8){
                for (int j = 29; j < 32; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Sales
            else if(userOption == 9){
                for (int j = 32; j < 34; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Employment Firms
            else if(userOption == 10){
                for (int j = 34; j < 41; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
        }
    }
    //Other options
    if(userOption == 11){
        otherCountiesDFS(index, visited);
    }
    auto t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> timeDiff =     std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1);
    cout << "----------------------------" << endl;
    cout << "Through DFS: " << timeDiff.count() << " seconds.\n\n";

}

void Graph::DFSUtil(int u, vector<bool> &visited) {
// Mark the current node as visited and print it
    visited[u] = true;
}

void Graph::otherCountiesDFS(int u, vector<bool> &visited) {
    // Recur for all the vertices adjacent to this vertex
    for (int i = 0; i < adjList[u].size(); ++i) {
        int v = adjList[u][i];
        if (!visited[v]) {
            DFSUtil(v, visited);
        }
    }
    cout << "Other counties in this state include: " << endl;
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i]) {
            cout << counties[i].first << endl;
        }
    }
    cout << endl;
}

void Graph::BFS(string county, string state, int userOption) {
    auto t1 = std::chrono::steady_clock::now();

    string key = "\"" + county + "\", \"" + state + "\"";
    int index = countyIndices[key];

// Initialize visited vector
    vector<bool> visited(adjList.size(), false);

    // Create a queue for BFS
    queue<int> q;

    // Start from the first county
    q.push(index);
    visited[index] = true;

    // print demographic data for visited nodes
    for (int i = index; i < visited.size(); i++) {
        if (visited[i]) {
            //Age
            if(userOption == 1){
                for (int j = 0; j < 3; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Education
            else if(userOption == 2){
                for (int j = 3; j < 5; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Employment
            else if(userOption == 3){
                for (int j = 5; j < 6; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Ethnicities
            else if(userOption == 4){
                for (int j = 6; j < 14; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Housing
            else if(userOption == 5){
                for (int j = 14; j < 19; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Income
            else if(userOption == 6){
                for (int j = 19; j < 21; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Miscellaneous
            else if(userOption == 7){
                for (int j = 21; j < 29; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Population
            else if(userOption == 8){
                for (int j = 29; j < 32; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
                //cout << endl;
            }
                //Sales
            else if(userOption == 9){
                for (int j = 32; j < 34; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
               // cout << endl;
            }
                //Employment Firms
            else if(userOption == 10){
                for (int j = 34; j < 41; j++) {
                    cout << dataLabels[j] << ": " << data[i][j] << endl;
                }
               // cout << endl;
            }
        }
    }
    //Other options
    if(userOption == 11){
        otherCountiesBFS(q, visited);
    }
    auto t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> timeDiff = std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1);
    cout << "----------------------------" << endl;
    cout << "Through BFS: " << timeDiff.count() << " seconds.\n\n";
}

void Graph::otherCountiesBFS(queue<int>q, vector<bool> &visited) {
    while (!q.empty()) {
        // Dequeue a vertex from queue and print it
        int u = q.front();
        q.pop();

        // Process adjacent vertices of the dequeued vertex
        for (int i = 0; i < adjList[u].size(); ++i) {
            int v = adjList[u][i];
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }

    }
    cout << "Other counties in this state include: " << endl;
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i]) {
            cout << counties[i].first << endl;
        }
    }
    cout << endl;
}

bool Graph::checkInput(string county, string state, bool check) {
    string key = "\"" + county + "\", \"" + state + "\"";
    int index = countyIndices[key];
    if (index == 0) {
        if (key != "\"Abbeville County\", \"SC\"") {
            cout << "Error: " << key << " not found in the dataset." << endl;
            check = false;
            return check;
        }
    }
    check = true;
    return check;
}

