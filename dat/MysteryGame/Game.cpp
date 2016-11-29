/*
	This file impliments the methods as initialized in Game.h
*/
#include "Game.h"



Game::Game()
{
	// the following is a test procedure for the map of loaded rooms

	// creates three rooms 000,001,002
	for (int i = 0; i < 3; i++)
	{
		Coordinates roomNumber = { 0,0,i };
		Room* pointer = new Room(roomNumber);
		loadedRooms.push_back(pointer);
	}
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
	return true;
}

bool Game::changeRoom()
{
	// checks which direciton the player wants to move
	return false;
}

bool Game::checkRoomChangeValidity()
{
	Room* tRoom = getCurrentRoom();
	Doors temp = tRoom->getDoors();
	return false;
}
