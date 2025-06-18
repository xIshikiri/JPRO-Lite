#include "CombatManager.h"

#include "Enemy.h"
#include "GameInstance.h"
#include "GameplayStatics.h"
#include "PlayerCharacter.h"

void CombatManager::initialize()
{
}

void CombatManager::update()
{
	if (currentEnemy == nullptr)
	{
		DEBUG_LOG(LogLevel::ERR, "CombatManager: No current enemy set for combat.");
		GameInstance::setCurrentState(GameState::Exploration); // Return to exploration state if no enemy
		return; // No enemy to combat with
	}
	if (bPlayerTurn)
	{
		GameplayStatics::getPlayerCharacter()->Attack(currentEnemy); // Player attacks the enemy
		if (!currentEnemy->isAlive())
		{
			DEBUG_LOG(LogLevel::INFO, "CombatManager: Enemy defeated.");
			currentEnemy = nullptr; // Clear the current enemy if defeated
			GameInstance::setCurrentState(GameState::Exploration); // Return to exploration state
		}
	}
	else
	{
		currentEnemy->getBehavior()(*currentEnemy); // Execute the enemy's behavior function
		currentEnemy->Attack(GameplayStatics::getPlayerCharacter()); // Enemy attacks the player
	}
	bPlayerTurn = !bPlayerTurn; // Toggle turn after each action
}

void CombatManager::startCombat(Enemy* enemy)
{
	currentEnemy = enemy; // Set the current enemy for combat
	if (GameplayStatics::getPlayerCharacter()->getDexterity() > enemy->getDexterity())
	{
		bPlayerTurn = true; // Player goes first if their dexterity is higher
	}
	else
	{
		bPlayerTurn = false; // Enemy goes first otherwise
	}
}
