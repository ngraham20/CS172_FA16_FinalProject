#include "OpenFlame.h"

bool OpenFlame::lightItem(Item * original)
{
	Item tempItem = *original;

	if (tempItem.getType() == "unlit")
	{
		// light the item

		// this overwrites the information in original pointer location to a lit (and therefore bright) version of the same item
		string newName = "flaming_" + tempItem.getName();

		original = new OpenFlame(newName, "open_flame", 1.0);
	}
	else
	{
		cout << "That item cannot be lit on fire." << endl;
		return false;
	}

	return true;
}
