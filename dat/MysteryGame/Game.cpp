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
	// loop through all currently loaded rooms
	for (int i = 0; i < loadedRooms.size(); i++)
	{
		// gain access to vector contents
		Room* temp = loadedRooms.at(i);

		// delete temporary files for loaded rooms
		temp->deleteTemp();

		// unload rooms
		delete loadedRooms.at(i);
	}
}

bool Game::changeRoom()
{
	return false;
}
