/*
	This file impliments the methods as initialized in Game.h
*/
#include "Game.h"

// initializes the player to be static
Character* Game::player;

vector<Achievement*> Game::achievements;

// this constructor begins a new game and calls playGame()
Game::Game()
{
	createAchievements();

	// sets the current room for begining of game
	firstRoom = { 1,4,2 };
	player = new Character();
	setPlayerLocation(firstRoom);
	Room* startingRoom = new Room(firstRoom);
	currentRoom = startingRoom;

	// begins the game.
	playGame();
}

// this is for loading the game
Game::Game(int slot)
{
	createAchievements();

	player = new Character();
	loadGame(slot);
	setPlayerLocation(firstRoom);
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

	for (int i = 0; i < achievements.size(); i++)
	{
		delete achievements.at(i);

	}
	delete player;
	deleteTemp();
	return;
}


bool Game::createAchievements()
{
	// TODO edit saveGame and loadGame to work with these
	// TODO pull these from file instead of from code

	achievements = {
	new Achievement("Lighting_the_Way"),
	new Achievement("Drop_the_Base"),
	new Achievement("Help_Me"),
	new Achievement("Taking_Inventory"),
	new Achievement("Poor_Vision")
	};

	return true;
}

bool Game::saveGame(int slotNumber)
{
	ifstream input;
	ofstream output;

	//-----------------------------------------------------ROOMS--------------------------------------------------------
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
				//cout << "[overwrightSaves]: Could not delete " << fileName << ". . ." << endl;
			}
			else
			{
				//cout << "[overwrightSaves]: Deleted " << fileName << endl;
			}

		}

		fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\saved_rooms.txt";

		// delete saved_rooms.txt
		if (remove(fileName.c_str()) != 0)
		{
			//cout << "[overwrightSaves]: Could not delete " << fileName << ". . ." << endl;
		}
		else
		{
			//cout << "[overwrightSaves]: Deleted " << fileName << endl;
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


		//----------------------------------------------ROOM_INVENTORY-------------------------------------------
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

	//------------------------------------------PLAYER_LOCATION---------------------------------------------------------
	fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\player_location.txt";
	
	Coordinates tempCoordinates = player->getLocation();

	string playerLocation = to_string(tempCoordinates.y) + to_string(tempCoordinates.x) + to_string(tempCoordinates.z);

	// create/overwright the playerlocation
	output.open(fileName.c_str());

	output << playerLocation;

	output.close();

	//----------------------------------------------PLAYER_INVENTORY----------------------------------------------------

	// save player inventory

	fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\player_inventory.txt";

	output.open(fileName.c_str());

	vector<Item*> tempInventory = player->getInventory();

	for (int i = 0; i < tempInventory.size(); i++)
	{
		Item* tempItem = tempInventory.at(i);

		output << tempItem->getName() << " " << tempItem->getType() << " " << tempItem->getLumosity() << endl;
	}

	output.close();

	//------------------------------------------------------UNLOCKED_ACHIEVEMENTS---------------------------------
	fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\unlocked_achievements.txt";

	output.open(fileName.c_str());

	for (int i = 0; i < achievements.size(); i++)
	{
		Achievement* tempAchievement = achievements.at(i);

		if (tempAchievement->isUnlocked() == true)
		{
			output << tempAchievement->getName() << endl;
		}
	}

	return true;
}

