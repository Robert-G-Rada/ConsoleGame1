#include "Game.h"

Game::Game()
{
	startMessage();
	init();
	run();
}

void Game::init()
{
	running = true;
	frame_start = (SCREEN_WIDTH - FRAME_WIDTH - 1) / 2;

	drawFrame();

	clock1 = new Clock(30);
	map1 = new Map(100);
	player = new Player(this, map1);
	map1->setPlayer(player);
}

void Game::run()
{
	while (running)
	{
		clock1->update();

		if (clock1->tick())
		{
			map1->update();
		}
	}
}

void Game::drawFrame()
{
	int x1, x2;
	x1 = (SCREEN_WIDTH - FRAME_WIDTH - 1) / 2 - 1;
	x2 = x1 + FRAME_WIDTH + 1;

	for (int i = x1; i <= x2; i++)
	{
		Console::setCursor(0, i);
		std::cout << (char)219;
		Console::setCursor(SCREEN_HEIGHT - 1, i);
		std::cout << (char)219;
	}
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		Console::setCursor(i, x1);
		std::cout << (char)219;
		Console::setCursor(i, x2);
		std::cout << (char)219;
	}
	Console::setCursor(0, 0);
}

void Game::startMessage()
{
	std::cout << "SET SCREEN BUFFER SIZE AND WINDOW SIZE TO:\nWIDTH = 70\nHEIGHT = 40\nPRESS ANY KEY TO CONTINUE\n";
	while (!_kbhit());
	Console::getInput();
	Console::setCursor(0, 0);
	std::cout << "                                                 ";
	Console::setCursor(1, 0);
	std::cout << "                                                 ";
	Console::setCursor(2, 0);
	std::cout << "                                                 ";
	Console::setCursor(3, 0);
	std::cout << "                                                 ";
}