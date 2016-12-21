/*
	This file impliments the methods as initialized in Character.h
*/
#include "Character.h"



Character::Character()
{
	currentLocation = { 0, 0, 0 };

	// initializes equipped vector so no push_backs are necessary
	equipped = { NULL, NULL };
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

bool Character::hasItem(string name)
{
	for (int i = 0; i < inventory.size(); i++)
	{
		Item* tempItem = inventory.at(i);

		if (tempItem->getName() == name)
		{
			return true;
		}
	}
	cout << "You do not have that item in your inventory." << endl;

	return false;
}

Item* Character::getInventoryItemFromName(string name)
{
	for (int i = 0; i < inventory.size(); i++)
	{
		Item* tempItem = inventory.at(i);

		if (tempItem->getName() == name)
		{
			return tempItem;
		}
	}
	cout << "[GetInventoryItem]: ERROR returning nullpointer. . ." << endl;
	return nullptr;
}

bool Character::equip(Item* item)
{
	// if the item is already equipped
	if (item == equipped.at(0) || item == equipped.at(1))
	{
		cout << "You already have that item in your hand." << endl;
		return false;
	}
	// else if the item is a new one
	else
	{
		if (equipped.at(0) == NULL)
		{
			equipped.at(0) = item;
		}
		else if (equipped.at(1) == NULL)
		{
			equipped.at(1) = item;
		}
		else
		{
			cout << "You cannot equip more than two items at once." << endl;
			return false;
		}
	}

	cout << "You take the " << item->getName() << " in your hand." << endl;
	return true;
}

bool Character::unequip(string name)
{
	if (equipped.at(0) != NULL && equipped.at(0)->getName() == name)
	{
		equipped.at(0) = nullptr;
	}
	else if (equipped.at(1) != NULL && equipped.at(1)->getName() == name)
	{
		equipped.at(1) = nullptr;
	}
	else
	{
		cout << "You do not have that item equipped." << endl;
		return false;
	}

	cout << "You unequipped the " << name << "." << endl;
	return true;
}

