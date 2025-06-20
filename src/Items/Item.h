#pragma once
#include <string>

#include "Logger.h"
#include "IGameEntity.h"

class Item
{
public:
	Item(std::string name, std::string description, int width, int height)
		: name(std::move(name)),
		  description(std::move(description)),
		  width(width),
		  height(height),
		  symbol('i')
	{
		if (width <= 0 || height <= 0)
		{
			DEBUG_LOG(LogLevel::ERR, "Attempted to create an item of size smaller than 1 tile");
			width = 1;
			height = 1;
		}
	}

	std::string getName() const { return name; }
	std::string getDescription() const { return description; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	char getSymbol() const { return getName()[0]; }

	bool rotateItem();

private:
	std::string name;
	std::string description;
	int width;
	int height;
	char symbol;
};

