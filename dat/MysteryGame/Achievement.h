#pragma once
#include <string>
using namespace std;

class Achievement
{
public:
	// constructor creates the achievement and sets the unlocked bool to false
	Achievement(string name);

	string getName();

	bool unlock();

	~Achievement();
private:
	string name;
	bool unlocked;
};

