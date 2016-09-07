#ifndef ENEMY_H
#define ENEMY_H

#include "Map.h"
#include "Gun.h"
#include "Console.h"
#include "Game.h"
#include <vector>

class Game;
class Map;
class Gun;

struct int2;

class Enemy
{
public:
	Enemy(Map *map1, int x);
	void update();
	bool checkHit(int x, int y, int damage);
	bool isRemoved();
protected:
	bool is_removed;
	int health;
	int x, y;
	int height;
	int move_timer;
	int speed;
	static const int MOVE_TIME = 600;

	std::vector<int2> body;

	Gun *gun;
	Map *map1;
	Game *game;

	void init();
	void drawEnemy();
	void deleteEnemy();
	void move(int x, int y);
	int2 newInt2(int x, int y);
};

#endif // ENEMY_H