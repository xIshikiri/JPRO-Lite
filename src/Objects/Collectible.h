#pragma once
#include "IGameEntity.h"

class Item;

class Collectible : public IGameEntity
{
public:
	Collectible(Item* items);
	~Collectible() override;

	// IGameEntity interface
	char getDisplayChar() const override { return 'C'; }
	EntityType getEntityType() const override { return EntityType::Collectible; }
	bool onInteract() override; // Interaction behavior when the collectible is picked up
	Item* getItem() const; // Returns the items contained in this collectible

private:
	Item* item; // Array of items that this collectible can contain
};

