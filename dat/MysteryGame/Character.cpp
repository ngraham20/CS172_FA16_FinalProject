/*
	This file impliments the methods as initialized in Character.h
*/
#include "Character.h"



Character::Character()
{
}


Character::~Character()
{
}

Coordinates Character::getLocation() { return currentLocation; }

vector<Item*> Character::getInventory() { return inventory; }

void Character::addItemToInventory(Item * item)
{
}

void Character::removeItemFromInventory(Item * item)
{
	int index = -1;
	auto it = std::find(inventory.begin(), inventory.end(), item);
	if (it == inventory.end())
	{
		// name not in vector
	}
	else
	{
		index = std::distance(inventory.begin(), it);
	}
	if (index != -1)
	{
		inventory.erase(inventory.begin() + index);
	}
}

