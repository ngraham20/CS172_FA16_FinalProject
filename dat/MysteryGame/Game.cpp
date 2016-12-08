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
	getline(cin, input);

	Input userin(input);

	string verb = userin.getVerb();
	string subject = userin.getSubject();
	// TODO change this code to work for words
	// get a temporary fix on the current room's door situation
	vector<bool> temp = currentRoom->getDoors();

	if (subject == "north")
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
	else if (subject == "south")
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
	else if (subject == "east")
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
	else if (subject == "west")
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
	else if (subject == "up")
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
	else if (subject == "down")
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
	else if (verb == "quit")
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

bool Game::checkRoomChangeValidity()
{
	Room* tRoom = getCurrentRoom();
	vector<bool> temp = tRoom->getDoors();
	return false;
}
