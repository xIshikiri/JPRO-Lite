#include "WorldManager.h"

#include <iostream>

#include "GameplayStatics.h"
#include "Logger.h"
#include "PlayerCharacter.h"

char Tile::getDisplayChar() const
{
	if (entity)
	{
		return entity->getDisplayChar();
	}
	switch (terrain)
	{
	case TerrainType::Empty:
		return '.';
	case TerrainType::Wall:
		return '#';
	default:
		return '?'; // Unknown terrain type
	}
}

WorldManager::WorldManager()
{
	clearWorld(); // Initialize the world with empty tiles
	DEBUG_LOG(LogLevel::INFO, "WorldManager initialized.");
}

WorldManager::~WorldManager()
{
	clearWorld(); // Clean up the world tiles
}

void WorldManager::initialize()
{
	setEntity(0, 0, GameplayStatics::getPlayerCharacter()); // Set the player character at the starting position (0, 0)
}

bool WorldManager::isInBounds(int x, int y) const
{
	return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

bool WorldManager::isWalkable(int x, int y) const
{
	if (isInBounds(x, y))
	{
		return world[y][x].isWalkable();
	}
	return false; // Out of bounds is not walkable
}

bool WorldManager::setEntity(int x, int y, IGameEntity* entity)
{
	if (entity == nullptr)
	{
		DEBUG_LOG(LogLevel::ERR, "Attempted to set a null entity at (" << x << ", " << y << ").");
		return false; // Do not allow setting a null entity, for removal use removeEntity()
	}
	if (isInBounds(x, y))
	{
		if (world[y][x].entity)
		{
			DEBUG_LOG(LogLevel::WARN, "Tried overwriting existing entity at (" << x << ", " << y << ").");
			return false; // Tile already occupied by another entity
		}
		world[y][x].entity = entity;
		return true;
	}
	else
	{
		// Handle out of bounds case
		DEBUG_LOG(LogLevel::ERR, "Attempted to set entity out of bounds at (" << x << ", " << y << ")");
		return false;
	}
}

bool WorldManager::moveEntity(int fromX, int fromY, int toX, int toY)
{
	if (!isInBounds(fromX, fromY) || !isInBounds(toX, toY))
	{
		DEBUG_LOG(LogLevel::ERR, "Attempted to move entity out of bounds from (" << fromX << ", " << fromY << ") to (" << toX << ", " << toY << ")");
		return false; // Out of bounds
	}
	if (!world[toY][toX].isWalkable())
	{
		DEBUG_LOG(LogLevel::ERR, "Destination tile (" << toX << ", " << toY << ") is not walkable.");
		return false; // Destination is not walkable
	}
	if (world[fromY][fromX].entity == nullptr)
	{
		DEBUG_LOG(LogLevel::ERR, "No entity to move from (" << fromX << ", " << fromY << ").");
		return false; // No entity to move
	}

	world[toY][toX].entity = world[fromY][fromX].entity;
	world[fromY][fromX].entity = nullptr; // Clear the old position
	return true;
}

bool WorldManager::removeEntity(int x, int y)
{
	if (isInBounds(x, y))
	{
		if (world[y][x].entity)
		{
			if (dynamic_cast<PlayerCharacter*>(world[y][x].entity))
			{
				world[y][x].entity = nullptr; // Do not delete player character, just clear the pointer
				return true;
			}
			delete world[y][x].entity; // Delete the entity to avoid memory leaks
			world[y][x].entity = nullptr; // Clear the entity pointer
			return true;
		}
		else
		{
			DEBUG_LOG(LogLevel::WARN, "No entity to remove at (" << x << ", " << y << ").");
			return false; // No entity to remove
		}
	}
	else
	{
		DEBUG_LOG(LogLevel::ERR, "Attempted to remove entity out of bounds at (" << x << ", " << y << ")");
		return false; // Out of bounds
	}
}


bool WorldManager::setTerrain(int x, int y, Tile::TerrainType terrain)
{
	if (isInBounds(x, y))
	{
		world[y][x].terrain = terrain; // Set the terrain type at the specified coordinates
		return true;
	}
	else
	{
		// Handle out of bounds case
		DEBUG_LOG(LogLevel::ERR, "Attempted to set terrain out of bounds at (" << x << ", " << y << ")");
		return false; // Out of bounds
	}
}

void WorldManager::setPlayerPosition(int x, int y)
{
	playerX = x;
	playerY = y;
}

bool WorldManager::movePlayer(int toX, int toY)
{
	if (moveEntity(playerX, playerY, toX, toY))
	{
		playerX = toX;
		playerY = toY;
		return true;
	}
	if (isInBounds(toX, toY) && world[toX][toY].entity)
	{
		if (world[toX][toY].entity->onInteract())
		{
			removeEntity(toX, toY); // Remove the entity after interaction
			if (movePlayer(toX, toY))
			{
				playerX = toX;
				playerY = toY;
			}
			DEBUG_LOG(LogLevel::INFO, "Player moved to (" << toX << ", " << toY << ") and interacted with entity.");
			return true; // Successfully moved and interacted with the entity
		}
		else
		{
			DEBUG_LOG(LogLevel::INFO, "Player moved to (" << toX << ", " << toY << ") but interaction failed.");
			return false; // Interaction failed, but player still moved
		} // Call interact method if the tile has an entity
	}
	DEBUG_LOG(LogLevel::ERR, "Failed to move player from (" << playerX << ", " << playerY << ") to (" << toX << ", " << toY << ")");
	return false; // Failed to move player, either out of bounds or not walkable
}

Tile WorldManager::getTile(int x, int y) const
{
	if (isInBounds(x, y))
	{
		return world[y][x]; // Return the tile at the specified coordinates
	}
	else
	{
		DEBUG_LOG(LogLevel::ERR, "Attempted to get tile out of bounds at (" << x << ", " << y << ")");
		return {}; // Return an empty tile if out of bounds
	}
}

void WorldManager::clearWorld()
{
	for (auto& y : world)
	{
		for (auto& x : y)
		{
			// Delete the entity if there is one
			if (x.entity)
			{
				if (!x.entity->isPlayer())
					delete x.entity;
				x.entity = nullptr;
			}
			x.terrain = Tile::TerrainType::Empty; // Reset terrain to empty
		}
	}
	DEBUG_LOG(LogLevel::INFO, "World cleared.");
}
