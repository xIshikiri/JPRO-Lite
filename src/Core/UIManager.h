#pragma once
#include <cstdint>
#include "GameInstance.h"
#include "IUIScreen.h"

class UIManager
{
public:
	UIManager();
	~UIManager();

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

