#include "ExplorationScreen.h"

#include <iostream>

#include "GameInstance.h"
#include "UIUtils.h"
#include "WorldManager.h"

void ExplorationScreen::initialize()
{
	worldManager = GameInstance::getInstance()->getWorldManager();
}

void ExplorationScreen::render() const
{
	UIUtils::renderGameWorld(worldManager);
	std::cout << "Exploration Screen" << std::endl;
	std::cout << "Use WASD to move, Q to quit." << std::endl;
}

void ExplorationScreen::handleInput(char input)
{
	std::pair<int, int> playerLocation = worldManager->getPlayerPosition();
	switch (input)
	{
	case 'w': // Move up
		worldManager->movePlayer(playerLocation.first, playerLocation.second - 1);
		break;
	case 's': // Move down
		worldManager->movePlayer(playerLocation.first, playerLocation.second + 1);
		break;
	case 'a': // Move left
		worldManager->movePlayer(playerLocation.first - 1, playerLocation.second);
		break;
	case 'd': // Move right
		worldManager->movePlayer(playerLocation.first + 1, playerLocation.second);
		break;
	case 'i': // Open inventory
		GameInstance::setCurrentState(GameState::Inventory);
		break;
	case 'q': // Quit exploration
		GameInstance::setCurrentState(GameState::MainMenu);
		break;
	}
}
