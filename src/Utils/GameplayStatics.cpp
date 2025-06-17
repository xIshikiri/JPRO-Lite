#include "GameplayStatics.h"

#include "GameInstance.h"
#include "PlayerCharacter.h"
#include "WorldManager.h"

PlayerCharacter* GameplayStatics::getPlayerCharacter()
{
	GameInstance* gameInstance = GameInstance::getInstance();
	if (gameInstance)
	{
		return gameInstance->getPlayerCharacter();
	}
	DEBUG_LOG(LogLevel::ERR, "Failed to get player character: GameInstance is null.");
	return nullptr; // Return nullptr if game instance or player character is not available
}

InventoryComponent* GameplayStatics::getPlayerInventory()
{
	GameInstance* gameInstance = GameInstance::getInstance();
	if (gameInstance && gameInstance->getPlayerCharacter())
	{
		return gameInstance->getPlayerCharacter()->getInventory();
	}
	DEBUG_LOG(LogLevel::ERR, "Failed to get player inventory: GameInstance or PlayerCharacter is null.");
	return nullptr; // Return nullptr if player character or inventory is not available
}

std::pair<int, int> GameplayStatics::getPlayerLocation()
{
	GameInstance* gameInstance = GameInstance::getInstance();
	if (gameInstance && gameInstance->getWorldManager())
	{
		return gameInstance->getWorldManager()->getPlayerPosition();
	}
	DEBUG_LOG(LogLevel::ERR, "Failed to get player location: GameInstance or WorldManager is null.");
	return std::make_pair(-1, -1); // Return invalid coordinates if player location is not available
}
