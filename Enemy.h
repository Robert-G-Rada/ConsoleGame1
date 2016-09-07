#ifndef ENEMY_H
#define ENEMY_H

#include "Map.h"
#include "Gun.h"
#include "Console.h"
#include "Game.h"
#include <vector>

class Projectile;
class Player;
class Game;
class Map;
class Gun;

struct int2;

class Enemy
{
public:
	Enemy(Map *map1, int x, int value, std::string color);
	Enemy(Map *map1, int x);
	void update();
	void checkHitPlayer(Player *player);
	bool checkHit(Projectile projectile);
	bool isRemoved();
	int getValue();
protected:
	bool is_removed;
	int health;
	int x, y;
	int height;
	int move_timer;
	int speed;
	int value;
	static const int MOVE_TIME = 600;

	std::string color;
	std::vector<int2> body;

	Gun *gun;
	Map *map1;
	Game *game;

	void checkCollision();
	void init();
	void drawEnemy();
	void deleteEnemy();
	void move(int x, int y);
	int2 newInt2(int x, int y);
};

#endif // ENEMY_H