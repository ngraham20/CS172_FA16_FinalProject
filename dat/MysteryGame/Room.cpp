/*
	This file impliments the methods as initialized in Room.h
*/
#include "Room.h"
using namespace std;

Room::Room(Coordinates coordinates)
{
	ifstream input;

	string fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\name.txt";
	
	input.open(fileName.c_str());
	// if the temp file does not exist --------------------------------------------------------------if
	if (input.fail())
	{
		// set the fileName variable
		fileName = ".\\room\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\name.txt";

		// get the name of the room from file
		input.open(fileName.c_str());

		// if file opens
		if (!input.fail())
		{
			// set the name variable
			getline(input, name);
			cout << name << endl; // TODO remove this to properly play game
			input.close();
		}
		// otherwise
		else
		{
			// call destructor
			cout << "Could not open file. . ." << endl;
			this->~Room();
		}

		// set the fileName variable
		fileName = ".\\room\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\inventory.txt";

		// get the name of the room from file
		input.open(fileName.c_str());
		// if file opens
		if (!input.fail())
		{
			cout << "Accessing inventory.txt" << endl; // TODO remove this to properly play game
			// set the inventory variables
			while (!input.eof())
			{
				string temp;
				input >> temp;
				if (temp != "")
					cout << temp << endl; // TODO replace cout with inventory.push_back(item)
			}
			input.close();
		}
		//otherwise
		else
		{
			// call destructor
			this->~Room();
		}

		// set the fileName variable
		fileName = ".\\room\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\description.txt";

		// get the name of the room from file
		input.open(fileName.c_str());
		// if file opens
		if (!input.fail())
		{
			cout << "Accessing description.txt" << endl;
			// set the inventory variables
			while (!input.eof())
			{
				string temp;
				getline(input, temp);
				description = description + temp + "\n";
			}
			cout << description << endl; // TODO remove this to properly play game
			input.close();
		}
		//otherwise
		else
		{
			// call destructor
			cout << "Could not open file. . .\n";
			this->~Room();
		}

		//---------------------------------creates temp-------------------------------------
		ofstream output;
		// set the fileName variable
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\name.txt";

		// get the name of the room from file
		output.open(fileName.c_str());

		// if file opens
		if (output.fail())
		{
			cout << fileName << " failed to open." << endl;
		}
		else output.close();

		// set the fileName variable
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\inventory.txt";

		// get the name of the room from file
		output.open(fileName.c_str());

		// if file opens
		if (output.fail())
		{
			cout << fileName << " failed to open." << endl;
		}
		else output.close();
		// set the fileName variable
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\description.txt";

		// get the name of the room from file
		output.open(fileName.c_str());

		// if file opens
		if (output.fail())
		{
			cout << fileName << " failed to open." << endl;
		}
		else output.close();
	}
	// else if the temp files do exist, read from them-------------------------------------else
	else
	{
		input.close();
		// set the fileName variable
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\name.txt";

		// get the name of the room from file
		input.open(fileName.c_str());

		// if file opens
		if (!input.fail())
		{
			// set the name variable
			getline(input, name);
			cout << name << endl; // TODO remove this to properly play game
			input.close();
		}
		// otherwise
		else
		{
			// call destructor
			cout << "Failed to access " << fileName << endl;
			this->~Room();
		}

		// set the fileName variable
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\inventory.txt";

		// get the name of the room from file
		input.open(fileName.c_str());
		// if file opens
		if (!input.fail())
		{
			cout << "Accessing inventory.txt" << endl; // TODO remove this to properly play game
													   // set the inventory variables
			while (!input.eof())
			{
				string temp;
				input >> temp;
				if (temp != "")
					cout << temp << endl; // TODO replace cout with inventory.push_back(item)
			}
			input.close();
		}
		//otherwise
		else
		{
			// call destructor
			cout << "Failed to access " << fileName << endl;
			this->~Room();
		}

		// set the fileName variable
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\description.txt";

		// get the name of the room from file
		input.open(fileName.c_str());
		// if file opens
		if (!input.fail())
		{
			cout << "Accessing description.txt" << endl;
			// set the inventory variables
			while (!input.eof())
			{
				string temp;
				getline(input, temp);
				description = description + temp + "\n";
			}
			cout << description << endl; // TODO remove this to properly play game
			input.close();
		}
		//otherwise
		else
		{
			// call destructor
			cout << "Failed to access " << fileName << endl;
			this->~Room();
		}

	}
}

bool Room::changeRoom(Coordinates coordinates)
{
	// constructs the room at the given coordinates
	// constructs all adjacent connecting rooms
	// moves player to the room at the given coordinates
	// destructs the connecting adjacent rooms to the previous room
	return false;
}

bool Room::updateFile()
{
	// open output file with current room label
	ofstream output;

	string fileName = ".\\room\\temp\\" + to_string(coordinates.y) + 
		to_string(coordinates.x) + to_string(coordinates.z) + "\\name.txt";

	output.open(fileName.c_str());

	if (!output.fail())
	{
		cout << fileName << " accessed!" << endl;
	}
	else
	{
		cout << fileName << " could not be accessed." << endl;
	}
	// read all variables to file
	return false;
}

vector<Item*> Room::getInventory() { return inventory; }

Coordinates Room::getLocation() { return coordinates; }

Room::Door Room::getDoors() { return door; }

Room::~Room()
{
	// calls the updateRoom() function to update the temp files with all variable information
	// deletes the allocated memory for the items within inventory
}
