#pragma once
#include "Items/Item.h"

class InventoryComponent
{
public:
	InventoryComponent(int Width, int Height);
	~InventoryComponent();

	bool AddItem(Item* item);
	Item* GetItem(int x, int y);
	void RemoveItem(int x, int y);

	int GetWidth() const
	{
		return Width;
	}

	int GetHeight() const
	{
		return Height;
	}

private:
	int Width;
	int Height;
	Item*** Inventory;
};

