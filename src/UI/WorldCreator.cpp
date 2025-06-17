#include "WorldCreator.h"

#include <iostream>
#include "GameInstance.h"
#include "PlayerCharacter.h"
#include "UIUtils.h"
#include "WorldManager.h"

void WorldCreator::initialize()
{
	worldManager = GameInstance::getInstance()->getWorldManager();
}

void WorldCreator::render() const
{
	UIUtils::renderGameWorld(worldManager);

	std::cout << "Choose what to place in the world:\n"
	<< "1. Player Character\n"
	<< "2. NPC Character\n"
	<< "3. Item\n"
	<< "4. Exit\n";
}

void WorldCreator::handleInput(char input)
{
	std::pair<int, int> coords = { 0, 0 }; // Default coordinates
	if (input != '4')
		coords = getCoordinates();
	switch (input)
	{
	case '1':
	{
		PlayerCharacter* player = new PlayerCharacter("Player", 1, 100, 10, 10, 5);
		worldManager->setEntity(coords.first, coords.second, player);
		std::cout << "Player Character placed at (" << coords.first << ", " << coords.second << ").\n";
		break;
	}
	case '2':
	{
		Character* npc = new Character("Stefan", 1, 50, 5, 5, 3);
		worldManager->setEntity(coords.first, coords.second, npc);
		std::cout << "NPC Character placed at (" << coords.first << ", " << coords.second << ").\n";
		break;
	}
	case '3':
	{
		Item* item = new Item("Health Potion", "Restores 50 health", 1, 1);
		worldManager->setEntity(coords.first, coords.second, item);
		std::cout << "Item placed at (" << coords.first << ", " << coords.second << ").\n";
		break;
	}
	case '4':
	{
		GameInstance::setCurrentState(GameState::MainMenu);
		break;
	}
	default:
	{
		std::cout << "Invalid choice. Please try again.\n";
		break;
	}
	}
}

std::pair<int, int> WorldCreator::getCoordinates()
{
	int x, y;
	std::cout << "Enter coordinates (x y): ";
	std::cin >> x >> y;
	if (!worldManager->isInBounds(x, y))
	{
		std::cout << "Coordinates out of bounds. Please try again.\n";
		return getCoordinates(); // Recursively ask for valid coordinates
	}
	return std::make_pair(x, y);
}
