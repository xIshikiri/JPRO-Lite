#include "Character.h"
#include "Logger.h"

Character::Character(std::string name, int level, int health, int strength, int dexterity, int inventoryWidth, int inventoryHeight)
	: name(std::move(name)), level(level), health(health), strength(strength), dexterity(dexterity)
{
	if (inventoryHeight == 0)
	{
		inventoryHeight = inventoryWidth; // Default to square inventory if height is not specified
	}
	inventory = new InventoryComponent(inventoryWidth, inventoryHeight);

	DEBUG_LOG(LogLevel::INFO, "Character created with stats: " << "\n"
		<< "Level: " << getLevel() << "\n"
		<< "Health: " << getHealth() << "\n"
		<< "Strength: " << getStrength() << "\n"
		<< "Dexterity: " << getDexterity() << "\n");
}

Character::~Character()
{
	delete inventory; // Clean up the inventory component to avoid memory leaks
	DEBUG_LOG(LogLevel::INFO, "Character destroyed.");
}

Character::Character(const Character& other)
{
	level = other.level;
	health = other.health;
	strength = other.strength;
	dexterity = other.dexterity;
	inventory = new InventoryComponent(*other.inventory); // Deep copy of the inventory component
}

Character& Character::operator=(const Character& other)
{
	if (this != &other) // Check for self-assignment
	{
		level = other.level;
		health = other.health;
		strength = other.strength;
		dexterity = other.dexterity;
		delete inventory; // Clean up existing inventory
		inventory = new InventoryComponent(*other.inventory); // Deep copy of the inventory component
	}
	return *this;
}

Character::Character(Character&& other) noexcept
{
	level = other.level;
	health = other.health;
	strength = other.strength;
	dexterity = other.dexterity;
	inventory = other.inventory; // Transfer ownership of the inventory
	other.inventory = nullptr; // Set the moved-from object's inventory to nullptr
}

Character& Character::operator=(Character&& other) noexcept
{
	if (this != &other) // Check for self-assignment
	{
		level = other.level;
		health = other.health;
		strength = other.strength;
		dexterity = other.dexterity;
		delete inventory; // Clean up existing inventory
		inventory = other.inventory; // Transfer ownership of the inventory
		other.inventory = nullptr; // Set the moved-from object's inventory to nullptr
	}
	return *this;
}

bool Character::onInteract()
{
	DEBUG_LOG(LogLevel::INFO, "Character " << getName() << " interacted with.");
	return false;
}
