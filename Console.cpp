#include "Console.h"

#include <windows.h>
#include <conio.h>

Console::Console()
{
	//ctor
}

void Console::setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Console::setCursor(int i, int j)
{
	COORD cPos;
	cPos.X = j;
	cPos.Y = i;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cPos);
}

int Console::getInput()
{
	int input;
	if (_kbhit())
	{
		input = _getch();

		if (input == 0 || input == 224) input = _getch();
		return input;
		// 75 = left | 72 = up | 77 = right | 80 = down
	}
	return 0;
}
