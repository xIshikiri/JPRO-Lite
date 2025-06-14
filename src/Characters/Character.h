#pragma once
#include "InventoryComponent.h"
#include "IGameEntity.h"

class Character : public IGameEntity
{
public:
	Character(int level, int health, int strength, int dexterity, int inventoryWidth, int inventoryHeight = 0);
	~Character() override;
	Character(const Character& other);
	Character& operator=(const Character& other);
	Character(Character&& other) noexcept;
	Character& operator=(Character&& other) noexcept;

	// IGameEntity interface
	virtual char getDisplayChar() const override { return 'C'; }

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
