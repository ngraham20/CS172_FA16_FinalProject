/*
	This class describes every item with interaction permission within
	the game. This could mean interaction with the player, it could mean that it moves
	during the game, or it could mean that it can be observed with greater detail than
	the rest of the room.
*/
#pragma once
#include <string>
using namespace std;

class Item
{
public:
	Item();
	Item(string name);
	~Item();

	static Item* createItemfromFile(string type);

	// returns the name
	string getName();

	// getLumosity is a method that can be used inherantly by another class which ALWAYS returns
	// the lumosity
	virtual double getLumosity();

	// setLumosity sets the lumosity for any item
	virtual bool setLumosity(double lumosity);
private:
	string name;
	double lumosity;
	int power;
};

