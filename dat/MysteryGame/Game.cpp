/*
	This file impliments the methods as initialized in Game.h
*/
#include "Game.h"


// this constructor begins a new game and calls playGame()
Game::Game()
{
	// sets the current room for begining of game
	Coordinates firstRoom = { 1,4,2 };
	player = new Character();
	Room* startingRoom = new Room(firstRoom);
	currentRoom = startingRoom;

	// begins the game.
	playGame();
}

Game::Game(string slot)
{
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

	string fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\saved_rooms.txt";

	input.open(fileName.c_str());
		
	// if the file already exists
	if (!input.fail())
	{
		// go through all previously saved rooms and delete the data inside them
		while (!input.eof())
		{
			string coordinates;

			// save the coordinates to a variable
			input >> coordinates;

			if (coordinates != "")
			{
				// delete the files inside that folder
				fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\" + coordinates + "\\inventory.txt";
			}

			// remove the files
			if (remove(fileName.c_str()) != 0)
			{
				cout << "[overwrightSaves]: Could not delete " << fileName << ". . ." << endl;
			}
			else
			{
				cout << "[overwrightSaves]: Deleted " << fileName << endl;
			}

		}

		fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\saved_rooms.txt";

		// delete saved_rooms.txt
		if (remove(fileName.c_str()) != 0)
		{
			cout << "[overwrightSaves]: Could not delete " << fileName << ". . ." << endl;
		}
		else
		{
			cout << "[overwrightSaves]: Deleted " << fileName << endl;
		}

		input.close();
	}

	// creates a tempory vector of the coordinates of previously
	// visited rooms
	vector<Coordinates> temp = Room::getcreatedTempFiles();

	// then save all new data
	// opens the saved_rooms file to write all saved rooms to
	output.open(fileName.c_str());

	for (int i = 0; i < temp.size(); i++)
	{
		// sets the coordinates for each repetition of the loop
		Coordinates coordinates = temp.at(i);

		// this saves the coordinates of the saved rooms to a file
		string tempCoordinates = to_string(coordinates.y) + to_string(coordinates.x) + to_string(coordinates.z);
		output << tempCoordinates << endl;
	}

	output.close();

	for (int i = 0; i < temp.size(); i++)
	{
		// sets the coordinates for each repetition of the loop
		Coordinates coordinates = temp.at(i);

		string tempName;
		vector<bool> tempDoors;
		vector<Item*> tempInventory;
		string tempDescription;


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
				string itemName;
				string itemType;
				double itemLumosity;

				input >> itemName;
				input >> itemType;
				input >> itemLumosity;

				if (itemName != "")
				{
					//	cout << "[readTemp]: roomInventory: " << temp << endl; // TODO replace cout with inventory.push_back(item)

					// creates an item with specific properties based on the item type
					Item* item = Item::createItem(itemName, itemType, itemLumosity);
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
			string itemName = item->getName();
			string itemType = item->getType();
			double itemLumosity = item->getLumosity();

			if (itemName != "")
			{
				// cout << "[updateTemp]: " << inventoryItem << endl;
				output << itemName + " ";
				output << itemType + " ";
				output << itemLumosity << endl;
			}
		}
		output.close();
	}
	return true;
}

// TODO finish loadGame()
bool Game::loadGame(int slotNumber)
{
	ifstream input;
	ofstream output;

	// use a for loop to loop through a vector of location variables
	string fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\saved_rooms.txt";

	input.open(fileName.c_str());

	if (!input.fail())
	{
		vector<string> roomsToLoad;

		while (!input.eof())
		{
			string coordinates;

			// pushes the coordinates of each line to a vector to be read from later within this method
			input >> coordinates;
			roomsToLoad.push_back(coordinates);

		}
		input.close();

		// TODO read the coordinate string from the vector
		for (int i = 0; i < roomsToLoad.size(); i++)
		{
			string temp = roomsToLoad.at(i);
			
			// open the file at that coordinate
			fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\" + temp + "\\inventory.txt";

			output.open(fileName.c_str());

			// read its inventory to a variable
			
			// close the file

			// open the temp file at the same coordinate
			// write the inventory there
			// close the file
		}

	}
	// set name, type, and lumosity from file to local variables
	// TODO transfer those variables to the temp files
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

		//---------------------------------------inventory------------------------------
		// changes filename to inventory
		string fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
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
		////-----------------------------------------doors-------------------------------------------------
		//fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
		//	to_string(coordinates.x) + to_string(coordinates.z) + "\\doors.txt";
		//if (remove(fileName.c_str()) != 0)
		//{
		//	cout << "[deleteTemp]: Could not delete " << fileName << ". . ." << endl;
		//	return false;
		//}
		//else
		//{
		//	cout << "[deleteTemp]: Deleted " << fileName << endl;
		//}
		////--------------------------------------description----------------------------------------------
		//// changes filename to description
		//fileName = ".\\room\\temp\\" + to_string(coordinates.y) +
		//	to_string(coordinates.x) + to_string(coordinates.z) + "\\description.txt";
		//if (remove(fileName.c_str()) != 0)
		//{
		//	cout << "[deleteTemp]: Could not delete " << fileName << ". . ." << endl;
		//	return false;
		//}
		//else
		//{
		//	cout << "[deleteTemp]: Deleted " << fileName << endl;
		//}
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

	setPlayerLocation(coordinates);

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
	//Clears the cin for when the game classes uses getLine
	cin.ignore();
	do
	{
		
		// call getPlayerInput()
		 playerInput = getAction();

	} while (playerInput != "quit");

	this->~Game();
}

