#include "Map.h"

Map::Map(int size)
{
	this->size = size;
	position = 0;
	scroll_speed = 60;
	scroll_timer = 0;
	initEvents();
}

void Map::update()
{
	updateMap();
	player->update();
	updateProjectiles();
	updateEnemies();
}

void Map::endGame()
{
	std::cout << "PLAYER IS DEAD\n";
}

void Map::updateMap()
{
	scroll_timer += scroll_speed;
	if (scroll_timer >= SCROLL_TIME)
	{
		scroll_timer -= SCROLL_TIME;
		position++;
		if (events.size() != 0)
			while (events.front()->getPosition() == position)
			{
				events.front()->trigger();
				events.pop();
				if (events.size() == 0)
					break;
			}
	}
}

void Map::updateProjectiles()
{
	for (std::list<Projectile>::iterator projectile = projectiles.begin(); projectile != projectiles.end();)
	{
		bool erased = false;
		projectile->update();
		if (projectile->is_removed)
		{
			erased = true;

			std::list<Projectile>::iterator t = projectile;
			++t;
			if (t == projectiles.end())
			{
				projectiles.erase(projectile);
				break;
			}
			projectile = projectiles.erase(projectile);
			continue;
		}
		for (std::list<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
		{
			if (enemy->checkHit(projectile->getX(), projectile->getY(), projectile->getDamage()))
			{
				erased = true;

				projectile->erase();
				projectile = projectiles.erase(projectile);
				break;
			}
			else
				if (enemy->checkHit(projectile->getX(), projectile->getY()+1, projectile->getDamage()))
				{
					erased = true;

					projectile->erase();
					projectile = projectiles.erase(projectile);
					break;
				}
		}
		if (erased == false)
		{
			if (player->checkHit(projectile->getX(), projectile->getY(), projectile->getDamage()))
			{
				erased = true;
				projectile->erase();
				projectile = projectiles.erase(projectile);
			}
		}
		if (projectiles.size() == 0)
			break;
		if (erased == false)
			++projectile;
	}
}

void Map::updateEnemies()
{
	for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (it->isRemoved())
		{
			std::list<Enemy>::iterator t = it;
			++t;
			if (t == enemies.end())
			{
				enemies.erase(it);
				break;
			}
			it = enemies.erase(it);
		}
	}
	for (std::list<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		it->update();
}

void Map::addProjectile(Projectile projectile)
{
	projectiles.push_back(projectile);
}

void Map::addEnemy(Enemy enemy)
{
	enemies.push_back(enemy);
}

void Map::setPlayer(Player *player)
{
	this->player = player;
}

void Map::initEvents()
{
	events.push(new Event(1, this, 1, 8));
	events.push(new Event(1, this, 1, 16));
	events.push(new Event(6, this, 1, 13));
	events.push(new Event(11, this, 1, 3));
	events.push(new Event(11, this, 1, 20));
	events.push(new Event(11, this, 1, 10));
	events.push(new Event(20, this, 1, 5));
	events.push(new Event(20, this, 1, 9));
	events.push(new Event(20, this, 1, 13));
	events.push(new Event(20, this, 1, 17));
}