/*
	This file impliments the methods as initialized in Game.h
*/
#include "Game.h"



Game::Game()
{
	// the following is a test procedure for the map of loaded rooms
	// TODO change this to begin at the front door
	// creates rooms 000
	for (int i = 0; i < 1; i++)
	{
		Coordinates roomNumber = { 0,0,i };
		Room* pointer = new Room(roomNumber);
		loadedRooms.push_back(pointer);
	}
	Coordinates roomNumber = { 0,0,0 };
	// this is a repeated opening of the same room. This should cause readTemp to activate
	Room newroom(roomNumber);
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

bool Game::changeRoom()
{
	// checks which direciton the player wants to move
	return false;
}

bool Game::checkRoomChangeValidity()
{
	Room* tRoom = getCurrentRoom();
	vector<bool> temp = tRoom->getDoors();
	return false;
}
