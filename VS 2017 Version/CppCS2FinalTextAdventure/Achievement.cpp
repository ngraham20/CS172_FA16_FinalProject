#include "Achievement.h"



Achievement::Achievement(string name)
{
	this->name = name;
	unlocked = false;
}

string Achievement::getName() { return name; }

bool Achievement::isUnlocked() { return unlocked; }

bool Achievement::unlock()
{
	unlocked = true;
	return true;
}


Achievement::~Achievement()
{
}
