/*
	This file impliments the methods as initialized in Room.h
*/
#include "Room.h"
using namespace std;

vector<Coordinates> Room::createdTempFiles;

// default constructor for begining of game
Room::Room(Coordinates coordinates)
{
	cout << "\n[Default Room Constructor]: " << endl;
	this->coordinates = coordinates;

	ifstream input;

	// check to see if the temp name file exists
	fileName = ".\\room\\temp\\" + to_string(this->coordinates.y) +
		to_string(this->coordinates.x) + to_string(this->coordinates.z) + "\\name.txt";
	
	input.open(fileName.c_str());
	// if the temp files do exist
	if (!input.fail())
	{
		// close the file
		input.close();

		// read the temp files into the room properties
		readTemp();
	}
	// else if the temp files do not exist
	else
	{

		// read the origin file into the room properties
		readOrigin();

		// create blank temp files
		cout << "[constructor]: Creating temp files." << endl; // TODO delete before release
		createTemp();

		// this adds the created room's coordinates to the vector.
		createdTempFiles.push_back(this->coordinates);

		// write to the temp files from rom properties
		updateTemp();

	}
}

// TODO create overloaded constructor to be called upon loadGame() to read from saves

bool Room::createTemp()
{
	// createTemp is only called privately, and only by the constructor...
	// it is also only to CREATE blank files. They will always open.

	ofstream output;

	string filename = ".\\room\\temp\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\name.txt";

	output.open(filename.c_str());
	if (output.fail()) { return false; }
	output.close();
	cout << "[createTemp]: Created name.txt" << endl;

	filename = ".\\room\\temp\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\inventory.txt";

	output.open(filename.c_str());
	if (output.fail()) { return false; }
	output.close();
	cout << "[createTemp]: Created invnentory.txt" << endl;

	filename = ".\\room\\temp\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\description.txt";

	output.open(filename.c_str());
	if (output.fail()) { return false; }
	output.close();
	cout << "[createTemp]: Created description.txt" << endl;

	return true;
}

bool Room::readTemp()
{
	ifstream input;
	//------------------------------------------name-------------------------------------------
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
		cout << "[readTemp]: roomName" << name << endl; // TODO remove this to properly play game
		input.close();
	}
	// otherwise
	else
	{
		// call destructor
		cout << "[readTemp]: Failed to access " << fileName << endl;
		this->~Room();
		return false;
	}

	//--------------------------------------------------inventory------------------------------------
	// set the fileName variable
	fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\inventory.txt";

	// get the name of the room from file
	input.open(fileName.c_str());
	// if file opens
	if (!input.fail())
	{
		cout << "[readTemp]: Accessing inventory.txt" << endl; // TODO remove this to properly play game
												   // set the inventory variables
		while (!input.eof())
		{
			string temp;
			input >> temp;
			if (temp != "")
				cout << "[readTemp]: roomInventory: " << temp << endl; // TODO replace cout with inventory.push_back(item)
		}
		input.close();
	}
	//otherwise
	else
	{
		// call destructor
		cout << "[readTemp]: Failed to access " << fileName << endl;
		this->~Room();
		return false;
	}

	// -----------------------------------------doors---------------------------------------------------
	// set the filename variable
	fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\doors.txt";

	// open the file
	input.open(fileName.c_str());

	// if the file opens
	if (!input.fail())
	{
		// read to the door struct from file
		string temp;
		constexpr int doorCount = 6;
		for (int i = 0; i < doorCount; i++)
		{
			input >> temp;
			if (temp == "true")
			{
				doors.push_back(true);
				cout << "[readTemp]: door " << i << ": true" << endl;
			}
			else if (temp == "false")
			{
				doors.push_back(false);
				cout << "[readTemp]: door " << i << ": false" << endl;
			}
			else
			{
				cout << "[readTemp]: file input is not true or false." << endl;
			}
		}
		input.close();
	}
	else
	{
		cout << "[readTemp]: Could not open Door temp files" << endl;
	}

	//-----------------------------------------------description-----------------------------------------
	// set the fileName variable
	fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\description.txt";

	// get the name of the room from file
	input.open(fileName.c_str());
	// if file opens
	if (!input.fail())
	{
		cout << "[readTemp]: Accessing description.txt" << endl;
		// set the inventory variables
		while (!input.eof())
		{
			string temp;
			getline(input, temp);
			description = description + temp + "\n";
		}
		cout << "[readTemp]: roomDescription: " << description << endl; // TODO remove this to properly play game
		input.close();
	}
	//otherwise
	else
	{
		// call destructor
		cout << "[readTemp]: Failed to access " << fileName << endl;
		this->~Room();
		return false;
	}

	return true;
}

