#pragma once
#include <string>
#include "GameInstance.h"

class UIUtils {
public:
	static void clearScreen();
	static std::string gameStateToString(GameState state);
	static void renderGameWorld(WorldManager* worldManager);
};
