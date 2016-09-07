#include "Enemy.h"

Enemy::Enemy(Map *map1, int x)
{
	move_timer = 0;

	this->map1 = map1;
	this->x = x;
	init();
	this->y = height;
	this->gun = new Gun(1, map1);

	drawEnemy();
}

void Enemy::update()
{
	move_timer += speed;
	if (move_timer >= MOVE_TIME)
		move(0, 1);

	gun->update();
	if (gun->isReady())
		gun->shoot(x, y+1);
}

bool Enemy::checkHit(int x, int y, int damage)
{
	for (unsigned i = 0; i < body.size(); i++)
	{
		if (this->x + body[i].x == x && this->y + body[i].y == y)
		{
			health -= damage;
			if (health <= 0)
			{
				is_removed = true;
				deleteEnemy();
			}
			return true;
		}
	}
	return false;
}

void Enemy::drawEnemy()
{
	for (unsigned i = 0; i < body.size(); i++)
	{
		Console::setCursor(y + body[i].y, x + body[i].x + Game::FRAME_START);
		std::cout << '#';
	}
	Console::setCursor(0, 0);
}

void Enemy::deleteEnemy()
{
	for (unsigned i = 0; i < body.size(); i++)
	{
		Console::setCursor(y + body[i].y, x + body[i].x + Game::FRAME_START);
		std::cout << ' ';
	}
	Console::setCursor(0, 0);
}

void Enemy::move(int x, int y)
{
	deleteEnemy();
	this->x += x;
	this->y += y;
	drawEnemy();
	move_timer -= MOVE_TIME;
}

void Enemy::init()
{
	is_removed = false;
	speed = 60;
	health = 5;
	gun = new Gun(1, map1);
	height = 2;
	body.push_back(newInt2(0, 0));
	body.push_back(newInt2(0, -1));
	body.push_back(newInt2(-1, -1));
	body.push_back(newInt2(1, -1));
}

int2 Enemy::newInt2(int x, int y)
{
	int2 t;
	t.x = x;
	t.y = y;
	return t;
}
bool Enemy::isRemoved()
{
	return is_removed;
}