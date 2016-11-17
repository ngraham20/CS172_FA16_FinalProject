/*
	This class describes every item with interaction permission within
	the game. This could mean interaction with the player, it could mean that it moves
	during the game, or it could mean that it can be observed with greater detail than
	the rest of the room.
*/
#pragma once
class Item
{
public:
	Item();
	~Item();
private:
	double lumosity;
protected: 
	// getLumosity is a method that can be used inherantly by another class
	virtual double getLumosity();

	// setLumosity is also an inheritance method
	virtual double setLumosity();
};

