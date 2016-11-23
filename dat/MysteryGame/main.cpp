/*
	This file runs the menu before the game, and
	begins the game upon request from the player.
	After the game begins, however, little is done
	in this file.
*/
#include <iostream>
#include "Item.h"
#include "Weapon.h"
#include "Coordinates.h"
#include "Room.h"
#include "Input.h"
#include "Character.h"
#include "Game.h"
using namespace std;

int main()
{
	/*Coordinates location = { 0,0,0 };

	cout << "[main]: Accessing File: " << location.y << location.x << location.z << ". . ." << endl;
	Room _000(location);

	location = { 0,0,1 };
	cout << "[main]: Accessing File: " << location.y << location.x << location.z << ". . ." << endl;
	Room _001(location);

	_000.~Room();

	_001.~Room();

	location = { 0,0,0 };
	Room _001_2(location);

	_000.deleteTemp();

	_001.deleteTemp();*/


	Game game;

	game.~Game();

	return 0;
}