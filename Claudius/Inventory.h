#pragma once

#include <vector>
#include "Item.h"

class Inventory
{
	std::vector<Pickup*> items;
public:
	int rupees;
	int keys;
	int bombs;
	bool menu;
	void ObtainItem(Pickup* pickup);
	Inventory();
	
};

