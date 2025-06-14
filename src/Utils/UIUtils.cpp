#include "UIUtils.h"
#include <cstdlib>

void UIUtils::clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
