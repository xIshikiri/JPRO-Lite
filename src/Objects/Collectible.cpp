#include "Collectible.h"

#include "GameplayStatics.h"
#include "InventoryComponent.h"
#include "Item.h"
#include "Logger.h"

Collectible::Collectible(Item* item)
{
	if (item)
		this->item = new Item(*item); // Initialize the collectible with the provided item
}

Collectible::~Collectible()
{
	if (item)
	{
		delete item; // Clean up the item to avoid memory leaks
		item = nullptr; // Set item to nullptr after deletion
		DEBUG_LOG(LogLevel::INFO, "Collectible destroyed and item cleaned up.");
	}
	else
	{
		DEBUG_LOG(LogLevel::WARN, "Collectible destroyed but no item to clean up.");
	}
}

bool Collectible::onInteract()
{
	if (item)
	{
		DEBUG_LOG(LogLevel::INFO, "Collectible interacted with, item picked up: " << item->getName());
		if (InventoryComponent* playerInventory = GameplayStatics::getPlayerInventory())
		{
			if (playerInventory->placeItem(item)) // Attempt to add the item to the player's inventory
			{
				DEBUG_LOG(LogLevel::INFO, "Item " << item->getName() << " added to player's inventory.");
				item = nullptr; // Clear the item from the collectible after successful pickup
				return true;
			}
			else
			{
				DEBUG_LOG(LogLevel::ERR, "Failed to add item " << item->getName() << " to player's inventory.");
			}
		}
		else
		{
			DEBUG_LOG(LogLevel::ERR, "Player inventory not found, cannot add item.");
		}
		return false;
	}
	else
	{
		DEBUG_LOG(LogLevel::ERR, "Collectible interacted with but has no item to pick up.");
		return true; // Return false if no item is available to pick up
	}
}

Item* Collectible::getItem() const
{
	if (item)
	{
		return item; // Return the item contained in this collectible
	}
	DEBUG_LOG(LogLevel::ERR, "Collectible has no item to return.");
	return nullptr; // Return nullptr if no item is set
}