void Game::changeRoomsFromInput(string action)
{
	vector<bool> temp = currentRoom->getDoors();

	if (action == "goNorth")
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
		}
	}
	else if (action == "goSouth")
	{
		// only go south if there's a south door
		if (temp.at(1) == true)
		{
			// go south
			changeRoom(0, 1, 0);
		}
		else
		{
			cout << "You can't go that direction." << endl;
		//	getAction();

		}
	}
	else if (action == "goEast")
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
		}
	}
	else if (action == "goWest")
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
		}
	}
	else if (action == "goUp")
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
		}
	}
	else if (action == "goDown")
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
		}
	}
}

// TODO this needs to be re-named to travel() once the fullly-implimented getAction function is created
string Game::getAction()
{
	string input;
	cout << ">>";

	getline(cin, input);

	// cout << "[changeRoomsFromInput]: Your input was: " << input << endl;

	Input userin(input);

	string action = userin.checkAction();
	// TODO change this code to work for words
	// get a temporary fix on the current room's door situation

	if (action == "goNorth" || action == "goSouth" || action == "goEast" || action == "goWest" || action == "goUp" || action == "goDown")
	{
		changeRoomsFromInput(action);
	}
	else if (action == "quit")
	{
		input = quitGame();
	}
	else if (action == "help")
	{
		displayInstructions();
	}
	else if (action == "room")
	{
		displayRoom();
	}
	else if (input == "save")
	{
		cout << "Caution! This will overwrite any current save data." << endl;

		string answer;
		cout << "Which save slot do you want to save to?" << endl;
		cout << "--------" << endl;
		cout << "|slot 1|" << endl;
		cout << "--------" << endl;
		cout << "|slot 2|" << endl;
		cout << "--------" << endl;
		cout << "|slot 3|" << endl;
		cout << "--------" << endl;
		cout << "| back |" << endl;
		cout << "--------" << endl;
		cout << ">>";

		cin >> answer;

		if (answer == "1" || answer == "slot 1")
		{
			cout << "Overwrighting Save Data. . ." << endl;
			saveGame(1);
			cout << "Game saved to slot 1." << endl;
		}
		else if (answer == "2" || answer == "slot 2")
		{
			cout << "Overwrighting Save Data. . ." << endl;
			saveGame(1);
			cout << "Game saved to slot 2." << endl;
		}
		else if (answer == "3" || answer == "slot 3")
		{
			cout << "Overwrighting Save Data. . ." << endl;
			saveGame(1);
			cout << "Game saved to slot 3." << endl;
		}
		else if (answer == "back")
		{
			cout << "Returning to game. . ." << endl;
			input.clear();
		}
		else
		{
			cout << "Invalid Save Slot." << endl;
			input.clear();
		}
	}
	else if (action == "takeItem")
	{
		Room* temp = currentRoom;
		Item* tempitem = temp->removeItemFromInventory(userin.getSubject());
		if (tempitem != NULL)
		{
			player->addItemToInventory(tempitem);
		}
		else
		{
			cout << "You do not see that item." << endl;
		}
		roomToPlayerItem(userin, action);
	}
	else if (action == "dropItem")
	{

		playerToRoomItem(userin, action);
	}
	else
	{
		cout << "Invalid input. Please Try Again." << endl;
		input.clear();
	}
	return input;
}

void Game::displayInstructions()
{
	cout << "------------------------------------------------------------------------" << endl;
	cout << "  Only type commands in two words phrases. Input is not case sensitive. " << endl;
	cout << "        If an action requires two words, underscore the space           " << endl;
	cout << "          To move, type a cardinal direction or up or down.             " << endl;
	cout << "              Examples: go north , pick_up flashlight                   " << endl;
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

	// describe room inventory
	vector<Item*> tempInventory = currentRoom->getInventory();
	int inventorySize = tempInventory.size();
	cout << "On the floor, you can see a ";

	for (int i = 0; i < inventorySize - 1; i++)
	{
		Item tempItem = *tempInventory.at(i);

		cout << "a " << tempItem.getName() << ",\n";
	}

	Item tempItem = *tempInventory.at(inventorySize - 1);
	cout << "and a " << tempItem.getName() << endl;
}

// this function makes sure that the doors exist
// TODO maybe flush this out and replace some code in getAction() with this
string Game::quitGame()
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
		return "continue";
	}
	else
	{
		cout << "Invalid Input. Please Try again." << endl;
		return "continue";
	}
}

void Game::setPlayerLocation(Coordinates location)
{
	player->setLocation(location);
}

bool Game::checkRoomChangeValidity()
{
	Room* tRoom = getCurrentRoom();
	vector<bool> temp = tRoom->getDoors();
	return false;
}

void Game::roomToPlayerItem(Input userin, string action)
{
	Item* tempItem = currentRoom->removeItemFromInventory(userin.getSubject());
	if (tempItem != NULL)
	{
		player->addItemToInventory(tempItem);
		cout << "You take the " << tempItem->getName() << "." << endl;
	}
	else
	{
		cout << "You do not see that item." << endl;
	}
}

void Game::playerToRoomItem(Input userin, string action)
{
	Item* tempItem = player->removeItemFromInventory(userin.getSubject());
	if (tempItem != NULL)
	{
		currentRoom->addItemToInventory(tempItem);
		cout << "You drop the " << tempItem->getName() << "." << endl;
	}
	else
	{
		cout << "You do not have that item." << endl;
	}
}
