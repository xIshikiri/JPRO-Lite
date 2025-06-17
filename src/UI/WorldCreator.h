#pragma once
#include "IUIScreen.h"

class WorldCreator : public IUIScreen
{
public:
	void render() const override;
	void handleInput(char input) override;
};

