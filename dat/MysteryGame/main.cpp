/*
	This file runs the menu before the game, and
	begins the game upon request from the player.
	After the game begins, however, little is done
	in this file.
*/
#include <iostream>
#include "Coordinates.h"
#include "Game.h"
#include "Input.h"
#include "Room.h"
using namespace std;

int main()
{
	// basic game menu to play game
	cout << "------------------------------------------------" << endl;
	cout << "        WELCOME TO THE JACKSONBURG MANSION      " << endl;
	cout << "------------------------------------------------" << endl;
	cout << "Type 'play' to begin!\n>>";
	string input;
	cin >> input;
	bool quit = false;

	cin.ignore();

	if (input == "play")
		Game game;

	else if (input == "clear")
		Game::fullTempClear();
	return 0;
}