#pragma once
#include <utility>

#include "IUIScreen.h"

class WorldManager;

class WorldCreator : public IUIScreen
{
public:
	void initialize() override;
	void render() const override;
	void handleInput(char input) override;

	std::pair<int, int> getCoordinates();
private:
	WorldManager* worldManager = nullptr; // Pointer to the WorldManager instance
};

