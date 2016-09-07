#include "Gun.h"

Gun::Gun(int owner, Map *map1)
{
	if (owner == -1)
	{
		timer = ATTACK_TIME;
		speed = 60;
	}
	else
	{
		timer = 0;
		speed = 15;
	}
	this->owner = owner;
	this->map1 = map1;
}

void Gun::update()
{
	timer += speed;
	if (timer >= ATTACK_TIME)
		timer = ATTACK_TIME;
}

void Gun::shoot(int x, int y)
{
	if (timer >= ATTACK_TIME)
	{
		map1->addProjectile(Projectile(x, y, owner));
		timer = 0;
	}
}

bool Gun::isReady()
{
	if (timer >= ATTACK_TIME)
		return true;
	return false;
}