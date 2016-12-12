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

Item* Character::removeItemFromInventory(string itemName)
{
	// searches for a given item by name and then removes it from the player inventory, using shrink_to_fit to make sure the vector contains no
	// empty indexes
	for (int i = 0; i < inventory.size(); i++)
	{
		Item * temp = inventory.at(i);
		if (temp != NULL)
		{
			if (temp->getName() == itemName)
			{
				Item* temp = inventory.at(i);
				inventory.erase(inventory.begin() + i);
				inventory.shrink_to_fit();
				return temp;
			}
		}
	}
	return NULL;
}

void Character::setLocation(Coordinates roomLocation)
{
	currentLocation = roomLocation;
}

