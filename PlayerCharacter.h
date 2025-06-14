#pragma once
#include "Character.h"

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(int level, int health, int strength, int dexterity, int inventoryWidth, int inventoryHeight)
		: Character(level, health, strength, dexterity, inventoryWidth, inventoryHeight)
	{
	}
	
	char getDisplayChar() const override { return '@'; }
};

