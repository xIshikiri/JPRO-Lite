#pragma once

class IUIScreen {
public:
	virtual ~IUIScreen() = default;
	virtual void initialize() = 0; // Initialize the screen
	virtual void render() const = 0; // Render the screen
	virtual void handleInput(char input) = 0; // Handle user input
};