#include "WorldManager.h"

#include <iostream>

#include "Logger.h"

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
	DEBUG_LOG(LogLevel::INFO, "WorldManager initialized with a cleared world.");
}

WorldManager::~WorldManager()
{
	clearWorld(); // Clean up the world tiles
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

bool WorldManager::moveEntity(int fromX, int fromY, int toX, int toY)
{
	if (!isInBounds(fromX, fromY) || !isInBounds(toX, toY))
	{
		return false; // Out of bounds
	}
	if (!world[fromY][fromX].isWalkable() || !world[toY][toX].isWalkable())
	{
		return false; // Either the source or destination is not walkable
	}
	if (world[fromY][fromX].entity == nullptr)
	{
		return false; // No entity to move
	}

	world[toY][toX].entity = world[fromY][fromX].entity;
	world[fromY][fromX].entity = nullptr; // Clear the old position
	return true;
}

void WorldManager::setEntity(int x, int y, IGameEntity* entity)
{
	if (entity == nullptr)
	{
		DEBUG_LOG(LogLevel::ERR, "Attempted to set a null entity at (" << x << ", " << y << ").");
		return; // Do not allow setting a null entity, for removal use removeEntity()
	}
	if (isInBounds(x, y))
	{
		if (world[y][x].entity)
		{
			DEBUG_LOG(LogLevel::WARN, "Overwriting existing entity at (" << x << ", " << y << ").");
			delete world[y][x].entity; // Delete the existing entity to avoid memory leaks
		}
		world[y][x].entity = entity;
	}
	else
	{
		// Handle out of bounds case
		DEBUG_LOG(LogLevel::ERR, "Attempted to set entity out of bounds at (" << x << ", " << y << ")");
	}
}

void WorldManager::setTerrain(int x, int y, Tile::TerrainType terrain)
{
	if (isInBounds(x, y))
	{
		world[y][x].terrain = terrain; // Set the terrain type at the specified coordinates
	}
	else
	{
		// Handle out of bounds case
		DEBUG_LOG(LogLevel::ERR, "Attempted to set terrain out of bounds at (" << x << ", " << y << ")");
	}
}

void WorldManager::render() const
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			std::cout << world[y][x].getDisplayChar() << " ";
		}
		std::cout << "\n";
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
				delete x.entity;
				x.entity = nullptr;
			}
			x.terrain = Tile::TerrainType::Empty; // Reset terrain to empty
		}
	}
	DEBUG_LOG(LogLevel::INFO, "World cleared.");
}
