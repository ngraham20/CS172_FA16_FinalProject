/*
	This class describes any character within the game who
	might interact with a room, character, or item. This class
	includes, but is not limited to, the player, NPCs, and animals.
*/
#pragma once
#include "Coordinates.h"
#include <vector>
#include "Item.h"
using namespace std; 

class Character
{
public:
	Character();
	~Character();

	Coordinates getLocation();
	vector<Item*> getInventory();
	void addItemToInventory(Item* item);
	Item* removeItemFromInventory(string itemName);
	void setLocation(Coordinates roomLocation);

private:
	Coordinates currentLocation;
	vector<Item*> inventory;
};