bool Room::readOrigin()
{
	ifstream input;
	// ------------------------------------name-----------------------------------------------
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
		cout << "[origin]: roomName: " << name << endl; // TODO remove this to properly play game
		input.close();
	}
	// otherwise
	else
	{
		// call destructor
		cout << "[readOrigin]: " << fileName << " does not exist. . ." << endl;
		this->~Room();
		return false;
	}
	// --------------------------------------inventory--------------------------------
	// set the fileName variable
	fileName = ".\\room\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\inventory.txt";

	// get the name of the room from file
	input.open(fileName.c_str());
	// if file opens
	if (!input.fail())
	{
		cout << "[readOrigin]: Accessing inventory.txt" << endl; // TODO remove this to properly play game

		// set the inventory variables
		while (!input.eof())
		{
			string temp;
			input >> temp;
			if (temp != "")
				cout << "[origin]: roomInventory:" << temp << endl;
			Item* item = Item::createItemfromFile(temp);
			inventory.push_back(item);
		}
		input.close();
	}
	//otherwise
	else
	{
		// call destructor
		this->~Room();
		return false;
	}
	// -----------------------------------------doors---------------------------------------------------
	// set the filename variable
	fileName = ".\\room\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\doors.txt";

	// open the file
	input.open(fileName.c_str());

	// if the file opens
	if (!input.fail())
	{
		// read to the door struct from file
		string temp;
		constexpr int doorCount = 6;
		for (int i = 0; i < doorCount; i++)
		{
			input >> temp;
			if (temp == "true")
			{
				doors.push_back(true);
				cout << "[readOrigin]: door " << i << ": true" << endl;
			}
			else if (temp == "false")
			{
				doors.push_back(false);
				cout << "[readOrigin]: door " << i << ": false" << endl;
			}
			else
			{
				cout << "[readOrigin]: file input is not true or false." << endl;
			}
		}
		input.close();
	}

	// -----------------------------------------description--------------------------------------------
	// set the fileName variable
	fileName = ".\\room\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\description.txt";

	// get the name of the room from file
	input.open(fileName.c_str());
	// if file opens
	if (!input.fail())
	{
		cout << "[readOrigin]: Accessing description.txt" << endl;
		// set the inventory variables
		while (!input.eof())
		{
			string temp;
			getline(input, temp);
			description = description + temp + "\n";
		}
		cout << "[origin]: roomDescription: " << description << endl; // TODO remove this to properly play game
		input.close();
	}
	//otherwise
	else
	{
		// call destructor
		cout << "[readOrigin]: Could not open file. . .\n";
		this->~Room();
		return false;
	}
	return true;
}

bool Room::changeRoom(Coordinates coordinates)
{
	// constructs the room at the given coordinates
	// constructs all adjacent connecting rooms
	// moves player to the room at the given coordinates
	// destructs the connecting adjacent rooms to the previous room
	return false;
}

bool Room::updateTemp()
{
	// open output file with current room label
	ofstream output;
	ifstream input;

	// -------------------------------------------name----------------------------------------------
	fileName = ".\\room\\temp\\" + to_string(coordinates.y) + 
		to_string(coordinates.x) + to_string(coordinates.z) + "\\name.txt";

	input.open(fileName.c_str());

	if (!input.fail())
	{
		cout << "[updateTemp]: " << fileName << " accessed to be updated. . .!" << endl;

		// closes the file once it's been opened (and written to)
		input.close();

		output.open(fileName.c_str());
		output << name;
		output.close();

		//------------------------------------inventory----------------------------------------------
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\inventory.txt";

		output.open(fileName.c_str());
		for (int i = 0; i < inventory.size(); i++)
		{
			Item* item = inventory.at(i);
			string inventoryItem = item->getName();
			if (inventoryItem != "")
			{
				cout << "[updateTemp]: " << inventoryItem << endl;
				output << inventoryItem << endl;
			}
		}
		output.close();
		//--------------------------------------doors----------------------------------------------------
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\doors.txt";
		output.open(fileName.c_str());
		for (int i = 0; i < doors.size(); i++)
		{
			if (doors.at(i) == true)
			{
				output << "true" << endl;
			}
			else if (doors.at(i) == false)
			{
				output << "false" << endl;
			}
			else
			{
				cout << "[updateTemp]: Could not write bool to file" << endl;
			}
		}
		output.close();

		//------------------------------------description------------------------------------------------
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\description.txt";
		output.open(fileName.c_str());
		output << description;
		output.close();
	}
	else
	{
		cout << "[updateTemp]: " << fileName << " could not be accessed." << endl;
	}
	// read all variables to file
	return false;
}

vector<Item*> Room::getInventory() { return inventory; }

Coordinates Room::getLocation() { return coordinates; }

vector<Coordinates> Room::getcreatedTempFiles() { return createdTempFiles; }

vector<bool> Room::getDoors() { return doors; }

Room::~Room()
{
	cout << "[Room Destructor]: " << endl;
	// calls the updateTemp() function to update the temp files with all variable information
	updateTemp();

	// deletes the allocated memory for the items within inventory
	for (int i = 0; i < inventory.size(); i++)
	{
		delete inventory.at(i);
	}
}
