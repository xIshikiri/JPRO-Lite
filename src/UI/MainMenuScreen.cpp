#include "MainMenuScreen.h"

#include <iostream>

#include "GameInstance.h"

void MainMenuScreen::render() const
{
	// Render the main menu screen
	std::cout << "Welcome to the Game!" << std::endl;
	std::cout << "1. Start Game" << std::endl;
	std::cout << "2. World Creator" << std::endl;
	std::cout << "3. Exit" << std::endl;
	std::cout << "Please select an option: ";
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
		GameInstance::setCurrentState(GameState::Exit);
		break;
	default:
		std::cout << "Invalid option. Please try again." << std::endl;
		break;
	}
}
