/*
	This file impliments the methods as initialized in Item.h
*/
#include "Item.h"
#include "Weapon.h"



Item::Item()
{
}

Item::Item(string name)
{
	this->name = name;
}


Item::~Item()
{
}

Item* Item::createItemfromFile(string type)
{
	
	return new Weapon;
}

string Item::getName() { return name; }

double Item::getLumosity() { return lumosity; }

bool Item::setLumosity(double lumosity)
{
	this->lumosity = lumosity;
	return true;
}
