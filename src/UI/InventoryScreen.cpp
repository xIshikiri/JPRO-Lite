#include "InventoryScreen.h"

#include <iostream>
#include <ostream>

#include "GameInstance.h"
#include "GameplayStatics.h"
#include "InventoryComponent.h"
#include "PlayerCharacter.h"

void InventoryScreen::initialize()
{
	// Initialize the inventory screen - default to Player's inventory
	setInventory(nullptr);
}

void InventoryScreen::setInventory(InventoryComponent* inventory)
{
	if (inventory)
	{
		this->inventory = inventory; // Initialize the inventory pointer with the provided inventory
		DEBUG_LOG(LogLevel::INFO, "InventoryScreen initialized with provided inventory.");
	}
	else
	{
		// If no inventory is provided, try to get the player's inventory
		if (auto* playrInventory = GameplayStatics::getPlayerInventory())
		{
			this->inventory = inventory; // Get the player's inventory if no inventory is provided
			DEBUG_LOG(LogLevel::INFO, "InventoryScreen initialized with player's inventory.");
		}
		else
		{
			this->inventory = nullptr; // Set inventory to nullptr if no inventory is found
			DEBUG_LOG(LogLevel::ERR, "Failed to initialize InventoryScreen: No inventory found.");
		}
	}
}

void InventoryScreen::render() const
{
	// Render the inventory screen
	std::cout << "Inventory Screen" << "\n";
	std::cout << "----------------" << "\n";
	if (inventory)
	{
		for (int y = 0; y < inventory->getHeight(); ++y)
		{
			for (int x = 0; x < inventory->getWidth(); ++x)
			{
				Item* item = inventory->getItem(x, y);
				if (item)
				{
					std::cout << "[" << item->getDisplayChar() << "] ";
				}
				else
				{
					std::cout << "[ ] ";
				}
			}
			std::cout << "\n";
		}
	}
	else
	{
		DEBUG_LOG(LogLevel::WARN, "Inventory not found!");
	}
}

void InventoryScreen::handleInput(char input)
{
}
