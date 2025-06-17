#pragma once
#include "IUIScreen.h"

class ExplorationScreen : public IUIScreen
{
public:
	void render() const override;
	void handleInput(char input) override;
};

