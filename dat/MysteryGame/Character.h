/*
	This class describes any character within the game who
	might interact with a room, character, or item. This class
	includes, but is not limited to, the player, NPCs, and animals.
*/
#pragma once
#include "Coordinates.h"
#include <vector>
#include <iostream>
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

	// checks for an item in the player's inventory
	bool hasItem(string name);

	Item* getInventoryItemFromName(string name);

	// equips an item from inventory to equipped vector
	bool equip(Item* item);

	// moves the item back into player inventory, and sets the equipped vector location to NULL
	bool unequip(string name);

private:
	Coordinates currentLocation;
	vector<Item*> inventory;
	vector<Item*> equipped;
};

