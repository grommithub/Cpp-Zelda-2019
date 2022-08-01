#include "Inventory.h"
#include  "Item.h"

void Inventory::ObtainItem(Pickup* pickup)
{
	if (pickup == nullptr) return;
	for (int i = 0; i < items.size(); i++)
	{	//if item is already in inventory, don't add it again
		if (typeid(*items[i]) == typeid(*pickup))  //https://en.cppreference.com/w/cpp/language/typeid
			return;
	}
	items.push_back(pickup);
}

Inventory::Inventory() : rupees(0), bombs(0), keys(0), menu(false)
{
}

