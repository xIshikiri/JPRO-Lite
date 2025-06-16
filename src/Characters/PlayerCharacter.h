#pragma once
#include "Character.h"

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(std::string name, int level, int health, int strength, int dexterity, int inventoryWidth, int inventoryHeight = 0)
		: Character(name, level, health, strength, dexterity, inventoryWidth, inventoryHeight)
	{
	}
	
	char getDisplayChar() const override { return '@'; }
};

