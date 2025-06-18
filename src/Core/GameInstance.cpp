#include "GameInstance.h"

#include "Logger.h"
#include "PlayerCharacter.h"
#include "CombatManager.h"
#include "UIManager.h"
#include "WorldManager.h"

GameInstance* GameInstance::instance = nullptr;
bool GameInstance::bIsInitializing = false; // Static flag to check if the game instance is initializing

GameInstance::GameInstance()
	:currentState()
{
	playerCharacter = new PlayerCharacter("Player", 1, 20, 10, 10, 10); // Initialize player character
	worldManager = new WorldManager();
	combatManager = new CombatManager();
	uiManager = new UIManager();
}

GameInstance::~GameInstance()
{
	delete worldManager;
	delete combatManager;
	delete uiManager;
}

GameInstance* GameInstance::getInstance()
{
	if (!instance)
	{
		if (isInitializing())
		{
			DEBUG_LOG(LogLevel::ERR, "GameInstance is already being initialized.");
			return nullptr; // Prevent re-initialization if already in progress
		}

		bIsInitializing = true;
		instance = new GameInstance();
		instance->initialize(); // Initialize managers
		bIsInitializing = false;

		DEBUG_LOG(LogLevel::INFO, "GameInstance created.");
	}
	return instance;
}

void GameInstance::initialize()
{
	if (bIsRunning)
	{
		DEBUG_LOG(LogLevel::WARN, "GameInstance is already initialized and running.");
		return; // Prevent re-initialization if already running
	}
	if (instance)
	{
		worldManager->initialize(); // Initialize the world manager
		combatManager->initialize(); // Initialize the turn manager
		uiManager->initialize(); // Initialize the UI manager and its screens
		DEBUG_LOG(LogLevel::INFO, "GameInstance initialized with WorldManager, CombatManager, and UIManager.");
	}
	else
	{
		DEBUG_LOG(LogLevel::ERR, "GameInstance is not created yet. Call getInstance() first.");
	}
}

void GameInstance::destroyInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
	else
	{
		DEBUG_LOG(LogLevel::WARN, "GameInstance is already destroyed or not created yet.");
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
