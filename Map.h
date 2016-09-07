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
	void deleteStuff();
	bool isEnded();
	long long getScore();
protected:
private:
	bool ended;

	long long score;
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
	void updateScore();

	std::queue<Event*> events;
	std::list<Projectile> projectiles;
	std::list<Enemy> enemies;
};

#endif // MAP_H
