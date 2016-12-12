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
Item::Item(string name, string type, double lumosity)
{
	this->name = name;
	this->type = type;
	this->lumosity = lumosity;

}

// destructs the Item
Item::~Item()
{
}

// Returns a pointer to a specific type of Item, based upon input from system
Item* Item::createItem(string name, string type, double lumosity)
{
	if (type == "weapon")
	{
		return new Weapon(name,type,lumosity);
	}
	else if (type == "tool")
	{
		return new Tool(name,type,lumosity);
	}
	else if (type == "consumable")
	{
		return new Consumable(name,type,lumosity);
	}

	cout << "Item Type Not Properly Specified. Returning NULL Pointer." << endl;
	return NULL;
}

// returns the name of the item
string Item::getName() { return name; }

string Item::getType() { return type; }

// returns the lumosity value of the item
double Item::getLumosity() { return lumosity; }

// sets the item's lumosity
bool Item::setLumosity(double lumosity)
{
	this->lumosity = lumosity;
	return true;
}
