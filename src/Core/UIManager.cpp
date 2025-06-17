#include "UIManager.h"

#include <iostream>

#include "CombatScreen.h"
#include "DialogueScreen.h"
#include "ExplorationScreen.h"
#include "InventoryScreen.h"
#include "Logger.h"
#include "MainMenuScreen.h"
#include "UIUtils.h"
#include "WorldCreator.h"

UIManager::UIManager()
{
	mainMenuScreen = new MainMenuScreen();
	worldCreatorScreen = new WorldCreator();
	explorationScreen = new ExplorationScreen();
	combatScreen = new CombatScreen();
	inventoryScreen = new InventoryScreen();
	dialogueScreen = new DialogueScreen();
	currentScreen = nullptr;
	DEBUG_LOG(LogLevel::INFO, "UIManager initialized with main menu screen.");
}

UIManager::~UIManager()
{
	delete mainMenuScreen;
	delete worldCreatorScreen;
	delete explorationScreen;
	delete combatScreen;
	delete inventoryScreen;
	delete dialogueScreen;
	currentScreen = nullptr; // Reset current screen pointer
	DEBUG_LOG(LogLevel::INFO, "UIManager destroyed and all screens cleaned up.");
}

void UIManager::setScreen(GameState state)
{
	switch (state)
	{
	case GameState::MainMenu:
		currentScreen = mainMenuScreen;
		break;
	case GameState::WorldCreator:
		currentScreen = worldCreatorScreen;
		break;
	case GameState::Exploration:
		currentScreen = explorationScreen;
		break;
	case GameState::Combat:
		currentScreen = combatScreen;
		break;
	case GameState::Inventory:
		currentScreen = inventoryScreen;
		break;
	case GameState::Dialogue:
		currentScreen = dialogueScreen;
		break;
	case GameState::Exit:
		UIUtils::clearScreen(); // Clear the screen for exit state
		return; // No screen to set for exit state
	default:
		DEBUG_LOG(LogLevel::WARN, "Attempted to set an invalid game state screen.");
		return; // Invalid state, do nothing
	}
	DEBUG_LOG(LogLevel::INFO, "UIManager switched to screen for state: " << UIUtils::gameStateToString(state));
}

void UIManager::update()
{
	if (currentScreen)
	{
		currentScreen->render(); // Render the current screen
		char input;
		std::cin >> input; // Get user input
		currentScreen->handleInput(input); // Handle input for the current screen
		UIUtils::clearScreen(); // Clear the screen after handling input
	}
	else
	{
		DEBUG_LOG(LogLevel::ERR, "Current screen is null, cannot render.");
	}
}
