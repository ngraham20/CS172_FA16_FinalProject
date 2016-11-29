/*
	This class describes the game as a concept. This class will run all
	basic process within the game such as save, load, pause, and quit.
*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"
#include "Doors.h"
#include "Room.h"
class Game
{
public:
	Game();
	~Game();

	// the room the player is currently in
	Room* getCurrentRoom();

	bool deleteTemp();
	bool changeRoom();
private:
	// the game has loaded rooms
	// these rooms will be ordered as follows <n,s,e,w,u,d>
	vector<Room*>loadedRooms;

	// the game has a player
	Character* player;

	Room* currentRoom;

	// checks through the current room's doors to make sure that
	// the player can move the direction he wants to
	bool checkRoomChangeValidity();
};

