#ifndef PLAYER_H
#define PLAYER_H

#include <conio.h>

#include "Map.h"
#include "Gun.h"
#include "Console.h"
#include "Game.h"

class Game;
class Map;
class Gun;

class Player
{
public:
	Player(Game *game, Map *map1);
	void update();
	bool checkHit(int x, int y, int damage);
protected:
private:
	int health;
	int x;
	int y;

	Gun *gun;
	Map *map1;
	Game *game;

	void drawPlayer();
	void deletePlayer();
	void move(int x);
};

#endif // PLAYER_H
