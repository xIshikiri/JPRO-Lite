#pragma once
#include <cstdint>

#include "IUIScreen.h"

class WorldManager;

class ExplorationScreen : public IUIScreen
{
public:
	// IUIScreen interface
	void initialize() override;
	void render() const override;
	void handleInput(char input) override;

private:
	WorldManager* worldManager = nullptr; // Pointer to the WorldManager instance
};

