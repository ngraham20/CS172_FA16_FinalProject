/*
	This file impliments the methods as initialized in Room.h
*/
#include "Room.h"
using namespace std;

Room::Room(Coordinates coordinates)
{
	ifstream input;
	// set the fileName variable
	string fileName = ".\\room\\" + to_string(coordinates.y) + 
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
	// read all variables to file
	return false;
}

vector<Item*> Room::getInventory()
{
	// return inventory as a vector of items
	return vector<Item*>();
}

Coordinates Room::getLocation()
{
	// return the yxz coordinates within this class's Coordinates struct
	return Coordinates();
}

Room::Door Room::getDoors()
{
	// return the bools of every door within this Class's Door struct
	return Door();
}

Room::~Room()
{
	// calls the updateRoom() function to update the temp files with all variable information
	// deletes the allocated memory for the items within inventory
}
