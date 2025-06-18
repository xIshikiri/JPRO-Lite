#pragma once
#include "InventoryComponent.h"
#include "IGameEntity.h"

class Character : public IGameEntity
{
public:
	Character(std::string name, int level, int health, int strength, int dexterity, int inventoryWidth, int inventoryHeight = 0);
	~Character() override;
	Character(const Character& other);
	Character& operator=(const Character& other);
	Character(Character&& other) noexcept;
	Character& operator=(Character&& other) noexcept;

	// IGameEntity interface
	virtual char getDisplayChar() const override { return 'N'; }
	EntityType getEntityType() const override { return EntityType::Dialogue; }
	bool onInteract() override;

	bool Attack(Character* other);
	int TakeDamage(int damage);
	void heal(int health);

	InventoryComponent* getInventory() const
	{
		return inventory;
	}

	std::string getName() const
	{
		return name;
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

	void setStrength(int strength) { this->strength = strength; }

	int getDexterity() const
	{
		return dexterity;
	}

	bool isAlive() const
	{
		return health > 0;
	}

private:
	std::string name; // Optional name for the character, can be set later

	// Stats
	int level;
	int health;
	int strength;
	int dexterity;

	//Components
	InventoryComponent* inventory;
};
