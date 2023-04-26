#include "county.h"
#include "graph.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
  bool menu = true;
  bool check = false;
  int userOption;
  string county, state;
  // create graph
  Graph g;

  cout << "Where Is My Home Sweet Home?" << endl;
  cout << "Welcome!" << endl;
  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
  cout << endl;

  while (check == false) {
    cout << "What county are you considering?" << endl;
    getline(cin, county);
    cout << "In what state?" << endl;
    getline(cin, state);
    if (g.checkInput(county, state, check)) {
      break;
    }
  }

  g.createEdges();
  

  while (menu) {
    cout << "\nAre there any specific factors you'd like to see?" << endl;
    cout << "1) Age" << endl;
    cout << "2) Education" << endl;
    cout << "3) Employment" << endl;
    cout << "4) Ethnicities" << endl;
    cout << "5) Housing" << endl;
    cout << "6) Income" << endl;
    cout << "7) Miscellaneous" << endl;
    cout << "8) Population" << endl;
    cout << "9) Sales" << endl;
    cout << "10) Employment Firms" << endl;
    cout << "11) Other counties in same state" << endl;
    cout << "12) Exit Program" << endl;
    cin >> userOption;

     while(cin.fail()){
      cin.clear(); 
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
      cout << "Please enter a valid menu option." << endl; 
      cin >> userOption; 
    }

    if (userOption == 12) {
      cout << "Thank you for using our program." << endl;
      break;
    }

    cout << "\nData for " << county << ", " << state << ":" << endl << endl;

    switch (userOption) {
    case 1:
      cout << "Only age data displayed below:" << endl;
      cout << endl;
      g.DFS(county, state, userOption);
      g.BFS(county, state, userOption);
      break;
    case 2:
      cout << "Only education data displayed below:" << endl;
      cout << endl;
      g.DFS(county, state, userOption);
      g.BFS(county, state, userOption);
      break;
    case 3:
      cout << "Only employment data displayed below:" << endl;
      cout << endl;
      g.DFS(county, state, userOption);
      g.BFS(county, state, userOption);
      break;
    case 4:
      cout << "Only ethnicity data displayed below:" << endl;
      cout << endl;
      g.DFS(county, state, userOption);
      g.BFS(county, state, userOption);
      break;
    case 5:
      cout << "Only housing data displayed below:" << endl;
      cout << endl;
      g.DFS(county, state, userOption);
      g.BFS(county, state, userOption);
      break;
    case 6:
      cout << "Only income data displayed below:" << endl;
      g.DFS(county, state, userOption);
      g.BFS(county, state, userOption);
      break;
    case 7:
      cout << "Only miscellaneous data displayed below:" << endl;
      cout << endl;
      g.DFS(county, state, userOption);
      g.BFS(county, state, userOption);
      break;
    case 8:
      cout << "Only population data displayed below:" << endl;
      cout << endl;
      g.DFS(county, state, userOption);
      g.BFS(county, state, userOption);
      break;
    case 9:
      cout << "Only sales data displayed below:" << endl;
      cout << endl;
      g.DFS(county, state, userOption);
      g.BFS(county, state, userOption);
      break;
    case 10:
      cout << "Only employment firm data displayed below:" << endl;
      cout << endl;
      g.DFS(county, state, userOption);
      g.BFS(county, state, userOption);
      break;
    case 11:
      g.DFS(county, state, userOption);
      g.BFS(county, state, userOption);
      break;
    default:
      cout << "Not found. Please enter a valid menu option." << endl;
      break;
    }
    check = true;
  }
}