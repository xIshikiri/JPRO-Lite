#pragma once
#include "Character.h"

class Enemy;

typedef void (*BehaviorFunc)(Enemy&);

class Enemy : public Character
{
public:
	Enemy(BehaviorFunc behavior, const std::string& name, int level, int health, int strength, int dexterity, int inventoryWidth,
		int inventoryHeight);

	// IGameEntity Interface
	char getDisplayChar() const override { return 'E'; }
	EntityType getEntityType() const override { return EntityType::Combat;  }
	bool onInteract() override;

	void setBehavior(BehaviorFunc behavior) { behavior_ = behavior; }
	BehaviorFunc getBehavior() const { return behavior_; }
private:
	BehaviorFunc behavior_;
};

