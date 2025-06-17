#pragma once
#include "IUIScreen.h"
class CombatScreen : public IUIScreen
{
public:
	void initialize() override;
	void render() const override;
	void handleInput(char input) override;
};

