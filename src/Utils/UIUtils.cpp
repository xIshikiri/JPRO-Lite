#include "UIUtils.h"
#include <cstdlib>
#include <iostream>

#include "GameInstance.h"
#include "Logger.h"
#include "WorldManager.h"

void UIUtils::clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

std::string UIUtils::gameStateToString(GameState state)
{
	switch (state)
	{
	case GameState::MainMenu:
		return "Main Menu";
	case GameState::WorldCreator:
		return "World Creator";
	case GameState::Exploration:
		return "Exploration";
	case GameState::Combat:
		return "Combat";
	case GameState::Inventory:
		return "Inventory";
	case GameState::Dialogue:
		return "Dialogue";
	case GameState::Exit:
		return "Exit";
	default:
		return "Unknown State";
	}
}

void UIUtils::renderGameWorld(WorldManager* worldManager)
{
	if (!worldManager)
	{
		DEBUG_LOG(LogLevel::ERR, "WorldManager is null, cannot render game world.");
		return;
	}
	for (int y = 0; y < WorldManager::HEIGHT; ++y)
	{
		for (int x = 0; x < WorldManager::WIDTH; ++x)
		{
			const Tile& tile = worldManager->getTile(x, y);
			if (tile.entity)
			{
				// If there's an entity, display its character
				std::cout << tile.entity->getDisplayChar() << ' ';
			}
			else
			{
				// Otherwise, display the terrain character
				std::cout << tile.getDisplayChar() << ' ';
			}
		}
		std::cout << '\n';
	}
}
