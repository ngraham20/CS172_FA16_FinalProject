/*
	This class describes any room where a character may enter. Its properties will
	be read from a file to be loaded by the Game class.
*/
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include "Coordinates.h"
#include "Item.h"
using namespace std;

class Room
{
// ----------------------------------PRIVATE--------------------------------------
private:
	// this is the file string which will be used to open any files during gameplay
	string fileName;

	// a static vector of all temp files created to be modified by Game class
	static vector<Coordinates>createdTempFiles;

	// doors are always n,s,e,w,u,d
	vector<bool> doors;

	Coordinates coordinates = {};

	string name; // the name of the room

	// a vector of pointers to item objects
	// the actual room description, which does not include mobile items
	// or details which can be observed.
	vector<Item*>inventory;

	// describes the room in detail
	string description;

	// reads from the original files created pre-compile
	bool readDefaultInventory();

	// creates temporary files to be read from and written to during gameplay
	bool createTempInventory();

// -----------------------------------PUBLIC--------------------------------------
public:

	// creates a room based only on location struct. The rest is read from file.
	Room(Coordinates coordinates);

	// changes the current room. It does this by
	// creating four new rooms in the direction of travel, entering the new room,
	// and destructing the three rooms surrounding the previous one.
	bool changeRoom(Coordinates coordinates);

	// reads from the temporary files created by the constructor
	bool readTempInventory();

	// when the destructor is activated, this method is called to update the
	// room file within a temporary folder. (Which will be read from upon game saving)
	bool updateTemp();

	// returns the description of the room
	string getDescription();

	// describes the room with a cout
	bool describeRoom();

	// returns the name of the room
	string getName();

	// returns as a vector of pointer variables the entire inventory of the room
	vector<Item*> getInventory();

	// returns the struct location of the room
	Coordinates getLocation();

	static vector<Coordinates> getcreatedTempFiles();

	// returns all possible doors, stating which are open, and which are closed.
	vector<bool> getDoors();

	// finds the item from its name variable and then removes it from room inventory
	Item* removeItemFromInventory(string itemName);

	// adds an item to the room's inventory
	void addItemToInventory(Item* item);

	~Room();
};

