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
#include "Room.h"
using namespace std;

int main()
{
	// basic game menu to play game
	cout << "Type 'play' to begin!\n>>";
	string input;
	cin >> input;
	bool quit = false;

	//while (!quit)
	//{
	//	// all game processes now run inside this loop
	//	if (input == "play")
	//	{
	//		// turns on a game, constructs (at the moment) three rooms
	//		Game game;

	//		// deletes all pointers and temp files
	//		game.~Game();
	//	}
	//	else
	//	{
	//		cout << "You did not type 'play.' Do you want to quit?\n>>";
	//		cin >> input;
	//		if (input == "yes")
	//		{
	//			quit = true;
	//		}
	//	}
	//}

	Game game;
	//game.~Game();

	return 0;
}