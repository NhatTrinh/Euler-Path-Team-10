#include <iostream>
#include <string>
#include <fstream>
#include "Euler.h"
#include "LinkedStack.h"

using namespace std;

struct EdgeInfo
{
    string city1;
    string city2;
    int edgeweight;
    
    EdgeInfo(string c1, string c2, int ew) { city1 = c1; city2 = c2; edgeweight = ew; }
};

bool greetUser();
void mainMenu();
bool mainMenuLoop(Euler<string> * eulerGraph, ifstream & ifs, LinkedStack<EdgeInfo*> *removedInfo);
bool openInputFile(ifstream &ifs);
void addGraphFromFile(ifstream &ifs, Euler<string> * eulerGraph);

int main()
{
    Euler<string> * eulerGraph = new Euler<string>();
    LinkedStack<EdgeInfo *> * removedInfo = new LinkedStack<EdgeInfo *>();
    ifstream ifs;
    
    if (!greetUser())
    {
        cout << "Good Bye!" << endl;
        return 0;
    }
    
    while (!mainMenuLoop(eulerGraph, ifs, removedInfo))
    {
        mainMenuLoop(eulerGraph, ifs, removedInfo);
    }

    ifs.close();
    return 0;
}

bool greetUser()
{
    string choice;
    bool answer = false;
    cout << "Welcome to the Euler's Path Program!" << endl;
    cout << endl;
    cout << "Do you want to run this program? " << endl;
    
    cout << "Type Y for YES or N for NO: ";
    cin >> choice;
    
    if (choice == "Y" || choice == "y")
        answer = true;
    return answer;
}
void mainMenu()
{
    cout << endl;
    cout << "1. Add graph from file" << endl;
    cout << "2. Add a graph edge" << endl;
    cout << "3. Remove a graph edge" << endl;
    cout << "4. Restore the last removed edge" << endl;
    cout << "5. Solve the graph (Euler's Path)" << endl;
    cout << "6. Display the Graph" << endl;
    cout << "7. Write graph to file" << endl;
    cout << "8. Quit the program" << endl;
    cout << endl;
}

bool openInputFile(ifstream &ifs)
{
    string filename;
    
    //	cout << "Enter the input filename: ";
    getline(cin, filename);
    ifs.open(filename.c_str());
    return ifs.is_open();
}

// this function takes in user input and checks for errors if the user did not enter in a correct number
bool mainMenuLoop(Euler<string> * eulerGraph, ifstream & ifs, LinkedStack<EdgeInfo *> * removedInfo)
{
    bool _switch = false;
    string numChoice;
    
    mainMenu();
    string city1, city2;
    int cityWeight;
    
    cout << "Enter your menu option choice: ";
    cin >> numChoice;
    
    if (numChoice == "1")
    {
        cout << "Enter the input filename: ";
        openInputFile(ifs);
        while (!openInputFile(ifs))
        {
            cout << "File not found. Re-enter: \n";
            continue;
        }
        cout << "Reading complete!\n";
        addGraphFromFile(ifs, eulerGraph);
    }
    
    else if (numChoice == "2")
    {
        cout << "Enter the first city name: ";
        cin >> city1;
        cout << "Enter the second city name: ";
        cin >> city2;
        cout << "Enter the weight of the edge: ";
        cin >> cityWeight;
        cout << endl;
        
        if (eulerGraph->add(city1, city2, cityWeight))
            cout << "Edge successfully added" << endl;
        else
            cout << "Did not work, try again" << endl;
    }
    
    else if (numChoice == "3")
    {
        cout << "Enter the first city name: ";
        cin >> city1;
        cout << "Enter the second city name: ";
        cin >> city2;
        cout << endl;
        
        cityWeight = eulerGraph->getEdgeWeight(city1, city2);
        removedInfo->push(new EdgeInfo(city1, city2, cityWeight));
        
        if (eulerGraph->remove(city1, city2))
            cout << "Edge successfully removed" << endl;
        else
            cout << "Did not work, try again" << endl;
    }
    
    else if (numChoice == "4")
    {
        if (!removedInfo->isEmpty())
        {
            EdgeInfo * temp = removedInfo->peek();
            removedInfo->pop();
            
            if (eulerGraph->add(temp->city1, temp->city2, temp->edgeweight))
                cout << "Edge successfully restored" << endl;
            else
                cout << "Edge restoration failed" << endl;
        }
        else
            cout << "There's no removed edge to recover" << endl;
        
        cout << endl;
    }
    
    else if (numChoice == "5")
    {
        cout << "Checking if the graph is Euler..." << endl;
        cout << endl;
        if (eulerGraph->isEuler())
            cout << "The graph satisfies the Euler's condition" << endl;
        else
            cout << "The graph does not satisfy the Euler's condition" << endl;
        cout << endl;
    }
    
    else if (numChoice == "6")
    {
        cout << endl;
        cout << "Displaying the graph.." << endl;
        eulerGraph->graphToText(cout);
        cout << endl;
    }
    
    
    else if (numChoice == "7")
    {
        ofstream outFile;
        string outfilename;
        
        cout << "Name your output file(with file extension): ";
        cin.ignore();
        getline(cin, outfilename);
        outFile.open(outfilename);
        eulerGraph->graphToText(outFile);
        outFile.close();
        
        cout << endl;
    }
    
    else if (numChoice == "8")
    {
        cout << endl;
        cout << "Thanks for using this program." << endl;
        _switch = true;
        cout << endl;
        return _switch;
    }
    
    else
    {
        cout << "You have entered an invalid number, try again." << endl;
        cout << endl;
    }
    return _switch;

}

void addGraphFromFile(ifstream &ifs, Euler<string> * eulerGraph)
{
    string start;
    string end;
    int edgeWeight;
    
    while (ifs)
    {
        ifs >> start >> end >> edgeWeight;
        if (ifs.eof())
            break;
        else
            eulerGraph->add(start, end, edgeWeight);
    }
}
