#ifndef GUN_H
#define GUN_H

#include "Map.h"
#include "Projectile.h"

class Map;

class Gun
{
public:
	Gun(int owner, Map *map1); // -1 = player | 1 = enemy
	void update();
	void shoot(int x, int y);
	bool isReady();
protected:
	int speed;
	int timer;
	int owner;

	Map *map1;

	static const int ATTACK_TIME = 600;
private:
};

#endif // GUN_H
