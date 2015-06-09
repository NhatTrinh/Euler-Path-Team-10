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
  int choice = 0;
  
  if (! greetUser())
    return 0;
  
  mainMenu();
  return 0;
}

bool greetUser()
{
  char choice;
  cout << "Welcome to the Euler's Path Program!" << endl;
  cout << endl;
  cout << "Do you want to run this program? " << endl;
  
  cout << "Type Y for YES or N for NO: ";
  cin >> choice;
  
  if (choice == 'Y')
    return true;
  return false;
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

bool mainMenuLoop()
{
  cout << "Enter your choice: ";
  cin >> choice;
  switch (choice)
  {
    case 5:
    {
      cout << endl;
      cout << "Thanks for using this program." << endl;
      return true;
    }
     
    default:
      cout << "You have entered an invalid number!" << endl;
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
      return true;
    }
     
    default:
      cout << "You have entered an invalid number!" << endl;
      return false;
      break;
  }
  }
  return true;
}
