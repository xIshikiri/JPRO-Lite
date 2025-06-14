#include <iostream>

#include "Character.h"
#include "Logger.h"
#include "PlayerCharacter.h"
#include "UIUtils.h"
#include "WorldManager.h"

int main()
{
	WorldManager* worldManager = new WorldManager();
	worldManager->render();

	int choice, x = 0, y = 0;
	bool bContinue = true;

	// Main loop for placing entities in the world
	do {

		std::cout << "Choose what to place in the world:\n"
			<< "1. Player Character\n"
			<< "2. NPC Character\n"
			<< "3. Item\n"
			<< "4. Exit\n";
		std::cin >> choice;
		if (choice != 4)
		{
			std::cout << "Enter coordinates (x y): ";
			std::cin >> x >> y;
			if (!worldManager->isInBounds(x, y))
			{
				UIUtils::clearScreen();
				worldManager->render();
				std::cout << "Coordinates out of bounds. Please try again.\n";
				continue; // Skip to the next iteration if out of bounds
			}
		}

		switch (choice)
		{
			case 1:
			{
				PlayerCharacter* player = new PlayerCharacter(1, 100, 10, 10, 5);
				worldManager->setEntity(x, y, player);
				std::cout << "Player Character placed at (" << x << ", " << y << ").\n";
				break;
			}
			case 2:
			{
				Character* npc = new Character(1, 50, 5, 5, 3);
				worldManager->setEntity(x, y, npc);
				std::cout << "NPC Character placed at (" << x << ", " << y << ").\n";
				break;
			}
			case 3:
			{
				Item* item = new Item("Health Potion", "Restores 50 health", 1, 1);
				worldManager->setEntity(x, y, item);
				std::cout << "Item placed at (" << x << ", " << y << ").\n";
				break;
			}
			case 4:
			{
				bContinue = false; // Exit the loop
				std::cout << "Exiting...\n";
				break;
			}
			default:
			{
				std::cout << "Invalid choice. Please try again.\n";
				break;
			}
		}
		if (choice != 4)
			UIUtils::clearScreen();
			worldManager->render(); // Render the world after each placement
	} while (choice != 4);

	delete worldManager;

	return 0;
}
