#include "Character.h"

Character::Character(int level, int health, int strength, int dexterity, int inventoryWidth, int inventoryHeight)
	: level(level), health(health), strength(strength), dexterity(dexterity)
{
	if (inventoryHeight == 0)
	{
		inventoryHeight = inventoryWidth; // Default to square inventory if height is not specified
	}
	inventory = new InventoryComponent(inventoryWidth, inventoryHeight);
}
