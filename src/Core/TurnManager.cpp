#include "TurnManager.h"

TurnManager::TurnManager()
    : currentState(GameState::Exploration)
{
}

void TurnManager::setState(GameState state)
{
    currentState = state;
}

GameState TurnManager::getState() const
{
    return currentState;
}

void TurnManager::nextTurn()
{
	switch (currentState)
	{
	case GameState::Combat:
		// Logic for advancing combat turn
		break;
	case GameState::Exploration:
		// Logic for advancing exploration turn
		break;
	case GameState::Inventory:
		// Logic for handling inventory turn
		break;
	default:
		// Handle unexpected state
		break;
	}
}
