#pragma once
#include "../Components/InventoryComponent.h"

class Character
{
public:
	Character(int level, int health, int strength, int dexterity, int inventoryWidth, int inventoryHeight = 0);

	InventoryComponent* getInventory() const
	{
		return inventory;
	}

	int getLevel() const
	{
		return level;
	}

	int getHealth() const
	{
		return health;
	}

	int getStrength() const
	{
		return strength;
	}

	int getDexterity() const
	{
		return dexterity;
	}

	bool isAlive() const
	{
		return health > 0;
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

