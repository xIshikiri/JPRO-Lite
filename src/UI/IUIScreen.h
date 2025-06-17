#pragma once

class IUIScreen {
public:
	virtual ~IUIScreen() = default;
	virtual void render() const = 0; // Render the screen
	virtual void handleInput(char input) = 0; // Handle user input
};