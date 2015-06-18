#include <iostream>
#include <string>
#include <fstream>
#include "Euler.h"

using namespace std;

bool greetUser();
void mainMenu();
void mainMenuLoop(Euler<string> * eulerGraph, bool & stopLoop, ifstream & ifs);
bool openInputFile(ifstream &ifs);
void addGraphFromFile(Euler<string> * eulerGraph,ifstream &ifs);

int main()
{
	int userChoice = 0;
	Euler<string> * eulerGraph = new Euler<string>();
	bool stopLoop = false;
	ifstream ifs;
	
	if (!greetUser())
		return 0;
	while (stopLoop != true)
	{
		mainMenuLoop(eulerGraph,stopLoop, ifs);
	}
	
	ifs.close();
	return 0;
}

bool greetUser()
{
	char choice;
	bool answer = false;
	cout << "Welcome to the Euler's Path Program!" << endl;
	cout << endl;
	cout << "Do you want to run this program? " << endl;

	cout << "Type Y for YES or N for NO: ";
	cin >> choice;

	if (choice == 'Y' || choice == 'y')
		answer = true;
	return answer;
}
void mainMenu()
{
	cout << "1. Add graph from file" << endl;
	cout << "2. Add a graph edge" << endl;
	cout << "3. Remove a graph edge" << endl;
	cout << "4. Solve the graph (Euler's Path)" << endl;
	cout << "5. Display the Graph" << endl;
	cout << "6. Write graph to file" << endl;
	cout << "7. Quit the program" << endl;
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
void mainMenuLoop(Euler<string> * eulerGraph, bool & loopStop, ifstream & ifs)
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
	{
		while (!openInputFile(ifs))
		{
			cout << "Please Enter File Name Again." << endl;
		}
		addGraphFromFile(eulerGraph, ifs);
		break;
	}
	case 2:
	{
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
	}
	case 3:
	{
		cout << "Enter the first city name: ";
		cin >> city1;
		cout << "Enter the second city name: ";
		cin >> city2;
		if (eulerGraph->remove(city1, city2))
			cout << "Edge successfully removed" << endl;
		else
			cout << "Did not work, try again" << endl;
		break;
	}
	case 4:
	{
		cout << "Checking if the graph is Euler..." << endl;
		if (eulerGraph->isEuler())
			cout << "The graph satisfies the Euler's condition" << endl;
		else
			cout << "The graph does not satisfy the Euler's condition" << endl;
		break;
	}
	case 5:
	{
		cout << "Displaying the graph.." << endl;
		break;
	}
	case 6:
	{
		ofstream outFile;
		string filename;

		cout << "Name your output file(with file extension): ";
		cin >> filename;
		outFile.open(filename);
		// do something here to write the graph to the file
		outFile.close();
	}
	case 7:
	{
		cout << endl;
		cout << "Thanks for using this program." << endl;
		loopStop = true;
		break;
	}
	default:
	{
		cout << "You have entered an invalid number, try again." << endl;
		break;
	}
	}
}

void addGraphFromFile(Euler<string> * eulerGraph, ifstream &ifs)
{
	string city1;
	string city2;
	int edgeWeight;
	
	while (ifs >> city1 >> city2 >> edgeWeight)
	{
		eulerGraph->add(city1, city2, edgeWeight);
	}
}

