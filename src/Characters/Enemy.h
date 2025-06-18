#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy(const std::string& name, int level, int health, int strength, int dexterity, int inventoryWidth,
		int inventoryHeight);
	char getDisplayChar() const override { return 'E'; }
	EntityType getEntityType() const override { return EntityType::Combat;  }
	bool onInteract() override;
};

