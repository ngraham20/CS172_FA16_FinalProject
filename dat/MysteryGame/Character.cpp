/*
	This file impliments the methods as initialized in Character.h
*/
#include "Character.h"



Character::Character()
{
	currentLocation = { 0, 0, 0 };
}


Character::~Character()
{
}

Coordinates Character::getLocation() { return currentLocation; }

vector<Item*> Character::getInventory() { return inventory; }

void Character::addItemToInventory(Item * item)
{
	inventory.push_back(item);
}

void Character::removeItemFromInventory(Item * item)
{
	// searches for a given item by name and then removes it from the inventory, using shrink_to_fit to make sure the vector contains no
	// empty indexes
	for (int i = 0; i < inventory.size(); i++)
	{
		Item * temp = inventory[i];
		if (temp->getName() == item->getName())
		{
			inventory.erase(inventory.begin() + i);
			inventory.shrink_to_fit();
			break;
		}
	}
}

void Character::setLocation(Coordinates roomLocation)
{
	currentLocation = roomLocation;
}

