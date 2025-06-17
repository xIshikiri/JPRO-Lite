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

Item* InventoryComponent::getItem(int x, int y) const
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
