#pragma once
#include <cstdint>

enum class GameState : uint8_t
{
	Combat,
	Exploration,
	Inventory    // Inventory management
};

class TurnManager
{
public:
    TurnManager();

    void setState(GameState state);
    GameState getState() const;

    void nextTurn(); // Advances the turn depending on state

private:
    GameState currentState;
    // Add more fields as needed, e.g., list of combatants, current turn index, etc.
};
