#pragma once
#include <string>

class Item
{
public:
	Item(std::string name, std::string description, int Width, int Height)
		: Name(std::move(name)),
		  Description(std::move(description)),
		  Width(Width),
		  Height(Height),
		  Symbol(0)
	{
	}

	std::string GetName() const
	{
		return Name;
	}

	std::string GetDescription() const
	{
		return Description;
	}

	int GetWidth() const
	{
		return Width;
	}

	int GetHeight() const
	{
		return Height;
	}

	char GetSymbol() const
	{
		return Symbol;
	}

private:
	std::string Name;
	std::string Description;
	int Width;
	int Height;
	char Symbol;
};

