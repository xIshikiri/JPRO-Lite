#pragma once
#include "IUIScreen.h"
class InventoryScreen : public IUIScreen
{
public:
	void render() const override;
	void handleInput(char input) override;
};

