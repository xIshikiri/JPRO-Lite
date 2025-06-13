#pragma once
#include "../Components/InventoryComponent.h"

class Character
{
public:
	Character(int level, int health, int strength, int dexterity, int inventoryWidth, int inventoryHeight = 0);

	InventoryComponent* GetInventory() const
	{
		return inventory;
	}



private:
	// Stats
	int level;
	int health;
	int strength;
	int dexterity;

	//Components
	InventoryComponent* inventory;
};

