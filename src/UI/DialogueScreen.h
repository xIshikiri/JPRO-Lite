#pragma once
#include "IUIScreen.h"
class DialogueScreen : public IUIScreen
{
public:
	void initialize() override;
	void render() const override;
	void handleInput(char input) override;
};

