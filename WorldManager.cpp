#include "WorldManager.h"

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
	// Move the entity
	world[toY][toX].entity = world[fromY][fromX].entity;
	world[fromY][fromX].entity = nullptr; // Clear the old position
	return true;
}

void WorldManager::setEntity(int x, int y, IGameEntity* entity)
{
	if (isInBounds(x, y))
	{
		world[y][x].entity = entity; // Set the entity at the specified coordinates
	}
	else
	{
		// Handle out of bounds case, e.g., log an error or throw an exception
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
		// Handle out of bounds case, e.g., log an error or throw an exception
		DEBUG_LOG(LogLevel::ERR, "Attempted to set terrain out of bounds at (" << x << ", " << y << ")");
	}
}

void WorldManager::render() const
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			std::cout << world[y][x].getDisplayChar();
		}
		std::cout << "\n";
	}
	DEBUG_LOG(LogLevel::INFO, "World rendered.");
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
