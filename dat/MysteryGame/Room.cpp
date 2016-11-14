/*
	This file impliments the methods as initialized in Room.h
*/
#include <iostream>
#include "Room.h"
using namespace std;

Room::Room(location coordinates) // TODO change struct to integers. Struct acts like a class!
{


	// set a string to equal the xy coordinates of the room + ".txt"
	string fileName = "room\\" + to_string(coordinates.x) + to_string(coordinates.y) + ".txt";

	ifstream input;
	input.open(fileName);
	if (!input.fail())
	{
		cout << "File Accessed";
	}
	else cout << "File not accessible.";
	// if the file opens
		// read from the file all room information
	// otherwise
		// print to console that the file failed to open
		// call destructor
}

bool Room::changeRoom(location coordinates)
{
	// constructs the room at the given coordinates
	// constructs all adjacent connecting rooms
	// moves player to the room at the given coordinates
	// destructs the connecting adjacent rooms to the previous room
	return false;
}

bool Room::updateFile()
{
	return false;
}

vector<Item*> Room::getInventory()
{
	return vector<Item*>();
}

Room::location Room::getLocation()
{
	return location();
}

Room::doors Room::getDoors()
{
	return doors();
}

Room::~Room()
{
}
