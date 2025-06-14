#pragma once
#include <cstdint>

#include "IGameEntity.h"

struct Tile
{
	enum class TerrainType : uint8_t
	{
		Empty,
		Wall
	};

	TerrainType terrain;
	IGameEntity* entity;

	Tile() : terrain(TerrainType::Empty), entity(nullptr) {}

	bool isWalkable() const
	{
		return terrain != TerrainType::Wall && entity == nullptr;
	}

	char getDisplayChar() const;
};

class WorldManager
{
public:
	static const int WIDTH = 50;
	static const int HEIGHT = 20;

	WorldManager();
	~WorldManager();

	bool isInBounds(int x, int y) const;
	bool isWalkable(int x, int y) const;
	bool moveEntity(int fromX, int fromY, int toX, int toY);
	void setEntity(int x, int y, IGameEntity* entity);
	void setTerrain(int x, int y, Tile::TerrainType terrain);
	void render() const;
private:
	Tile world[HEIGHT][WIDTH]; // 2D array representing the world grid
	void clearWorld(); // Helper function to initialize the world
};

