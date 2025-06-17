#include "Item.h"

bool Item::rotateItem()
{
	if (width == height)
	{
		DEBUG_LOG(LogLevel::INFO, "Item is already square, rotation has no effect.");
		return false; // No change if the item is square
	}
	std::swap(width, height); // Swap width and height to rotate the item
	return true; // Return true to indicate the item was successfully rotated
}
