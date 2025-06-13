#pragma once
#include <string>

class Item
{
public:
	Item(std::string name, std::string description, int width, int height)
		: name(std::move(name)),
		  description(std::move(description)),
		  width(width),
		  height(height),
		  symbol(0)
	{
		if (width <= 0 || height <= 0)
		{
			
		}
	}

	std::string getName() const
	{
		return name;
	}

	std::string getDescription() const
	{
		return description;
	}

	int getWidth() const
	{
		return width;
	}

	int getHeight() const
	{
		return height;
	}

	char getSymbol() const
	{
		return symbol;
	}

private:
	std::string name;
	std::string description;
	int width;
	int height;
	char symbol;
};

