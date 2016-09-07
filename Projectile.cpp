#include "Projectile.h"

Projectile::Projectile(int x, int y, int owner)
{
	is_removed = false;
	move_timer = 0;
	if (owner == -1)
	{
		damage = 5;
		speed = 300;
	}
	else
	{
		damage = 2;
		speed = 200;
	}
	this->x = x;
	this->y = y;
	this->dy = owner;

	Console::setCursor(y, Game::FRAME_START + x);
	std::cout << '|';
	Console::setCursor(0, 0);
}

void Projectile::update()
{
	move_timer += speed;
	if (move_timer >= MOVE_TIME)
		move();
}

void Projectile::move()
{
	erase();
	y += dy;
	move_timer -= MOVE_TIME;

	if (y < 1 || y >= Game::SCREEN_HEIGHT - 1)
	{
		is_removed = true;
		return;
	}

	Console::setCursor(y, Game::FRAME_START + x);
	std::cout << '|';
	Console::setCursor(0, 0);
}

void Projectile::erase()
{
	Console::setCursor(y, Game::FRAME_START + x);
	std::cout << ' ';
	Console::setCursor(0, 0);
}

void Projectile::explode()
{

}

int Projectile::getX()
{
	return x;
}

int Projectile::getY()
{
	return y;
}
int Projectile::getDamage()
{
	return damage;
}