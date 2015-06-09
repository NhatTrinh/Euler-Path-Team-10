#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool greetUser();
void mainMenu();
bool mainMenuLoop();
bool openInputFile(ifstream &ifs);

int main()
{
	int userChoice = 0;

	if (!greetUser())
		return 0;

	mainMenu();
	mainMenuLoop();
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
	return answer
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
bool mainMenuLoop()
{
	int choice = 0;
	bool retVal = 0;

	cout << "Enter your choice: ";
	cin >> choice;
	switch (choice)
	{
	case 5:
	{
		cout << endl;
		cout << "Thanks for using this program." << endl;
		break;
	}

	default:
		cout << "You have entered an invalid number, try again." << endl;
		break;
	}
	while (choice != 5)
	{
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 5:
		{
			cout << endl;
			cout << "Thanks for using this program." << endl;
			break;
		}

		default:
			cout << "You have entered an invalid number, try again." << endl;
			break;
		}
	}
	return retVal;
}
