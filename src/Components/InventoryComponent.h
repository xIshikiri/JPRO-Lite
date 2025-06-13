#pragma once
#include "Items/Item.h"

class InventoryComponent
{
public:
	InventoryComponent(int Width, int Height);
	~InventoryComponent();

	bool addItem(Item* item);
	Item* getItem(int x, int y);
	void removeItem(int x, int y);

	int getWidth() const
	{
		return width;
	}

	int getHeight() const
	{
		return height;
	}

private:
	int width;
	int height;
	Item*** inventory;
};

