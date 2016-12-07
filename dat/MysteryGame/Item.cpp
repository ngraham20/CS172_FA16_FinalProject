/*
	This file impliments the methods as initialized in Item.h
*/
#include <iostream>
#include "Item.h"
#include "Weapon.h"
#include "Consumable.h"
#include "Tool.h"


// default constructor does nothing.
Item::Item()
{
}

// creates an item with specific name (to be created when string is read from file)
Item::Item(string name)
{
	this->name = name;
}

// destructs the Item
Item::~Item()
{
}

// Returns a pointer to a specific type of Item, based upon input from system
Item* Item::createItemfromFile(string type)
{
	if (type == "weapon")
	{
		return new Weapon;
	}
	else if (type == "tool")
	{
		return new Tool;
	}
	else if (type == "consumable")
	{
		return new Consumable;
	}

	cout << "Item Type Not Properly Specified. Returning NULL Pointer." << endl;
	return NULL;
}

// returns the name of the item
string Item::getName() { return name; }

// returns the lumosity value of the item
double Item::getLumosity() { return lumosity; }

// sets the item's lumosity
bool Item::setLumosity(double lumosity)
{
	this->lumosity = lumosity;
	return true;
}
