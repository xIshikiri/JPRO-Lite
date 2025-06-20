#include "WorldCreator.h"

#include <iostream>

#include "Collectible.h"
#include "Enemy.h"
#include "GameInstance.h"
#include "PlayerCharacter.h"
#include "UIUtils.h"
#include "WorldManager.h"

void aggressiveBehavior(Enemy& enemy)
{
	enemy.setStrength(enemy.getStrength() + 1);
	std::cout << "Enemy raised their strengh by one!\n";
}

void defensiveBehavior(Enemy& enemy)
{
	enemy.heal(5);
	std::cout << "Enemy healed for 5 health!\n";
}

void WorldCreator::initialize()
{
	worldManager = GameInstance::getInstance()->getWorldManager();
}

void WorldCreator::render() const
{
	UIUtils::renderGameWorld(worldManager);

	std::cout << "Choose what to place in the world:\n"
	<< "1. Aggressive enemy\n"
	<< "2. Defensive enemy\n"
	<< "3. NPC Character\n"
	<< "4. Item\n"
	<< "5. Exit\n";
}

void WorldCreator::handleInput(char input)
{
	std::pair<int, int> coords = { 0, 0 }; // Default coordinates
	if (input != '5')
		coords = getCoordinates();
	switch (input)
	{
	case '1':
	{
		Enemy* enemy = new Enemy(aggressiveBehavior, "Agresywny Zbir", 1, 35, 5, 8, 5, 5);
		worldManager->setEntity(coords.first, coords.second, enemy);
		std::cout << "Aggressive Enemy placed at (" << coords.first << ", " << coords.second << ").\n";
		break;
	}
	case '2':
	{
		Enemy* enemy = new Enemy(defensiveBehavior, "Defensywny Zbir", 1, 30, 5, 6, 5, 5);
		worldManager->setEntity(coords.first, coords.second, enemy);
		std::cout << "Defensive Enemy placed at (" << coords.first << ", " << coords.second << ").\n";
		break;
	}
	case '3':
	{
		Character* npc = new Character("Stefan", 1, 50, 5, 5, 3);
		worldManager->setEntity(coords.first, coords.second, npc);
		std::cout << "NPC Character placed at (" << coords.first << ", " << coords.second << ").\n";
		break;
	}
	case '4':
	{
		Item* item = new Item("Health Potion", "Restores 50 health", 1, 2);
		worldManager->setEntity(coords.first, coords.second, new Collectible(item));
		std::cout << "Item placed at (" << coords.first << ", " << coords.second << ").\n";
		break;
	}
	case '5':
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
