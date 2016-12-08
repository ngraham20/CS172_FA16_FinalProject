/*
	This file impliments the methods as initialized in Game.h
*/
#include "Game.h"


// this constructor begins a new game and calls playGame()
Game::Game() // TODO allow for load/save option
{
	// sets the current room for begining of game
	Coordinates firstRoom = { 1,4,2 };
	Room* startingRoom = new Room(firstRoom);
	currentRoom = startingRoom;

	// begins the game.
	playGame();
}

Game::~Game()
{
	for (int i = 0; i < loadedRooms.size(); i++)
	{
		delete loadedRooms.at(i);
	}

	deleteTemp();
}

bool Game::saveGame(int slotNumber)
{
	ifstream input;
	ofstream output;

	// creates a tempory vector of the coordinates of previously
	// visited rooms
	vector<Coordinates> temp = Room::getcreatedTempFiles();

	for (int i = 0; i < temp.size(); i++)
	{

		string tempName;
		vector<bool> tempDoors;
		vector<Item*> tempInventory;
		string tempDescription;

		// sets the coordinates for each repetition of the loop
		Coordinates coordinates = temp.at(i);


		// TODO the following:

		//-----------------------------------------NAME-------------------------------------------------------
			// collect the name of the room in the current temp coordinate

			// changes filename to name
		string fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\name.txt";

		input.open(fileName.c_str());
		if (!input.fail())
		{
			// sets tempName
			getline(input, tempName);
			input.close();
		}
		else
		{
			cout << "[Save]: Failed to open temp file for saving" << endl;
		}

			// save the name into the current temp coordinate in the given save slot

		// sets fileName to saveslot location
		fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\" +
			to_string(coordinates.y) + to_string(coordinates.x) +
			to_string(coordinates.z) + "\\name.txt";

		output.open(fileName.c_str());
		output << tempName;
		output.close();

		//------------------------------------------------DOORS------------------------------------------------------------
		// DOORS

			// collect the door info
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
					tempDoors.push_back(true);
					// cout << "[readOrigin]: door " << i << ": true" << endl;
				}
				else if (temp == "false")
				{
					tempDoors.push_back(false);
					// cout << "[readOrigin]: door " << i << ": false" << endl;
				}
				else
				{
					cout << "[Save]: temp File failed." << endl;
				}
			}
			input.close();
		}
			// save the door info
		fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\" +
			to_string(coordinates.y) + to_string(coordinates.x) +
			to_string(coordinates.z) + "\\doors.txt";

		output.open(fileName.c_str());
		for (int i = 0; i < tempDoors.size(); i++)
		{
			if (tempDoors.at(i) == true)
			{
				output << "true" << endl;
			}
			else if (tempDoors.at(i) == false)
			{
				output << "false" << endl;
			}
			else
			{
				cout << "[updateTemp]: Could not write bool to file" << endl;
			}
		}
		output.close();

		//----------------------------------------------INVENTORY-------------------------------------------
			// collect the inventory

			// set the fileName variable
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\inventory.txt";

		// get the name of the room from file
		input.open(fileName.c_str());
		// if file opens
		if (!input.fail())
		{
			// cout << "[readTemp]: Accessing inventory.txt" << endl;

			// set the inventory variables
			while (!input.eof())
			{
				string temp;
				input >> temp;
				if (temp != "")
				{
					//	cout << "[readTemp]: roomInventory: " << temp << endl; // TODO replace cout with inventory.push_back(item)

					// creates an item with specific properties based on the item type
					Item* item = Item::createItemfromFile(temp);
					tempInventory.push_back(item);
				}

			}
			input.close();
		}
		//otherwise
		else
		{
			cout << "[Save]: Failed to access temp file: " << fileName << endl;
			// return false;
		}

			// save the inventory
		fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\" +
			to_string(coordinates.y) + to_string(coordinates.x) +
			to_string(coordinates.z) + "\\inventory.txt";

		output.open(fileName.c_str());
		for (int i = 0; i < tempInventory.size(); i++)
		{
			Item* item = tempInventory.at(i);
			string inventoryItem = item->getName();
			if (inventoryItem != "")
			{
				// cout << "[updateTemp]: " << inventoryItem << endl;
				output << inventoryItem << endl;
			}
		}
		output.close();

		//---------------------------------------DESCRIPTION-------------------------------------------
			// collect the description

			// set the fileName variable
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\description.txt";

		// get the name of the room from file
		input.open(fileName.c_str());
		// if file opens
		if (!input.fail())
		{
			// cout << "[readTemp]: Accessing description.txt" << endl;
			// set the inventory variables
			while (!input.eof())
			{
				string temp;
				getline(input, temp);
				tempDescription = tempDescription + temp + "\n";
			}

			// gets rid of extra newline characters (always two of them for some reason)
			while (tempDescription.at(tempDescription.size() - 1) == '\n')
			{
				tempDescription.pop_back();
			}
			input.close();
		}
		//otherwise
		else
		{
			// call destructor
			cout << "[Save]: Failed to access temp file: " << fileName << endl;
			return false;
		}

			// save the description
		fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\" +
			to_string(coordinates.y) + to_string(coordinates.x) +
			to_string(coordinates.z) + "\\description.txt";

		output.open(fileName.c_str());
		output << tempDescription;
		output.close();
	}
	return true;
}

