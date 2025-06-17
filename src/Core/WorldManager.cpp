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
	DEBUG_LOG(LogLevel::INFO, "WorldManager initialized.");
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
			DEBUG_LOG(LogLevel::WARN, "Overwriting existing entity at (" << x << ", " << y << ").");
			delete world[y][x].entity; // Delete the existing entity to avoid memory leaks
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

bool WorldManager::removeEntity(int x, int y)
{
	if (isInBounds(x, y))
	{
		if (world[y][x].entity)
		{
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

void WorldManager::render() const
{
	for (const auto& y : world)
	{
		for (auto x : y)
		{
			std::cout << x.getDisplayChar() << " ";
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
