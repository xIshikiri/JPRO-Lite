#pragma once
class IGameEntity {
public:
	virtual ~IGameEntity() = default;
    virtual char getDisplayChar() const = 0;
	virtual bool isPlayer() const { return false; } // Default implementation, can be overridden
};