#pragma once
#include "Item.h"

class InventoryComponent
{
public:
	InventoryComponent(int Width, int Height);
	~InventoryComponent();

	void AddItem(Item* item, int x, int y);
	void GetItem(Item* item, int x, int y);
	void RemoveItem(Item* item, int x, int y);

private:
	int Width;
	int Height;
	Item*** Inventory;
};

