#include <iostream>
#include <string>
#include <fstream>
#include "Euler.h"

using namespace std;

bool greetUser();
void mainMenu();
void mainMenuLoop(Euler<string> * &eulerGraph, bool & stopLoop);
bool openInputFile(ifstream &ifs);

int main()
{
	int userChoice = 0;
	Euler<string> * eulerGraph = new Euler<string>();
	bool stopLoop = false;
	ifstream ifs;
	string inputData;
	
	while(!openInputFile)
	{
		cout << "Reenter the file name." << endl;
	}
	if (!greetUser())
		return 0;
	while (stopLoop != true)
	{
		mainMenuLoop(eulerGraph,stopLoop);
	}
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
	cout << "1. Add a graph edge" << endl;
	cout << "2. Remove a graph edge" << endl;
	cout << "3. Solve the graph (Euler's Path)" << endl;
	cout << "4. Write graph to file" << endl;
	cout << "5. Quit the program" << endl;
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
void mainMenuLoop(Euler<string> * &eulerGraph, bool & loopStop)
{
	int choice = 0;

	mainMenu();
	string city1, city2;
	int cityWeight;
	
	cout << "Enter your menu option choice: ";
	cin >> choice;
	switch (choice)
	{
	case 1:
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
	case 2:
		cout << "Enter the first city name: ";
		cin >> city1;
		cout << "Enter the second city name: ";
		cin >> city2;
		if (eulerGraph->remove(city1, city2))
			cout << "Edge successfully removed" << endl;
		else 
			cout << "Did not work, try again" << endl;
			break;
	case 3:		
		cout << "Checking if the graph is Euler..." << endl;
		if (eulerGraph->isEuler())
			cout << "The graph satisfies the Euler's condition" << endl;
		else 
			cout << "The graph does not satisfy the Euler's condition" << endl;
			break;
	case 4:
			
	case 5:
		cout << endl;
		cout << "Thanks for using this program." << endl;
		loopStop = true;
		break;

	default:
		cout << "You have entered an invalid number, try again." << endl;
		break;
	}
}
