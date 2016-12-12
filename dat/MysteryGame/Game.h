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
#include "Input.h"
class Game
{
public:
	// constructor creates the game
	Game();

	// overloaded constructor loads a game with specific save slot
	Game(string slot);

	// destructor deletes the game and all temp files.
	~Game();

	// this function saves all created temp files to a save slot.
	// because the room constructor checks for temp files, the save
	// function needn't fill all rooms with original data.
	// TODO save player current room as well
	// TODO maybe change this to only save for current save slot?
	bool saveGame(int slotNumber);

	// TODO Impliment this
	// This method will delete all files in a save slot. This
	// should happen when a new game is created over a save slot.
	// This way, file management won't have to be a problem.
	bool deleteSave(int slotNumber);

	// this method will load all temp files from save slots, then place
	// the player in the saved current room
	bool loadGame(int slotNumber);

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

	// this will change the room according to the users input
	void changeRoomsFromInput(string action);

	// this receives player action and returns a string
	string getAction();

	void displayInstructions();

	// re-displays the room for the player to read
	void displayRoom();

	// makes necessary calls to quit the game
	string quitGame();

	// updates the player's location
	void setPlayerLocation(Coordinates location);

private:
	// the game has loaded rooms
	// these rooms will be ordered as follows <n,s,e,w,u,d>
	vector<Room*>loadedRooms;

	// the game has a player
	Character* player;

	// pointer to the current room
	Room* currentRoom;

	Input* currentInput;

	// checks through the current room's doors to make sure that
	// the player can move the direction he wants to
	bool checkRoomChangeValidity();

	// this function controls the actions that take an item from a room and place it in player inventory
	void roomToPlayerItem(Input userin, string action);

	// this function controls the actions that take an item from the player and place it in room
	void playerToRoomItem(Input userin, string action);

};

