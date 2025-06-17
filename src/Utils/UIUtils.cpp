#include "UIUtils.h"
#include <cstdlib>

#include "GameInstance.h"

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
