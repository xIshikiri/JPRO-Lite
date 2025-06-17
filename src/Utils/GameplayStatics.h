#pragma once
#include <utility>

class InventoryComponent;
class PlayerCharacter;

class GameplayStatics
{
public:
	// Only call AFTER the game instance has been initialized
	static PlayerCharacter* getPlayerCharacter();
	static InventoryComponent* getPlayerInventory();
	static std::pair<int, int> getPlayerLocation();
};

