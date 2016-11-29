/*
	This file runs the menu before the game, and
	begins the game upon request from the player.
	After the game begins, however, little is done
	in this file.
*/
#include <iostream>
#include "Coordinates.h"
#include "Doors.h"
#include "Game.h"
#include "Input.h"
using namespace std;

int main()
{
	// turns on a game, constructs (at the moment) three rooms
	Game game;

	// deletes all pointers and temp files
	game.~Game();

	return 0;
}