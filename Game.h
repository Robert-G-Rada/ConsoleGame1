#ifndef GAME_H
#define GAME_H

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
	static const char BLOCK = (char)219;
	static const int INF = 0x3f3f3f3f;
	static const int SCREEN_WIDTH = 70;
	static const int SCREEN_HEIGHT = 40;
	static const int FRAME_WIDTH = 26;
	static const int FRAME_START = (SCREEN_WIDTH - FRAME_WIDTH - 1) / 2;
protected:
private:
	int frame_start;
	int tick_rate;
	bool running;
	bool restart;

	Clock *clock1;
	Map *map1;

	void init();
	long long run();
	void drawFrame();
	void startMessage();
	void endMessage(long long score);
	void deleteStuff();
	void clearScreen();
};

#endif // GAME_H
