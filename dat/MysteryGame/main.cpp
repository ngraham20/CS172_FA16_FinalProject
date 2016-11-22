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
	Coordinates location = { 0,0,0 };

	cout << "Accessing File: " << location.y << location.x << location.z << ". . ." << endl;
	Room _000(location);

	location = { 0,0,1 };
	cout << "Accessing File: " << location.y << location.x << location.z << ". . ." << endl;
	Room _001(location);

	_000.deleteTemp();

	_001.deleteTemp();
	return 0;
}