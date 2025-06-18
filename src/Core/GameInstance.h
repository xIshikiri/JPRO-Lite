#pragma once
#include <cstdint>

class PlayerCharacter;
class WorldManager;
class CombatManager;
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
	static bool isInitializing() { return bIsInitializing; }

	void run(); // Start the game instance
	void update(); // Update the game instance
	void stop(); // Stop the game instance

	static GameState getCurrentState() { return instance->currentState; }
	static void setCurrentState(GameState state) { instance->currentState = state; }

	// Managers
	WorldManager* getWorldManager() const { return worldManager; }
	CombatManager* getCombatManager() const { return combatManager; }
	UIManager* getUIManager() const { return uiManager; }

	PlayerCharacter* getPlayerCharacter() const { return playerCharacter; }

private:
	// Private constructor to prevent instantiation disable copy and move operations
	GameInstance();
	~GameInstance();
	GameInstance(const GameInstance&) = delete;
	GameInstance& operator=(const GameInstance&) = delete;
	GameInstance(GameInstance&&) = delete;
	GameInstance& operator=(GameInstance&&) = delete;

	void initialize(); // Initialize the game instance
	static bool bIsInitializing; // Flag to check if the game instance is initializing
	bool bIsRunning = false; // Flag to check if the game instance is running

	static GameInstance* instance; // Singleton instance
	GameState currentState; // Current game state

	WorldManager* worldManager;
	CombatManager* combatManager;
	UIManager* uiManager;

	// Pointer to the player character
	PlayerCharacter* playerCharacter;

};

