/*
	This file impliments the methods as initialized in Room.h
*/
#include "Room.h"
using namespace std;

Room::Room(Coordinates coordinates)
{
	this->coordinates = coordinates;

	ifstream input;

	// check to see if the name file exists
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

		// write to the temp files from rom properties
		updateTemp();

	}
}

// TODO create overloaded constructor to be called upon loadGame()

bool Room::createTemp() // TODO create the temp files with Coordinates as an input
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
				cout << "[origin]: roomInventory:" << temp << endl; // TODO replace cout with inventory.push_back(item)
			Item* item = new Item(temp);
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

	fileName = ".\\room\\temp\\" + to_string(coordinates.y) + 
		to_string(coordinates.x) + to_string(coordinates.z) + "\\name.txt";

	input.open(fileName.c_str());

	if (!input.fail())
	{
		cout << "[updateTemp]: " << fileName << " accessed to be updated. . .!" << endl;

		// closes the file once it's been opened (and written to)
		input.close();

		// TODO write to temp files

		output.open(fileName.c_str());
		output << name;
		output.close();

		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\inventory.txt";

		output.open(fileName.c_str());
		for (int i = 0; i < inventory.size(); i++)
		{
			cout << "[updateTemp]: " << inventory.at(i) << endl;
			output << inventory.at(i) << endl;
		}
		output.close();

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

bool Room::deleteTemp()
{
	// changes filename to name
	fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\name.txt";

	// tests the deletion
	if (remove(fileName.c_str()) != 0)
	{
		cout << "[deleteTemp]: Could not delete " << fileName << ". . ." << endl;
		return false;
	}
	else
	{
		cout << "[deleteTemp]: Deleted " << fileName << endl;
	}

	// changes filename to inventory
	fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\inventory.txt";
	if (remove(fileName.c_str()) != 0)
	{
		cout << "[deleteTemp]: Could not delete " << fileName << ". . ." << endl;
		return false;
	}
	else
	{
		cout << "[deleteTemp]: Deleted " << fileName << endl;
	}

	// changes filename to description
	fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
		to_string(coordinates.x) + to_string(coordinates.z) + "\\description.txt";
	if (remove(fileName.c_str()) != 0)
	{
		cout << "[deleteTemp]: Could not delete " << fileName << ". . ." << endl;
		return false;
	}
	else
	{
		cout << "[deleteTemp]: Deleted " << fileName << endl;
	}
}

vector<Item*> Room::getInventory() { return inventory; }

Coordinates Room::getLocation() { return coordinates; }

Room::Door Room::getDoors() { return door; }

Room::~Room()
{
	// calls the updateTemp() function to update the temp files with all variable information
	updateTemp();

	// deletes the allocated memory for the items within inventory

}
