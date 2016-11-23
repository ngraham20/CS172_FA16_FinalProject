/*
	This class describes the game as a concept. This class will run all
	basic process within the game such as save, load, pause, and quit.
*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Room.h"
class Game
{
public:
	Game();
	~Game();

	bool changeRoom();
private:
	// these rooms will be ordered as follows <n,s,e,w,u,d>
	vector<Room*>loadedRooms;
};

