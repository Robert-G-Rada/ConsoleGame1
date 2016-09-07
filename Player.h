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
	Player(Map *map1);
	void update();
	bool checkHit(int x, int y, int damage);
	void deleteStuff();
protected:
private:
	const int MAX_HEALTH = 10;
	int health;
	int x;
	int y;

	std::vector< std::pair<int, int> > body;

	Gun *gun;
	Map *map1;

	void drawPlayer();
	void deletePlayer();
	void move(int x);
	void changeHealth(int damage);
	void updateHPBar();
	void drawHPBarFrame();
};

#endif // PLAYER_H
