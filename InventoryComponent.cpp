#include "InventoryComponent.h"

InventoryComponent::InventoryComponent(int Width, int Height)
	:Width(Width), Height(Height), Inventory(nullptr)
{
	// Initialize the inventory with the given width and height
	Inventory = new Item**[Height];
	for (int i = 0; i < Height; ++i)
	{
		Inventory[i] = new Item*[Width];
		for (int j = 0; j < Width; ++j)
		{
			Inventory[i][j] = nullptr; // Initialize each slot to nullptr - no item
		}
	}
}

InventoryComponent::~InventoryComponent()
{
	// Clean up the inventory
	if (Inventory)
	{
		for (int i = 0; i < Height; ++i)
		{
			for (int j = 0; j < Width; ++j)
			{
				delete Inventory[i][j]; // Delete each item if it exists
			}
			delete[] Inventory[i]; // Delete the row
		}
		delete[] Inventory; // Delete the array of rows
	}
}

void InventoryComponent::AddItem(Item* item, int x, int y)
{

}

void InventoryComponent::GetItem(Item* item, int x, int y)
{
}

void InventoryComponent::RemoveItem(Item* item, int x, int y)
{
}
