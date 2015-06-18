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
void mainMenuLoop(Euler<string> * eulerGraph, bool & stopLoop, ifstream & ifs, LinkedStack<EdgeInfo*> *removedInfo);
bool openInputFile(ifstream &ifs);
void addGraphFromFile(ifstream &ifs, Euler<string> * eulerGraph);

int main()
{
	Euler<string> * eulerGraph = new Euler<string>();
    LinkedStack<EdgeInfo *> * removedInfo = new LinkedStack<EdgeInfo *>();
	bool stopLoop = false;
	ifstream ifs;
	
	if (!greetUser())
		return 0;
	while (stopLoop != true)
	{
		mainMenuLoop(eulerGraph, stopLoop, ifs, removedInfo);
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
	cout << "1. Add graph from file" << endl;
	cout << "2. Add a graph edge" << endl;
	cout << "3. Remove a graph edge" << endl;
    cout << "4. Restore the last removed edge" << endl;
	cout << "5. Solve the graph (Euler's Path)" << endl;
	cout << "6. Display the Graph" << endl;
	cout << "7. Write graph to file" << endl;
	cout << "8. Quit the program" << endl;
}

bool openInputFile(ifstream &ifs)
{
	string filename;

	cout << "Enter the input filename: ";
	getline(cin, filename);
	ifs.open(filename.c_str());
	return ifs.is_open();
}

// this function takes in user input and checks for errors if the user did not enter in a correct number
void mainMenuLoop(Euler<string> * eulerGraph, bool & loopStop, ifstream & ifs, LinkedStack<EdgeInfo *> * removedInfo)
{
	int choice = 0;

	mainMenu();
	string city1, city2;
	int cityWeight;
	string filename;
	
	cout << "Enter your menu option choice: ";
	cin >> choice;
	
	switch (choice)
	{
        case 1:
            while (!openInputFile(ifs))
            {
                cout << "Please Enter File Name Again." << endl;
            }
            addGraphFromFile(ifs, eulerGraph);
            break;

        case 2:
            cout << "Enter the first city name: ";
            cin >> city1;
            cout << "Enter the second city name: ";
            cin >> city2;
            cout << "Enter the weight of the edge: ";
            cin >> cityWeight;
            
            if (eulerGraph->add(city1, city2, cityWeight))
                cout << "Edge successfully added" << endl;
            else 
                cout << "Did not work, try again" << endl;
            break;
        
        case 3:
            cout << "Enter the first city name: ";
            cin >> city1;
            cout << "Enter the second city name: ";
            cin >> city2;
            
            cityWeight = eulerGraph->getEdgeWeight(city1, city2);
            removedInfo->push(new EdgeInfo(city1, city2, cityWeight));
            
            if (eulerGraph->remove(city1, city2))
                cout << "Edge successfully removed" << endl;
            else 
                cout << "Did not work, try again" << endl;
            break;
        
        case 4:
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
            }
                break;
            
        case 5:
            {
                cout << "Checking if the graph is Euler..." << endl;
                if (eulerGraph->isEuler())
                    cout << "The graph satisfies the Euler's condition" << endl;
                else
                    cout << "The graph does not satisfy the Euler's condition" << endl;
            }
                break;
        case 6:
            {
                cout << "Displaying the graph.." << endl;
                eulerGraph->graphToText(cout);
            }
            break;
        
        case 7:
            {
                ofstream outFile;
                string outfilename;
            
                cout << "Name your output file(with file extension): ";
                cin >> outfilename;
                outFile.open(outfilename);
                // do something here to write the graph to the file
                outFile.close();
            }
            break;
        
        case 8:
            cout << endl;
            cout << "Thanks for using this program." << endl;
            loopStop = true;
            break;
        
        default:
            cout << "You have entered an invalid number, try again." << endl;
            break;
    }
    
}

void addGraphFromFile(ifstream &ifs, Euler<string> * eulerGraph)
{
	string start;
	string end;
	int edgeWeight;
	
	while (ifs >> start >> end >> edgeWeight)
	{
		eulerGraph->add(start, end, edgeWeight);
	}
}