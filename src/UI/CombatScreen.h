#pragma once
#include "IUIScreen.h"
class CombatManager;

class CombatScreen : public IUIScreen
{
public:
	void initialize() override;
	void render() const override;
	void handleInput(char input) override;
private:
	CombatManager* combatManager; // Pointer to the combat manager
};

