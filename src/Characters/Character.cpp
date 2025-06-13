#include "Character.h"
#include "Core/Logger.h"

Character::Character(int level, int health, int strength, int dexterity, int inventoryWidth, int inventoryHeight)
	: level(level), health(health), strength(strength), dexterity(dexterity)
{
	if (inventoryHeight == 0)
	{
		inventoryHeight = inventoryWidth; // Default to square inventory if height is not specified
	}
	inventory = new InventoryComponent(inventoryWidth, inventoryHeight);

	DEBUG_LOG(LogLevel::INFO, "Character created with stats: " << "\n"
		<< "Level: " << getLevel() << "\n"
		<< "Health: " << getHealth() << "\n"
		<< "Strength: " << getStrength() << "\n"
		<< "Dexterity: " << getDexterity() << "\n");
}
