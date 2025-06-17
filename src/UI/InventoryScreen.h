#pragma once
#include "IUIScreen.h"
class InventoryComponent;

class InventoryScreen : public IUIScreen
{
public:
	InventoryScreen() = default;

	// IUIScreen interface
	void initialize() override;
	void render() const override;
	void handleInput(char input) override;

	void setInventory(InventoryComponent* inventory);

private:
	InventoryComponent* inventory = nullptr; // Pointer to the inventory component
};

