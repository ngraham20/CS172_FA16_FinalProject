#pragma once

// defines the active doors of the room n,s,e,w,u,d and
// stores them in a struct
struct Doors
{
	bool north;
	bool south;
	bool east;
	bool west;
	bool up;
	bool down;
};