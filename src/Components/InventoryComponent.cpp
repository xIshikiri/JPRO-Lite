#include "InventoryComponent.h"
#include <set>
#include "Items/Item.h"

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
	if (Inventory)
	{
		// Collect unique Item pointers and delete them later to avoid calling delete multiple times on the same item
		std::set<Item*> uniqueItems;
		for (int i = 0; i < Height; ++i) {
			for (int j = 0; j < Width; ++j)
			{
				if (Inventory[i][j] != nullptr) {
					uniqueItems.insert(Inventory[i][j]); // Insert unique items into the set
				}
			}
			delete[] Inventory[i];
		}
		delete[] Inventory;
		Inventory = nullptr; // Set Inventory to nullptr after deletion

		// Delete the unique items
		for (Item* item : uniqueItems)
		{
			delete item;
		}
	}
}

bool InventoryComponent::AddItem(Item* Item)
{
	// Find a valid slot in the inventory
	for (int i = 0; i < Height; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			// Check if the current slot is empty and if the item fits in the inventory
			if (Inventory[i][j] == nullptr && i + Item->GetHeight() <= Height && j + Item->GetWidth() <= Width)
			{
				// Found potential slot, check if the item can fit without overlapping other items
				bool bIsSlotValid = true;
				for (int k = 0; k < Item->GetHeight(); ++k)
				{
					for (int l = 0; l < Item->GetWidth(); ++l)
					{
						if (Inventory[i + k][j + l] != nullptr)
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
					for (int k = 0; k < Item->GetHeight(); ++k)
					{
						for (int l = 0; l < Item->GetWidth(); ++l)
						{
							Inventory[i + k][j + l] = Item; // Place the item in the slot
						}
					}
					return true; // Item added successfully
				}
			}
		}
	}
	return false; // No valid slot found, item not added
}

Item* InventoryComponent::GetItem(int x, int y)
{
	if (x < 0 || x >= Width || y < 0 || y >= Height)
	{
		return nullptr; // Out of bounds
	}
	return Inventory[y][x]; // Return the item at the specified coordinates
}

void InventoryComponent::RemoveItem(int x, int y)
{
	if (x < 0 || x >= Width || y < 0 || y >= Height)
	{
		return; // Out of bounds
	}

	if (Inventory[y][x] == nullptr)
	{
		return; // No item at the specified coordinates
	}

	// Save the item pointer to delete it later and avoid memory leaks
	Item* Item = Inventory[y][x];

	// Free the slots occupied by the item
	for (int i = 0; i < Height; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			if (Inventory[i][j] == Item)
			{
				Inventory[i][j] = nullptr; // Set the slot to nullptr
			}
		}
	}

	// Delete the item to free memory
	delete Item;
}
