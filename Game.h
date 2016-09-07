#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "Clock.h"
#include "Console.h"
#include "Map.h"
#include "Player.h"

class Player;
class Map;

class Game
{
public:
	Game();
	static const int SCREEN_WIDTH = 70;
	static const int SCREEN_HEIGHT = 40;
	static const int FRAME_WIDTH = 26;
	static const int FRAME_START = (SCREEN_WIDTH - FRAME_WIDTH - 1) / 2;
protected:
private:
	int frame_start;
	bool running;

	Player *player;
	Clock *clock1;
	Map *map1;

	void init();
	void run();
	void drawFrame();
	void startMessage();
};

#endif // GAME_H
