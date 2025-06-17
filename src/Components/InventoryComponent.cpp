#include "InventoryComponent.h"
#include <set>

InventoryComponent::InventoryComponent(int width = 10, int height = 10)
	:width(width), height(height), inventory(nullptr)
{
	// Initialize the inventory with the given width and height
	inventory = new Item**[height];
	for (int i = 0; i < height; ++i)
	{
		inventory[i] = new Item*[width];
		for (int j = 0; j < width; ++j)
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

InventoryComponent::InventoryComponent(const InventoryComponent& other)
	: width(other.width), height(other.height)
{
	// Create a deep copy of the inventory
	inventory = new Item**[height];
	for (int i = 0; i < height; ++i)
	{
		inventory[i] = new Item*[width];
		for (int j = 0; j < width; ++j)
		{
			if (other.inventory[i][j] != nullptr)
			{
				inventory[i][j] = new Item(*other.inventory[i][j]); // Deep copy of the item
			}
			else
			{
				inventory[i][j] = nullptr; // No item in this slot
			}
		}
	}
}

InventoryComponent::InventoryComponent(InventoryComponent&& other) noexcept
	: width(other.width), height(other.height), inventory(other.inventory)
{
	// Transfer ownership of the inventory
	other.inventory = nullptr; // Set the moved-from object's inventory to nullptr
	other.width = 0;
	other.height = 0;
}

InventoryComponent& InventoryComponent::operator=(const InventoryComponent& other)
{
	if (this != &other) // Check for self-assignment
	{
		width = other.width;
		height = other.height;

		// Clean up existing inventory
		for (int i = 0; i < height; ++i)
		{
			delete[] inventory[i];
		}
		delete[] inventory;

		// Create a deep copy of the inventory
		inventory = new Item**[height];
		for (int i = 0; i < height; ++i)
		{
			inventory[i] = new Item*[width];
			for (int j = 0; j < width; ++j)
			{
				if (other.inventory[i][j] != nullptr)
				{
					inventory[i][j] = new Item(*other.inventory[i][j]); // Deep copy of the item
				}
				else
				{
					inventory[i][j] = nullptr; // No item in this slot
				}
			}
		}
	}
	return *this;
}

InventoryComponent& InventoryComponent::operator=(InventoryComponent&& other) noexcept
{
	if (this != &other) // Check for self-assignment
	{
		width = other.width;
		height = other.height;

		// Clean up existing inventory
		for (int i = 0; i < height; ++i)
		{
			delete[] inventory[i];
		}
		delete[] inventory;
		inventory = other.inventory; // Transfer ownership of the inventory
		other.inventory = nullptr; // Set the moved-from object's inventory to nullptr
		other.width = 0;
		other.height = 0;
	}
	return *this;
}

bool InventoryComponent::placeItem(Item* item)
{
	// Find a valid slot in the inventory
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (placeItem(i, j, item))
			{
				return true; // Item successfully placed in the first valid slot found
			}
			if (item->rotateItem()) // Try rotating the item if placement failed
			{
				if (placeItem(i, j, item))
				{
					return true; // Item successfully placed after rotation
				}
				item->rotateItem(); // Rotate back to original orientation if placement failed
			}
		}
	}
	return false; // No valid slot found, item not added
}

bool InventoryComponent::placeItem(int x, int y, Item* item)
{
	if (canPlaceItemAt(x, y, item))
	{
		// Place the item at the specified coordinates
		for (int i = 0; i < item->getHeight(); ++i)
		{
			for (int j = 0; j < item->getWidth(); ++j)
			{
				int newX = x + j;
				int newY = y + i;
				inventory[newY][newX] = item; // Set the item in the inventory
			}
		}
		return true; // Item successfully placed
	}
	return false; // Cannot place item at the specified coordinates
}

Item* InventoryComponent::getItem(int x, int y) const
{
	if (!isSlotInBounds(x, y))
		return nullptr; // Out of bounds
	return inventory[y][x]; // Return the item at the specified coordinates
}

void InventoryComponent::removeItem(int x, int y)
{
	if (!isSlotInBounds(x, y))
		return; // Out of bounds

	if (getItem(x, y) == nullptr)
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

bool InventoryComponent::isSlotInBounds(int x, int y) const
{
	return (x >= 0 && x < width && y >= 0 && y < height); // Check if the coordinates are within the inventory bounds
}

bool InventoryComponent::isSlotValid(int x, int y) const
{
	if (!isSlotInBounds(x, y))
	{
		return false; // Out of bounds
	}
	return inventory[y][x] == nullptr; // Return true if the slot is empty
}

bool InventoryComponent::canPlaceItemAt(int x, int y, Item* item) const
{
	if (item)
	{
		if (x + item->getWidth() > width || y + item->getHeight() > height)
		{
			return false; // Item does not fit in the specified coordinates
		}
		for (int i = 0; i < item->getHeight(); ++i)
		{
			for (int j = 0; j < item->getWidth(); ++j)
			{
				int newX = x + j;
				int newY = y + i;
				if (!isSlotValid(newX, newY))
				{
					return false; // Slot is not valid for placing the item
				}
			}
		}
		return true; // All slots are valid for placing the item
	}
	return false; // Item is null, cannot place it
}
