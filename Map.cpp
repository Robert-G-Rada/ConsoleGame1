#define _CRT_SECURE_NO_WARNINGS

#include "Map.h"

Map::Map(int size)
{
	// Se initializeaza obiectul.
	player = new Player(this); // Se adauga un jucator pe harta.
	setPlayer(player);

	this->size = size;
	ended = false;
	position = 0;
	scroll_speed = 60;
	scroll_timer = 0;
	score = 0;
	initEvents();
}

void Map::update()
{
	// Actualizeaza harta si obiectele care se afla pe harta.
	updateMap();
	player->update();
	updateProjectiles();
	updateEnemies();
	updateScore();
}

void Map::endGame()
{
	// Termina jocul.
	ended = true;
}

void Map::updateMap()
{
	// Se actualizeaza harta.
	scroll_timer += scroll_speed;
	if (scroll_timer >= SCROLL_TIME)
	{
		// Jucatorul avanseaza pe harta.
		scroll_timer -= SCROLL_TIME;
		position++;
		if (events.size() != 0) // Se declanseaza evenimentele care se afla 
								//pe noua pozitie a hartii.
			while (events.front()->getPosition() == position)
			{
				events.front()->trigger();
				events.pop();
				if (events.size() == 0)
					break;
			}
		if (position > size)
		{
			// Daca jucatorul a ajuns la finalul hartii 
			// se opreste jocul si scorul se dubleaza.
			score *= 2;
			endGame();
		}
	}
}

void Map::updateScore()
{
	// Afiseaza noul scor pe ecran.
	int y = Game::SCREEN_HEIGHT / 2;
	int x = Game::FRAME_START + Game::FRAME_WIDTH + Game::FRAME_START / 4;

	Console::render("SCORE: " + Console::toString(score), y, x, "BLUE");
}

void Map::deleteStuff()
{
	// Sterge toate obiectele de pe harta.
	player->deleteStuff();
	delete player;
	std::queue<Event*> empty_events;
	std::swap(events, empty_events);
	std::list<Projectile> empty_projectiles;
	std::swap(projectiles, empty_projectiles);
	std::list<Enemy> empty_enemies;
	std::swap(enemies, empty_enemies);
}

void Map::updateProjectiles()
{
	// Pentru fiecare proiectil.
	for (std::list<Projectile>::iterator projectile = projectiles.begin(); projectile != projectiles.end();)
	{
		bool erased = false;
		projectile->update(); // Se actualizeaza proiectilul.
		if (projectile->is_removed)
		{
			// Sterge proiectilele care trebuiesc sterse.
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
			// Verifica daca proiectilul a lovit vreun inamic.
			if (enemy->checkHit(*projectile))
			{
				erased = true;

				projectile->erase();
				projectile = projectiles.erase(projectile);
				break;
			}
		}
		if (erased == false)
		{
			// Daca proiectilul nu a fost sters, verifica daca a lovit jucatorul.
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
	for (std::list<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
	{
		if (enemy->isRemoved())
		{
			// Daca inamicul a fost distrus mareste scorul si sterge obiectul.
			score += enemy->getValue();

			std::list<Enemy>::iterator t = enemy;
			++t;
			if (t == enemies.end())
			{
				enemies.erase(enemy);
				break;
			}
			enemy = enemies.erase(enemy);
		}
	}
	// Actualizeaza inamicii care nu au fost stersi.
	for (std::list<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
		enemy->update();

	// Verifica daca unul dintre inamici a lovit nava jucatorului.
	for (std::list<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
	{
		enemy->checkHitPlayer(player);
	}
}

void Map::addProjectile(Projectile projectile)
{
	// Adauga un proiectil in lista cu proiectile.
	projectiles.push_back(projectile);
}

void Map::addEnemy(Enemy enemy)
{
	// Adauga un inamic in lista cu inamici.
	enemies.push_back(enemy);
}

void Map::setPlayer(Player *player)
{
	this->player = player;
}

void Map::initEvents()
{
	// Se citesc dintr-un fisier pozitiile tuturor evenimentelor.
	FILE *in = fopen("Map.txt", "r");
	
	int x, y;
	while (1)
	{
		std::fscanf(in, "%d%d", &x, &y);
		if (x == -1 || y == -1) // fisierul va avea la sfarsit "-1 -1" care marcheaza sfarsitul fisierului.
			break;
		events.push(new Event(y, this, rand() % 5 + 1, x)); // adauga evenimentul in lista evenimentelor.
	}

	fclose(in);
}

bool Map::isEnded()
{
	// Inapoiaza valoarea "true" daca jocul trebuie oprit.
	return ended;
}

long long Map::getScore()
{
	// Inapoiaza scorul jucatorului.
	return score;
}