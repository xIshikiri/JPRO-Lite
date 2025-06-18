#pragma once

enum class EntityType
{
	Combat,
	Dialogue,
	Collectible
};

class IGameEntity {
public:
	virtual ~IGameEntity() = default;
    virtual char getDisplayChar() const = 0;
	virtual bool isPlayer() const { return false; }
	virtual EntityType getEntityType() const = 0;
	virtual bool onInteract() { return true;  } // Default interaction behavior, can be overridden by derived classes
};