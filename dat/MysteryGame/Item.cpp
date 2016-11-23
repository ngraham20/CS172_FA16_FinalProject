/*
	This file impliments the methods as initialized in Item.h
*/
#include "Item.h"



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

string Item::getName() { return name; }

double Item::getLumosity()
{
	return 0.0;
}

bool Item::setLumosity()
{
	return false;
}
