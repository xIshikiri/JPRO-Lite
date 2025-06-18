#pragma once
#include <cstdint>
#include <utility>

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

	void initialize();

	bool isInBounds(int x, int y) const;
	bool isWalkable(int x, int y) const;

	bool setEntity(int x, int y, IGameEntity* entity);
	bool moveEntity(int fromX, int fromY, int toX, int toY);
	bool removeEntity(int x, int y);

	Tile getTile(int x, int y) const;
	bool setTerrain(int x, int y, Tile::TerrainType terrain);

	void setPlayerPosition(int x, int y);
	std::pair<int, int> getPlayerPosition() const { return { playerX, playerY }; }
	bool movePlayer(int toX, int toY);

private:
	Tile world[HEIGHT][WIDTH]; // 2D array representing the world grid
	//TODO: dynamiczna alokacja
	int playerX = 0;
	int playerY = 0;
	void clearWorld(); // Helper function to initialize the world
};

