#ifndef MAP_H
#define MAP_H

#include <list>
#include <queue>

#include "Enemy.h"
#include "Event.h"
#include "Player.h"
#include "Projectile.h"

class Player;
class Projectile;
class Enemy;
class Event;

struct int2
{
	int x, y;
};

class Map
{
public:
	Map(int size);
	void update();
	void setPlayer(Player *player);
	void addProjectile(Projectile projectile);
	void addEnemy(Enemy enemy);
	void endGame();
protected:
private:
	int size;
	int position;
	int scroll_speed;
	int scroll_timer;
	const int SCROLL_TIME = 600;

	Player *player;

	void initEvents();
	void updateProjectiles();
	void updateEnemies();
	void updateMap();

	std::queue<Event*> events;
	std::list<Projectile> projectiles;
	std::list<Enemy> enemies;
};

#endif // MAP_H
