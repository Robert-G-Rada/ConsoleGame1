#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Console.h"
#include "Game.h"

class Projectile
{
public:
	Projectile(int x, int y, int owner);
	void update();
	void erase();
	int getX();
	int getY();
	int getDamage();
	int getOwner();

	bool is_removed;
protected:
private:
	int move_timer;
	int damage;
	int speed;
	int x, y, dy;
	static const int MOVE_TIME = 600;

	void draw();
	void move();
};

#endif // PROJECTILE_H
