#pragma once
#include <cstdint>

class Enemy;

class CombatManager
{
public:
	void initialize(); // Initialize the turn manager
	void update(); // Update the combat manager
	void startCombat(Enemy* enemy); // Start combat with the specified enemy

	Enemy* getCurrentEnemy() const { return currentEnemy; } // Get the current enemy in combat
	bool isPlayerTurn() const { return bPlayerTurn; } // Check if it's the player's turn
private:
	Enemy* currentEnemy; // Pointer to the current enemy in combat
	bool bPlayerTurn;
};
