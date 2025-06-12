#include <iostream>
#include "Character.h"

int main()
{
	Character* Player = new Character(1, 100, 10, 10, 10);
	std::cout << "Character created with inventory size: "
		<< Player->GetInventory()->GetWidth() << "x"
		<< Player->GetInventory()->GetHeight() << '\n';

	delete Player; // Clean up the character to avoid memory leaks

	return 0;
}
