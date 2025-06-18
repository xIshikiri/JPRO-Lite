#include "Enemy.h"

Enemy::Enemy(const std::string& name, int level, int health, int strength, int dexterity, int inventoryWidth,
	int inventoryHeight = 0)
	: Character(name, level, health, strength, dexterity, inventoryWidth, inventoryHeight = 0)
{
}

bool Enemy::onInteract()
{
	// combat start logic
	DEBUG_LOG(LogLevel::INFO, "Enemy " << getName() << " interacted with.");
	return true; // Indicate that the interaction was successful
}
