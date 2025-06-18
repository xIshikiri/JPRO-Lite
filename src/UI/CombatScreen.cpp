#include "CombatScreen.h"

#include <chrono>
#include <iostream>

#include "CombatManager.h"
#include "Enemy.h"
#include "GameInstance.h"
#include "GameplayStatics.h"
#include "PlayerCharacter.h"

void CombatScreen::initialize()
{
	combatManager = GameInstance::getInstance()->getCombatManager();
}

void CombatScreen::render() const
{
	std::cout << "Combat Screen" << "\n"
		<< "Current Enemy: " << (combatManager->getCurrentEnemy() ? combatManager->getCurrentEnemy()->getName() : "None") << "\n"
		<< "Enemy Health: " << (combatManager->getCurrentEnemy() ? combatManager->getCurrentEnemy()->getHealth() : 0) << "\n"
		<< "Player Health: " << GameInstance::getInstance()->getPlayerCharacter()->getHealth() << "\n";
	if (combatManager->isPlayerTurn())
	{
		std::cout << "It's your turn to attack!" << "\n";
	}
	else
	{
		std::cout << "Waiting for enemy's turn..." << "\n";
		// wait for 1 second
		auto start = std::chrono::steady_clock::now();
		while (std::chrono::steady_clock::now() - start < std::chrono::seconds(1))
		{
			// Simulate waiting for the enemy's turn
		}
		std::cout << "Enemy " << (combatManager->getCurrentEnemy() ? combatManager->getCurrentEnemy()->getName() : "Unknown")
			<< " attacks!" << "\n";
	}
	combatManager->update(); // Update the combat manager to process the turn
	std::cout << "Press any key to continue..." << "\n";
}

void CombatScreen::handleInput(char input)
{
	if (GameInstance::getCurrentState() == GameState::Exploration)
	{
		std::cout << "Combat ended. Returning to exploration." << "\n";
		auto start = std::chrono::steady_clock::now();
		while (std::chrono::steady_clock::now() - start < std::chrono::seconds(1))
		{
			// Give the player a second to read the message before returning to exploration
		}
	}
	if (!GameplayStatics::getPlayerCharacter()->isAlive())
	{
		std::cout << "You have been defeated! Game Over." << "\n";
		GameInstance::setCurrentState(GameState::Exit); // Exit the game if player is defeated
	}
}

