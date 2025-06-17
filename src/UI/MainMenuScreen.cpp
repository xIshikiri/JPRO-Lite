#include "MainMenuScreen.h"

#include <iostream>

#include "GameInstance.h"

void MainMenuScreen::initialize()
{
}

void MainMenuScreen::render() const
{
	// Render the main menu screen
	std::cout << "Welcome to the Game!" << "\n"
		<< "Please select an option:" << "\n"
		<< "1. Start Exploration" << "\n"
		<< "2. Create World" << "\n"
		<< "3. Open Inventory" << "\n"
		<< "4. Exit Game" << "\n";
}

void MainMenuScreen::handleInput(char input)
{
	switch (input)
	{
	case '1':
		GameInstance::setCurrentState(GameState::Exploration);
		break;
	case '2':
		GameInstance::setCurrentState(GameState::WorldCreator);
		break;
	case '3':
		GameInstance::setCurrentState(GameState::Inventory);
		break;
	case '4':
		GameInstance::setCurrentState(GameState::Exit);
		break;
	default:
		std::cout << "Invalid option. Please try again." << std::endl;
		break;
	}
}
