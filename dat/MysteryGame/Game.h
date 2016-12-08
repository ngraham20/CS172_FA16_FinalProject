/*
	This class describes the game as a concept. This class will run all
	basic process within the game such as save, load, pause, and quit.
*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"
#include "Room.h"
class Game
{
public:
	// constructor creates the game
	Game();

	// destructor deletes the game and all temp files.
	~Game();

	bool saveGame(int slotNumber);

	// the room the player is currently in
	Room* getCurrentRoom();

	// only deletes the temp files which have been opened by the game
	bool deleteTemp();

	// this is to be called when errors occur, and the game
	// needs to completely clear all temp. (Only to be called
	// by user)
	static bool fullTempClear();

	// this changes the coordinates of the current room and activates the new room
	bool changeRoom(int relativeY, int relativeX, int relativeZ);

	// this acts as the state machine, running the game
	void playGame();

	// this receives player action and returns a string
	string getAction();

	void displayInstructions();

	// re-displays the room for the player to read
	void displayRoom();

private:
	// the game has loaded rooms
	// these rooms will be ordered as follows <n,s,e,w,u,d>
	vector<Room*>loadedRooms;

	// the game has a player
	Character* player;

	// pointer to the current room
	Room* currentRoom;

	// checks through the current room's doors to make sure that
	// the player can move the direction he wants to
	bool checkRoomChangeValidity();
};

