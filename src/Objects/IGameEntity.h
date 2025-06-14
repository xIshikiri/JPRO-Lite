#pragma once
class IGameEntity {
public:
	virtual ~IGameEntity() = default;
    virtual char getDisplayChar() const = 0;
};