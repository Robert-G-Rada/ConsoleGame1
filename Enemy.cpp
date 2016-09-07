#include "Enemy.h"

/*
	Se initializeaza obiectul de tip "Enemy".
	Daca culoarea si valoarea nu sunt precizate, ele vor lua 
	valori prestabilite (value = 10, color = "WHITE").
*/
Enemy::Enemy(Map *map1, int x)
{
	move_timer = 0;

	this->map1 = map1;
	this->x = x;
	init();
	this->y = height;
	this->gun = new Gun(1, map1);
	value = 10;
	color = "WHITE";

	drawEnemy();
}

Enemy::Enemy(Map *map1, int x, int value, std::string color)
{
	move_timer = 0;

	this->map1 = map1;
	this->x = x;
	init();
	this->y = height;
	this->gun = new Gun(1, map1);
	this->value = value;
	this->color = color;

	drawEnemy();
}

void Enemy::update()
{
	// Se realizeaza actualizarea obiectului

	// Daca obiectul trebuie sters acesta nu mai este actualizat
	if (is_removed)
		return;

	/* Se verifica daca obiectul trebuie deplasat pe verticala.
	   Miscarea se realizeaza cu ajutorul functiei "move".
	   Frecventa deplasarilor depinde de variabila "speed".
	*/
	move_timer += speed;
	if (move_timer >= MOVE_TIME)
		move(0, 1);

	if (is_removed)
		return;

	// Se actualizeaza arma, iar daca este pregatita de tragere se lanseaza un proiectil.
	gun->update();
	if (gun->isReady())
	{
		gun->shoot(x, y + 1);
	}
}

bool Enemy::checkHit(Projectile projectile)
{
	// Se verifica daca inamicul este atins de un proiectil.

	for (unsigned i = 0; i < body.size(); i++)
	{
		if (this->x + body[i].x == projectile.getX())
		{
			if (this->y + body[i].y == projectile.getY() ||
				this->y + body[i].y == projectile.getY() + 1)
			{
				/*
				    Daca proiectilul a fost lansat de jucator, se scade din viata.
				    Daca proiectilul a fost lansat de un alt inamic, atunci nu se 
				    intampla nimic pentru a evita cazul in care inamicii se omoara intre ei.
				*/
				if (projectile.getOwner() == -1)
					health -= projectile.getDamage();
				/*
					Daca viata inamicului, reprezentata prin variabila "health" a ajuns sub 0
					se sterge obiectul.
				*/
				if (health <= 0)
				{
					is_removed = true;
					deleteEnemy();
				}
				return true;
			}
		}
	}
	return false;
}

void Enemy::checkHitPlayer(Player *player)
{
	// Se verifica daca inamicul se loveste de jucator
	for (unsigned i = 0; i < body.size(); i++)
	{
		// Daca o parte din inamic se loveste de jucator, jucatorul sufera daune foarte mari.
		player->checkHit(x + body[i].x, y + body[i].y, Game::INF);
	}
}

void Enemy::drawEnemy()
{
	/* 
		Se afiseaza pe ecran nava inamica.
		Aceasta va fi de forma : 
								  ###
								   #
	*/
	for (unsigned i = 0; i < body.size(); i++)
	{
		Console::render('#', y + body[i].y, x + body[i].x + Game::FRAME_START, color);
	}
}

void Enemy::deleteEnemy()
{
	// Se sterge nava inamica de pe ecran.
	
	for (unsigned i = 0; i < body.size(); i++)
	{
		Console::render(' ', y + body[i].y, x + body[i].x + Game::FRAME_START);
	}
}

void Enemy::move(int x, int y)
{
	/*
		Pentru a misca o nava se sterge mai intai de pe ecran,
		se modifica coordonatele ei, apoi se afiseaza in noua pozitie.
	*/
	deleteEnemy();
	this->x += x;
	this->y += y;
	//   Se verifica daca nava a iesit din cadru.
	checkCollision();
	//   Daca nava trebuie stearsa ea nu mai trebuie afisata pe ecran.
	if (is_removed)
		return;
	drawEnemy();
	move_timer -= MOVE_TIME;
}

void Enemy::checkCollision()
{
	// Se verifica pentru fiecare parte din nava daca a iesit din cadru.
	for (unsigned i = 0; i < body.size(); i++)
	{
		if (y + body[i].y >= Game::SCREEN_HEIGHT - 1)
		{
			is_removed = true;
			return;
		}
	}
}

void Enemy::init()
{
	// Se initializeaza variabilele obiectului.
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
	// Inapoiaza valoarea "true" daca obiectul trebuie sters.
	return is_removed;
}

int Enemy::getValue()
{
	// Inapoiaza punctajul pe care il primeste jucatorul daca distruge nava inamica.
	return value;
}