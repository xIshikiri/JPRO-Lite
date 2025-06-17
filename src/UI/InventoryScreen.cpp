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
		if (auto* playerInventory = GameplayStatics::getPlayerInventory())
		{
			this->inventory = playerInventory; // Get the player's inventory if no inventory is provided
			DEBUG_LOG(LogLevel::INFO, "InventoryScreen initialized with player's inventory.");
		}
		else
		{
			this->inventory = nullptr; // Set inventory to nullptr if no inventory is found
			DEBUG_LOG(LogLevel::ERR, "Failed to initialize InventoryScreen: No inventory found.");
		}
	}
}

std::pair<int, int> InventoryScreen::getCoordinates() const
{
	if (!inventory)
	{
		DEBUG_LOG(LogLevel::ERR, "Inventory is not set, cannot get coordinates.");
		return { -1, -1 }; // Return invalid coordinates if inventory is not set
	}
	std::pair<int, int> coords = { 0, 0 }; // Default coordinates
	std::cout << "Enter coordinates (x y): ";
	std::cin >> coords.first >> coords.second; // Get coordinates from user input
	if (inventory->isSlotInBounds(coords.first, coords.second))
	{
		return coords; // Return the coordinates if they are within bounds
	}
	DEBUG_LOG(LogLevel::ERR, "Coordinates out of bounds: (" << coords.first << ", " << coords.second << ")");
	std::cout << "Coordinates out of bounds. Please try again.\n";
	return getCoordinates(); // Recursively get coordinates until valid input is provided
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
	std::cout << "----------------" << "\n"
		<< "1. Add Item" << "\n"
		<< "2. Use Item" << "\n"
		<< "3. Remove Item" << "\n"
		<< "4. Exit Inventory" << "\n";
}

void InventoryScreen::handleInput(char input)
{
	switch (input)
	{
	case '1':
	{
		std::pair<int, int> coords = getCoordinates();
		inventory->placeItem(coords.first, coords.second, new Item("New Item", "This is a new item", 2, 3));
		break;
	}
	case '2':
	{
		std::pair<int, int> coords = getCoordinates();
		if (Item* item = inventory->getItem(coords.first, coords.second))
		{
			std::cout << "Here, the " << inventory->getItem(coords.first, coords.second)->getName() << " would be used, but the programmer was too lazy to code it in at this time.\n";
			inventory->removeItem(coords.first, coords.second); // Remove the item after using it
		}
		else
		{
			std::cout << "No item found at the specified coordinates." << "\n";
		}
		system("pause"); // Wait for user input to continue
		break;
	}
	case '3':
	{
		std::pair<int, int> coords = getCoordinates();
		inventory->removeItem(coords.first, coords.second);
		break;
	}
	case '4':
		GameInstance::setCurrentState(GameState::MainMenu); // Exit inventory and return to main menu
		break;
	default:
		std::cout << "Invalid option. Please try again." << "\n";
		break;
	}
}
