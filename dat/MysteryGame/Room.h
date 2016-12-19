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
#include "Game.h"
#include "Character.h"
#include "Coordinates.h"
#include "Item.h"
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define UP 4
#define DOWN 5
using namespace std;

class Game;

class Room
{
// ----------------------------------PRIVATE--------------------------------------
private:
	// this is the file string which will be used to open any files during gameplay
	string fileName;

	// doors are always n,s,e,w,u,d
	vector<string> doors;

	Coordinates coordinates = {};

	string name; // the name of the room

	// a vector of pointers to item objects
	// the actual room description, which does not include mobile items
	// or details which can be observed.
	vector<Item*>inventory;

	// describes the room in detail
	string description;

	// bool for whether the room has a default light source
	bool lightSource;

	// reads from the original files created pre-compile
	bool readVariableFilesFromOrigin();

	// creates temporary files to be read from and written to during gameplay
	bool createTempFiles();

// -----------------------------------PUBLIC--------------------------------------
public:

	//static vector<Item*> playerInventory;

	//// this sets the player
	//static bool setPlayerInventory(vector<Item*> playerInventory);

	// a static vector of all temp files created to be modified by Game class
	static vector<Coordinates>createdTempFiles;

	// creates a room based only on location struct. The rest is read from file.
	Room(Coordinates coordinates);

	// changes the current room. It does this by
	// creating four new rooms in the direction of travel, entering the new room,
	// and destructing the three rooms surrounding the previous one.
	bool changeRoom(Coordinates coordinates);

	// reads from the temporary files created by the constructor
	bool readVariableFilesFromTemp();

	// when the destructor is activated, this method is called to update the
	// room file within a temporary folder. (Which will be read from upon game saving)
	bool updateTemp();

	// returns the description of the room
	string getDescription();
	
	// displays room for the player to see
	bool displayRoom();

	// describes the room with a cout
	bool readConstantFromOrigin();

	// returns the name of the room
	string getName();

	// returns as a vector of pointer variables the entire inventory of the room
	vector<Item*> getInventory();

	// returns the struct location of the room
	Coordinates getLocation();

	static vector<Coordinates> getcreatedTempFiles();

	// returns all possible doors, stating which are open, and which are closed.
	vector<string> getDoors();

	// finds the item from its name variable and then removes it from room inventory
	Item* removeItemFromInventory(string itemName);

	// adds an item to the room's inventory
	void addItemToInventory(Item* item);

	// unlocks a given door in a room
	bool unlockDoor(int doorValue);

	// the following set functions are to be used by the Game's Load() function
	bool setInventory(vector<Item*> inventory);

	bool setDoors(vector<string> doors);

	~Room();
};

