#include <iostream>

#include "Character.h"
#include "Logger.h"
#include "PlayerCharacter.h"
#include "UIUtils.h"
#include "WorldManager.h"

int main()
{
	GameInstance::getInstance()->run();

	GameInstance::destroyInstance();

	return 0;
}
