#include "InventoryComponent.h"
#include <set>
#include "Items/Item.h"

InventoryComponent::InventoryComponent(int Width, int Height)
	:width(Width), height(Height), inventory(nullptr)
{
	// Initialize the inventory with the given width and height
	inventory = new Item**[Height];
	for (int i = 0; i < Height; ++i)
	{
		inventory[i] = new Item*[Width];
		for (int j = 0; j < Width; ++j)
		{
			inventory[i][j] = nullptr; // Initialize each slot to nullptr - no item
		}
	}
}

InventoryComponent::~InventoryComponent()
{
	if (inventory)
	{
		// Collect unique Item pointers and delete them later to avoid calling delete multiple times on the same item
		std::set<Item*> uniqueItems;
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j)
			{
				if (inventory[i][j] != nullptr) {
					uniqueItems.insert(inventory[i][j]); // Insert unique items into the set
				}
			}
			delete[] inventory[i];
		}
		delete[] inventory;
		inventory = nullptr; // Set Inventory to nullptr after deletion

		// Delete the unique items
		for (Item* item : uniqueItems)
		{
			delete item;
		}
	}
}

bool InventoryComponent::addItem(Item* item)
{
	// Find a valid slot in the inventory
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			// Check if the current slot is empty and if the item fits in the inventory
			if (inventory[i][j] == nullptr && i + item->getHeight() <= height && j + item->getWidth() <= width)
			{
				// Found potential slot, check if the item can fit without overlapping other items
				bool bIsSlotValid = true;
				for (int k = 0; k < item->getHeight(); ++k)
				{
					for (int l = 0; l < item->getWidth(); ++l)
					{
						if (inventory[i + k][j + l] != nullptr)
						{
							bIsSlotValid = false; // Slot is not valid as it overlaps with another item
							break;
						}
					}
					if (!bIsSlotValid) break; // Exit early if slot is invalid
				}
				if (bIsSlotValid)
				{
					// Place the item in the inventory
					for (int k = 0; k < item->getHeight(); ++k)
					{
						for (int l = 0; l < item->getWidth(); ++l)
						{
							inventory[i + k][j + l] = item; // Place the item in the slot
						}
					}
					return true; // Item added successfully
				}
			}
		}
	}
	return false; // No valid slot found, item not added
}

Item* InventoryComponent::getItem(int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return nullptr; // Out of bounds
	}
	return inventory[y][x]; // Return the item at the specified coordinates
}

void InventoryComponent::removeItem(int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		return; // Out of bounds
	}

	if (inventory[y][x] == nullptr)
	{
		return; // No item at the specified coordinates
	}

	// Save the item pointer to delete it later and avoid memory leaks
	Item* item = inventory[y][x];

	// Free the slots occupied by the item
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (inventory[i][j] == item)
			{
				inventory[i][j] = nullptr; // Set the slot to nullptr
			}
		}
	}

	// Delete the item to free memory
	delete item;
}
