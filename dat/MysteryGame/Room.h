/*
	This class describes any room where a character may enter. Its properties will
	be read from a file to be loaded by the Game class.
*/
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Coordinates.h"
#include "Item.h"
using namespace std;

class Room
{
// ----------------------------------PRIVATE--------------------------------------
private:

	// defines the active doors of the room n,s,e,w,u,d and
	// stores them in a struct
	struct Door
	{
		bool north;
		bool south;
		bool east;
		bool west;
		bool up;
		bool down;
	};
	Door door = {};
	Coordinates coordinates = {};

	string name; // the name of the room

	// a vector of pointers to item objects
	// the actual room description, which does not include mobile items
	// or details which can be observed.
	vector<Item*>inventory;

	// describes the room in detail
	string description;

// -----------------------------------PUBLIC--------------------------------------
public:
	// creates a room based only on location struct. The rest is read from file.
	Room(Coordinates coordinates);

	// creates temporary files to be read from and written to during gameplay
	bool createTemp();

	// reads from the temporary files created by the constructor
	bool readTemp();

	// reads from the original files created pre-compile
	bool readOrigin();

	// changes the current room. It does this by
	// creating four new rooms in the direction of travel, entering the new room,
	// and destructing the three rooms surrounding the previous one.
	bool changeRoom(Coordinates coordinates);

	// when the destructor is activated, this method is called to update the
	// room file within a temporary folder. (Which will be read from upon game saving)
	bool updateTemp();

	// returns as a vector of pointer variables the entire inventory of the room
	vector<Item*> getInventory();

	// returns the struct location of the room
	Coordinates getLocation();

	// returns all possible doors, stating which are open, and which are closed.
	Door getDoors();

	~Room();
};