bool Game::loadGame(int slotNumber)
{
	cout << "Loading Game. . ." << endl;

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
			if (coordinates != "")
			{
				constexpr int asciiInt = 48;

				Coordinates temp = { 
					coordinates[0] - asciiInt,
					coordinates[1] - asciiInt,
					coordinates[2] - asciiInt 
				};

				// pushes loaded temp rooms to the created temp files in room class
				Room::createdTempFiles.push_back(temp);
				roomsToLoad.push_back(coordinates);
			}

		}
		input.close();

		// for every room which needs to be loaded
		for (int i = 0; i < roomsToLoad.size(); i++)
		{
			string tempRoom = roomsToLoad.at(i);
			
			// open the save slot inventory file
			fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\" + tempRoom + "\\inventory.txt";

			string itemName;
			string itemType;
			double itemLumosity;

			// a temporary inventory to use to transfer items between files
			vector<Item*> temporaryInventory;

			input.open(fileName.c_str());

			//-----------------------------------------------READ INVENTORY TO VARIABLES--------------------------------------------------------
			// write the inventory there
			if (!input.fail())
			{
				while (!input.eof()) 
				{
					// set name, type, and lumosity from file to local variables
					input >> itemName;
					input >> itemType;
					input >> itemLumosity;

					if (itemName != "")
					{
						// create temporary pointer to a new item
						Item* temp1 = Item::createItem(itemName, itemType, itemLumosity);

						// if there are multiple items in the vector
						if (temporaryInventory.size() > 0)
						{
							// this is the last item in the vector
							Item* temp2 = temporaryInventory.at(temporaryInventory.size() - 1);

							// if the item-to-be-created is NOT the same as the temp2
							if (temp1->getName() != temp2->getName())
							{
								// send that item to the temporary vector
								temporaryInventory.push_back(temp1);
							}
						}
						// else if this is the first item to be put in the inventory
						else
						{
							// send that item to the temporary vector
							temporaryInventory.push_back(temp1);
						}
					}
				}
			}
			else
			{
				cout << "[Load]: failed to open save files." << endl;
				return false;
			}
			// close the file
			input.close();

			// --------------------------------------------------------WRITE TO TEMP---------------------------------
			fileName = ".\\room\\temp\\" + tempRoom + "\\inventory.txt";

			output.open(fileName.c_str());

			for (int i = 0; i < temporaryInventory.size(); i++)
			{
				// create temporary item to send to inventory.txt
				Item* temp = temporaryInventory.at(i);

				output << temp->getName() << " " << temp->getType() << " " << temp->getLumosity() << endl;
			
			}
			output.close();
		}

	}

	//-------------------------PLAYER_LOCATION-------------------------------------------------
	fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\player_location.txt";

	input.open(fileName.c_str());

	if (!input.fail())
	{
		string room;
		constexpr int asciiDecimal = 48;
		input >> room;

		// room[] returns the ascii value, subtracting 48 gives the actual 0-9 values
		firstRoom.y = room[0] - asciiDecimal;
		firstRoom.x = room[1] - asciiDecimal;
		firstRoom.z = room[2] - asciiDecimal;

		input.close();
	}
	else
	{
		cout << "[Load]: Failed to open player_location.txt" << endl;
	}

	//----------------------------------PLAYER_INVENTORY------------------------------------------------

	fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\player_inventory.txt";

	input.open(fileName.c_str());

	if (!input.fail())
	{
		while (!input.eof())
		{
			string itemName;
			string itemType;
			double itemLumosity;

			input >> itemName >> itemType >> itemLumosity;

			if (itemName != "")
			{
				Item* tempItem = Item::createItem(itemName, itemType, itemLumosity);

				player->addItemToInventory(tempItem);
			}
		}
		input.close();
	}

	//--------------------------------------ACHIEVEMENTS------------------------------------------------------------
	fileName = ".\\saves\\slot " + to_string(slotNumber) + "\\unlocked_achievements.txt";

	input.open(fileName.c_str());

	if (!input.fail())
	{
		while (!input.eof())
		{
			string achievementName;
			input >> achievementName;

			if (achievementName != "")
			{
				Achievement* tempAchievement = getAchievementWithName(achievementName);

				// unlocks the achievement pre-game for load sequence
				tempAchievement->unlock();
			}
		}
	}


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
			// cout << "[deleteTemp]: Could not delete " << fileName << ". . ." << endl;
			return false;
		}
		else
		{
			// cout << "[deleteTemp]: Deleted " << fileName << endl;
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


Achievement* Game::getAchievementWithName(string name)
{
	for (int i = 0; i < achievements.size(); i++)
	{
		Achievement* tempAchievement = achievements.at(i);

		if (tempAchievement->getName() == name)
		{
			return tempAchievement;
		}
	}

	return nullptr;
}

bool Game::tryUnlockAchievement(Achievement* achievement)
{
	// first checks to see if the achievement exists
	if (achievement != nullptr)
	{
		// then checks if the achievement has happened already
		if (!achievement->isUnlocked())
		{
			achievement->unlock();
			cout << "------------------------" << endl;
			cout << "<<ACHIEVEMENT UNLOCKED!>>" << endl;
			cout << "(" << achievement->getName() << ")" << endl;
			cout << "------------------------" << endl;

			/*for (int i = 0; i < lockedAchievements.size(); i++)
			{
				Achievement* tempAchievement = lockedAchievements.at(i);

				if (tempAchievement = achievement)
				{

				}
			}*/
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "Achievement unlock failed. Returned Nullpointer." << endl;
	}

	return false;
}

bool Game::changeRoom(int relativeY, int relativeX, int relativeZ)
{
	// checks which direciton the player wants to move
	Coordinates coordinates = currentRoom->getLocation();
	coordinates.y += relativeY;
	coordinates.x += relativeX;
	coordinates.z += relativeZ;

	setPlayerLocation(coordinates);

	// TODO delete any unneeded rooms (pre-loading)

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
}

void Game::changeRoomsFromInput(string action)
{
	vector<string> temp = currentRoom->getDoors();

	if (action == "goNorth")
	{
		// only go north if there's a north door
		if (temp.at(0) == "true")
		{
			// go north
			changeRoom(0, -1, 0);
		}
		else if (temp.at(0) == "locked")
		{
			cout << "That door is locked. . ." << endl;
		}
		else
		{
			cout << "You can't go that direction." << endl;
		}
	}
	else if (action == "goSouth")
	{
		// only go south if there's a south door
		if (temp.at(1) == "true")
		{
			// go south
			changeRoom(0, 1, 0);
		}
		else if (temp.at(1) == "locked")
		{
			cout << "That door is locked. . ." << endl;
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
		if (temp.at(2) == "true")
		{
			// go east
			changeRoom(0, 0, 1);
		}
		else if (temp.at(2) == "locked")
		{
			cout << "That door is locked. . ." << endl;
		}
		else
		{
			cout << "You can't go that direction." << endl;
		}
	}
	else if (action == "goWest")
	{
		// only go west if there's a west door
		if (temp.at(3) == "true")
		{
			// go west
			changeRoom(0, 0, -1);
		}
		else if (temp.at(3) == "locked")
		{
			cout << "That door is locked. . ." << endl;
		}
		else
		{
			cout << "You can't go that direction." << endl;
		}
	}
	else if (action == "goUp")
	{
		// only go up if there's an upper door
		if (temp.at(4) == "true")
		{
			// go up
			changeRoom(1, 0, 0);
		}
		else if (temp.at(4) == "locked")
		{
			cout << "That door is locked. . ." << endl;
		}
		else
		{
			cout << "You can't go that direction." << endl;
		}
	}
	else if (action == "goDown")
	{
		// only go down if there's a lower door
		if (temp.at(5) == "true")
		{
			// go down
			changeRoom(-1, 0, 0);
		}
		else if (temp.at(5) == "locked")
		{
			cout << "That door is locked. . ." << endl;
		}
		else
		{
			cout << "You can't go that direction." << endl;
		}
	}
}

string Game::getAction()
{
	string input;
	cout << ">>";

	getline(cin, input);
	
	Input userin(input);

	string action = userin.checkAction();
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
		cout << endl;
		cout << "               <[Caution!]>               " << endl;
		cout << "This will overwrite any current save data." << endl;

		string answer;
		cout << "Which save slot do you want to save to?" << endl;
		cout << "  -------- -------- -------- --------  " << endl;
		cout << "  | back | |  G1  | |  G2  | |  G3  |  " << endl;
		cout << "  -------- -------- -------- --------  " << endl;
		cout << ">>";

		cin >> answer;

		if (answer == "1" || answer == "G1" || answer == "g1")
		{
			cout << "Overwrighting Save Data. . ." << endl;
			saveGame(1);
			cout << "Game saved to slot 1." << endl;
			cin.ignore();
		}
		else if (answer == "2" || answer == "G2" || answer == "g2")
		{
			cout << "Overwrighting Save Data. . ." << endl;
			saveGame(2);
			cout << "Game saved to slot 2." << endl;
			cin.ignore();
		}
		else if (answer == "3" || answer == "G3" || answer == "g3")
		{
			cout << "Overwrighting Save Data. . ." << endl;
			saveGame(3);
			cout << "Game saved to slot 3." << endl;
			cin.ignore();
		}
		else if (answer == "back")
		{
			cout << "Returning to game. . ." << endl;
			input.clear();
			cin.ignore();
		}
		else
		{
			cout << "Invalid Save Slot." << endl;
			input.clear();
			cin.ignore();
		}
	}
	else if (action == "takeItem")
	{
		roomToPlayerItem(userin, action);
	}
	else if (action == "dropItem")
	{
		playerToRoomItem(userin, action);
	}
	else if (action == "inventory")
	{
		printPlayerInventory();

		tryUnlockAchievement(getAchievementWithName("Taking_Inventory"));
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

	tryUnlockAchievement(getAchievementWithName("Help_Me"));

	return;
}

void Game::displayRoom() 
{
	currentRoom->displayRoom(); 
}

// this function makes sure that the doors exist
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
		cin.ignore();
		cout << "Resuming game. . ." << endl;
		return "continue";
	}
	else
	{
		cin.ignore();
		cout << "Invalid Input. Please Try again." << endl;
		return "continue";
	}
}

void Game::setPlayerLocation(Coordinates location)
{
	player->setLocation(location);
}

Character * Game::getPlayer() { return player; }

bool Game::checkRoomChangeValidity()
{
	Room* tRoom = getCurrentRoom();
	vector<string> temp = tRoom->getDoors();
	return false;
}

void Game::roomToPlayerItem(Input userin, string action)
{
	Item* tempItem = currentRoom->removeItemFromInventory(userin.getSubject());
	if (tempItem != NULL)
	{
		player->addItemToInventory(tempItem);
		currentRoom->updateTemp();
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
		currentRoom->updateTemp();
		cout << "You drop the " << tempItem->getName() << "." << endl;


		if (tempItem->getName() == "base")
		{
			tryUnlockAchievement(getAchievementWithName("Drop_the_Base"));
		}


	}
	else
	{
		cout << "You do not have that item." << endl;
	}
}

void Game::printPlayerInventory()
{
	vector<Item*> tempinventory = player->getInventory();
	if (tempinventory.size() != 0)
	{
		cout << endl;
		cout << "-<[INVENTORY]>-" << endl;
		cout << "---------------" << endl;

		for (int i = 0; i < tempinventory.size(); i++)
		{
			Item* tempItem = tempinventory.at(i);

			cout << "| " << tempItem->getName() << " |" << endl;
			/*if ((i+1) % 3 == 0)
			{
				cout << "|" << tempItem->getName() << "|" << endl;
			}
			else
			{
				cout << "|" << tempItem->getName() << "|";

				if (tempinventory.size() == 1)
				{
					cout << endl;
				}
			}*/
		}
	}
	else
	{
		cout << "You are not carrying any items." << endl;
	}
}
