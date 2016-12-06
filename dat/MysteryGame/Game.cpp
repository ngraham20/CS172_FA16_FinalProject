/*
	This file impliments the methods as initialized in Game.h
*/
#include "Game.h"


// this constructor begins the game and calls playGame()
Game::Game()
{
	// the following is a test procedure for the map of loaded rooms
	// TODO change this to begin at the front door
	// creates rooms 000
	/*for (int i = 0; i < 1; i++)
	{
		Coordinates roomNumber = { 0,0,i };
		Room* pointer = new Room(roomNumber);
		loadedRooms.push_back(pointer);
	}*/
	//Coordinates roomNumber = { 0,0,0 };
	//// this is a repeated opening of the same room. This should cause readTemp to activate
	//Room newroom(roomNumber);
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
	// begin the game in the proper room
	Coordinates firstRoom = { 1,4,2 };
	Room* startingRoom = new Room(firstRoom);
	currentRoom = startingRoom;
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
		return "quit";
	}
	else
	{
		cout << "Invalid input. Please Try Again." << endl;
		input.clear();
	//	getAction();
	}
	return input;
}

bool Game::checkRoomChangeValidity()
{
	Room* tRoom = getCurrentRoom();
	vector<bool> temp = tRoom->getDoors();
	return false;
}
