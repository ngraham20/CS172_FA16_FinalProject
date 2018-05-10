#pragma once
#include <iostream>
#include "Item.h"

using namespace std;

class OpenFlame : public Item
{
public:
	using Item::Item;

	// TODO impliment OpenFlame class
	
	// this method will take in an item and change its type to an open flame, resulting in this item being deleted
	bool lightItem(Item* original);
};