bool Game::loadGame(int slotNumber)
{
	// initialize temporary variables

	return true;
}

Room * Game::getCurrentRoom() { return currentRoom; }

bool Game::deleteTemp()
{
	// creates a temporary vector of coordinates
	vector<Coordinates> temp = Room::getcreatedTempFiles();

	// loops through all open coordinates
	for (int i = 0; i < temp.size(); i++)
	{
		// sets the coordinates to the current one in the vector
		Coordinates coordinates = temp.at(i);

		//--------------------------------------name--------------------------------------
		// changes filename to name
		string fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
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

		//---------------------------------------inventory------------------------------
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
		//-----------------------------------------doors-------------------------------------------------
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\doors.txt";
		if (remove(fileName.c_str()) != 0)
		{
			cout << "[deleteTemp]: Could not delete " << fileName << ". . ." << endl;
			return false;
		}
		else
		{
			cout << "[deleteTemp]: Deleted " << fileName << endl;
		}
		//--------------------------------------description----------------------------------------------
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
	return true;
}

bool Game::fullTempClear()
{
	// creates a temporary vector of coordinates
	vector<Coordinates> temp;
	Coordinates yxz;

	// this calculates the y value
	for (int i = 0; i < 4; i++)
	{
		// this calculates the x value
		for (int j = 0; j < 10; j++)
		{
			// this calculates the z value
			for (int k = 0; k < 10; k++)
			{
				yxz = { i,j,k };
				temp.push_back(yxz);
			}
		}
	}

	// loops through all open coordinates
	for (int i = 0; i < temp.size(); i++)
	{
		// sets the coordinates to the current one in the vector
		Coordinates coordinates = temp.at(i);

		//--------------------------------------name--------------------------------------
		// changes filename to name
		string fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\name.txt";

		// tests the deletion
		if (remove(fileName.c_str()) != 0)
		{
			cout << "[deleteTemp]: Could not delete " << fileName << ". . ." << endl;
			// return false;
		}
		else
		{
			cout << "[deleteTemp]: Deleted " << fileName << endl;
		}

		//---------------------------------------inventory------------------------------
		// changes filename to inventory
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\inventory.txt";

		if (remove(fileName.c_str()) != 0)
		{
			cout << "[deleteTemp]: Could not delete " << fileName << ". . ." << endl;
			// return false;
		}
		else
		{
			cout << "[deleteTemp]: Deleted " << fileName << endl;
		}
		//-----------------------------------------doors-------------------------------------------------
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\doors.txt";
		if (remove(fileName.c_str()) != 0)
		{
			cout << "[deleteTemp]: Could not delete " << fileName << ". . ." << endl;
			// return false;
		}
		else
		{
			cout << "[deleteTemp]: Deleted " << fileName << endl;
		}
		//--------------------------------------description----------------------------------------------
		// changes filename to description
		fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
			to_string(coordinates.x) + to_string(coordinates.z) + "\\description.txt";
		if (remove(fileName.c_str()) != 0)
		{
			cout << "[deleteTemp]: Could not delete " << fileName << ". . ." << endl;
			// return false;
		}
		else
		{
			cout << "[deleteTemp]: Deleted " << fileName << endl;
		}
	}
	return true;
}

bool Game::changeRoom(int relativeY, int relativeX, int relativeZ)
{
	// checks which direciton the player wants to move
	Coordinates coordinates = currentRoom->getLocation();
	coordinates.y += relativeY;
	coordinates.x += relativeX;
	coordinates.z += relativeZ;

	// TODO this needs to delete all unneeded rooms

	Room* temp = new Room(coordinates);
	currentRoom = temp;
	return true;
}

void Game::playGame()
{
	// this method is run constantly and acts as the stateMachine for the game
	// do while input is not quit
	string playerInput;
	do
	{
		// call getPlayerInput()
		 playerInput = getAction();

	} while (playerInput != "quit");

	this->~Game();
}

// TODO this needs to be re-named to travel() once the fullly-implimented getAction function is created
string Game::getAction()
{
	string input;
	cout << ">>";
	//getline(cin, input);
	cin >> input;
	// TODO change this code to work for words
	// get a temporary fix on the current room's door situation
	vector<bool> temp = currentRoom->getDoors();

	if (input == "north")
	{
		// only go north if there's a north door
		if (temp.at(0) == true)
		{
			// go north
			changeRoom(0, -1, 0);
		}
		else
		{
			cout << "You can't go that direction." << endl;
		//	getAction();
		}
	}
	else if (input == "south")
	{
		// only go south if there's a south door
		if (temp.at(1) == true)
		{
			// go south
			changeRoom(0, 1, 0);
			return input;
		}
		else
		{
			cout << "You can't go that direction." << endl;
			return input;
		//	getAction();
		}
	}
	else if (input == "east")
	{
		// only go east if there's an east door
		if (temp.at(2) == true)
		{
			// go east
			changeRoom(0, 0, 1);
		}
		else
		{
			cout << "You can't go that direction." << endl;
	//		getAction();
		}
	}
	else if (input == "west")
	{
		// only go west if there's a west door
		if (temp.at(3) == true)
		{
			// go west
			changeRoom(0, 0, -1);
		}
		else
		{
			cout << "You can't go that direction." << endl;
		//	getAction();
		}
	}
	else if (input == "up")
	{
		// only go up if there's an upper door
		if (temp.at(4) == true)
		{
			// go up
			changeRoom(1, 0, 0);
		}
		else 
		{
			cout << "You can't go that direction." << endl;
			//	getAction();
		}
	}
	else if (input == "down")
	{
		// only go down if there's a lower door
		if (temp.at(5) == true)
		{
			// go down
			changeRoom(-1, 0, 0);
		}
		else
		{
			cout << "You can't go that direction." << endl;
			//	getAction();
		}
	}
	else if (input == "quit")
	{
		cout << "Are you sure you want to quit? Any unsaved progress will be lost.\n>>";
		string answer;
		cin >> answer;
		if (answer == "yes")
		{
			return "quit";
		}
		else if (answer == "no")
		{
			cout << "Resuming game. . ." << endl;
			input = "continue";
		}
		else
		{
			cout << "Invalid Input. Please Try again." << endl;
			input = "continue";
		}
	}
	else if (input == "instructions" || input == "help")
	{
		displayInstructions();
	}
	else if (input == "room" || input == "describe")
	{
		displayRoom();
	}
	else if (input == "save")
	{
		cout << "Which save slot do you want to save to?\n>>";
		char answer;
		cin >> answer;
		if (answer == '1')
		{
			cout << "Overwrighting Save Data. . ." << endl;
			saveGame(1);
			cout << "Game saved to slot 1." << endl;
		}
		else if (answer == '2')
		{
			cout << "Overwrighting Save Data. . ." << endl;
			saveGame(1);
			cout << "Game saved to slot 2." << endl;
		}
		else if (answer == '3')
		{
			cout << "Overwrighting Save Data. . ." << endl;
			saveGame(1);
			cout << "Game saved to slot 3." << endl;
		}
		else
		{
			cout << "Invalid Save Slot." << endl;
			input = "continue";
		}
		
	}
	else
	{
		cout << "Invalid input. Please Try Again." << endl;
		input.clear();
	//	getAction();
	}
	return input;
}

void Game::displayInstructions()
{
	cout << "------------------------------------------------------------------------" << endl;
	cout << "          To move, type a cardinal direction or up or down.             " << endl;
	cout << "              If you would like to quit, type \"quit.\"                 " << endl;
	cout << "------------------------------------------------------------------------" << endl;

	return;
}

void Game::displayRoom()
{
	cout << endl << "[" << this->currentRoom->getName() << "]:" << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << this->currentRoom->getDescription() << endl;
	cout << "------------------------------------------------------------------------" << endl;
}

// this function makes sure that the doors exist
// TODO maybe flush this out and replace some code in getAction() with this
bool Game::checkRoomChangeValidity()
{
	Room* tRoom = getCurrentRoom();
	vector<bool> temp = tRoom->getDoors();
	return false;
}
