#include <iostream>

#include "Character.h"
#include "Logger.h"
#include "PlayerCharacter.h"
#include "UIUtils.h"
#include "WorldManager.h"

int main()
{
	GameInstance::getInstance()->run();
	// Wrogowie
	// Wskazniki do funkcji
	// Zapis stanu
	GameInstance::destroyInstance();

	return 0;
}
