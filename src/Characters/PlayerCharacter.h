#pragma once
#include "Character.h"

class PlayerCharacter : public Character
{
public:
	PlayerCharacter(std::string name, int level, int health, int strength, int dexterity, int inventoryWidth, int inventoryHeight = 0);

	// IGameEntity interface
	char getDisplayChar() const override { return '@'; }
	bool isPlayer() const override { return true; }
};

