#pragma once
#include <cstdint>
class WorldManager;
class TurnManager;
class UIManager;

enum class GameState : uint8_t
{
	MainMenu,
	WorldCreator,
	Exploration,
	Combat,
	Inventory,
	Dialogue,
	Exit
};

// Singleton
class GameInstance
{
public:

	static GameInstance* getInstance();
	static void destroyInstance();

	static GameState getCurrentState() { return instance->currentState; }
	static void setCurrentState(GameState state) { instance->currentState = state; }

	// Managers
	WorldManager* getWorldManager() const { return worldManager; }
	TurnManager* getTurnManager() const { return turnManager; }
	UIManager* getUIManager() const { return uiManager; }

	void run(); // Start the game instance
	void update(); // Update the game instance
	void stop(); // Stop the game instance

private:
	// Private constructor to prevent instantiation disable copy and move operations
	GameInstance();
	~GameInstance();
	GameInstance(const GameInstance&) = delete;
	GameInstance& operator=(const GameInstance&) = delete;
	GameInstance(GameInstance&&) = delete;
	GameInstance& operator=(GameInstance&&) = delete;

	bool bIsRunning = false; // Flag to check if the game instance is running

	static GameInstance* instance; // Singleton instance
	GameState currentState; // Current game state

	WorldManager* worldManager;
	TurnManager* turnManager;
	UIManager* uiManager;

};

