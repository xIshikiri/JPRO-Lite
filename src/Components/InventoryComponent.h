#pragma once
#include "Item.h"

class InventoryComponent
{
public:
	InventoryComponent(int width, int height);
	~InventoryComponent();
	InventoryComponent(const InventoryComponent& other);
	InventoryComponent(InventoryComponent&& other) noexcept;
	InventoryComponent& operator=(const InventoryComponent& other);
	InventoryComponent& operator=(InventoryComponent&& other) noexcept;

	bool placeItem(Item* item);
	bool placeItem(int x, int y, Item* item);
	Item* getItem(int x, int y) const;
	void removeItem(int x, int y);

	bool isSlotInBounds(int x, int y) const;
	bool isSlotValid(int x, int y) const;
	bool canPlaceItemAt(int x, int y, Item* item) const;

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

