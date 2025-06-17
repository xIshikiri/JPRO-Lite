#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(std::string name, int level, int health, int strength, int dexterity, int inventoryWidth, int inventoryHeight)
	: Character(std::move(name), level, health, strength, dexterity, inventoryWidth, inventoryHeight)
{
}
