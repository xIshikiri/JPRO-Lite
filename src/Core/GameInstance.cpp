#include "GameInstance.h"

#include "Logger.h"
#include "TurnManager.h"
#include "UIManager.h"
#include "WorldManager.h"

GameInstance* GameInstance::instance = nullptr;

GameInstance::GameInstance()
	:currentState()
{
	worldManager = new WorldManager();
	turnManager = new TurnManager();
	uiManager = new UIManager();
}

GameInstance::~GameInstance()
{
	delete worldManager;
	delete turnManager;
	delete uiManager;
}

GameInstance* GameInstance::getInstance()
{
	if (!instance)
	{
		instance = new GameInstance();
		DEBUG_LOG(LogLevel::INFO, "GameInstance created.");
	}
	return instance;
}

void GameInstance::destroyInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void GameInstance::run()
{
	if (bIsRunning)
	{
		DEBUG_LOG(LogLevel::WARN, "GameInstance is already running.");
		return; // Prevent starting if already running
	}

	bIsRunning = true; // Set running flag to true
	currentState = GameState::MainMenu; // Set initial state to Main Menu
	DEBUG_LOG(LogLevel::INFO, "GameInstance started with Main Menu.");

	while (bIsRunning) {
		update(); // Call the tick function to update the game state
	}
}

void GameInstance::update()
{
	if (currentState == GameState::Exit) {
		stop();
		return;
	}
	uiManager->setScreen(currentState); // Set the current UI screen based on the game state
	uiManager->update(); // Render the current UI screen
}

void GameInstance::stop()
{
	if (!bIsRunning)
	{
		DEBUG_LOG(LogLevel::WARN, "GameInstance is not running.");
		return; // Prevent stopping if not running
	}
	bIsRunning = false; // Set running flag to false
	DEBUG_LOG(LogLevel::INFO, "GameInstance stopped.");
}
