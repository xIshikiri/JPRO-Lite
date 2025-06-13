#include <iostream>

#include "Logger.h"
#include "Characters/Character.h"

int main()
{
	Character* Player = new Character(1, 100, 10, 10, 10);

	delete Player; // Clean up the character to avoid memory leaks

	return 0;
}
