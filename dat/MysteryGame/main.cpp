/*
	This file runs the menu before the game, and
	begins the game upon request from the player.
	After the game begins, however, little is done
	in this file.
*/
#include <iostream>
#include "Coordinates.h"
#include "Room.h"
#include "Input.h"
#include "Character.h"
#include "Game.h"
using namespace std;

int main()
{
	Coordinates location = { 0,0,0 };
	Room testroom(location);
	return 0;
}