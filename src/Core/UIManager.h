#pragma once
#include <cstdint>
#include "IUIScreen.h"

enum class GameState : uint8_t;

class UIManager
{
public:
	UIManager();
	~UIManager();

	void initialize(); // Initialize the UI manager and its screens

	void setScreen(GameState state);
	void update();

private:
	IUIScreen* currentScreen; // Pointer to the current screen being displayed

	// Screens for different game states
	IUIScreen* mainMenuScreen;
	IUIScreen* worldCreatorScreen;
	IUIScreen* explorationScreen;
	IUIScreen* combatScreen;
	IUIScreen* inventoryScreen;
	IUIScreen* dialogueScreen;
};

