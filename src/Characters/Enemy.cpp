#include "Enemy.h"

#include "CombatManager.h"
#include "GameInstance.h"

Enemy::Enemy(const std::string& name, int level, int health, int strength, int dexterity, int inventoryWidth,
             int inventoryHeight = 0)
	: Character(name, level, health, strength, dexterity, inventoryWidth, inventoryHeight = 0)
{
}

bool Enemy::onInteract()
{
	// combat start logic
	DEBUG_LOG(LogLevel::INFO, "Enemy " << getName() << " interacted with.");
	if (isAlive())
	{
		GameInstance::getInstance()->getCombatManager()->startCombat(this); // Start combat with this enemy
		GameInstance::setCurrentState(GameState::Combat);
		return false; // Don't move onto the occupied tile
	}
	return true;
}
