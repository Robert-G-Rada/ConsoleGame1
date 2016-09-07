#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Console.h"
#include "Game.h"

class Projectile
{
public:
	Projectile(int x, int y, int owner);
	void update();
	void move();
	void explode();
	void erase();
	int getX();
	int getY();
	int getDamage();

	bool is_removed;
protected:
private:
	int move_timer;
	int damage;
	int speed;
	int x, y, dy;
	static const int MOVE_TIME = 600;
};

#endif // PROJECTILE_H
