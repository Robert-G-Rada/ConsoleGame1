#include "Projectile.h"

Projectile::Projectile(int x, int y, int owner)
{
	/*
	Se initializeaza obiectul.
	Variabila "owner" are valoarea -1 daca arma apartine jucatorului
	si valoarea 1 daca apartine unui inamic.
	*/
	is_removed = false;
	move_timer = 0;
	if (owner == -1)
	{
		damage = 5;
		speed = 300;
	}
	else
	{
		damage = 1;
		speed = 300;
	}
	this->x = x;
	this->y = y;
	this->dy = owner;

	draw(); // Afiseaza proiectilul pe ecran.
}

void Projectile::update()
{
	// Actualizeaza proiectilul.
	move_timer += speed;
	if (move_timer >= MOVE_TIME) 			 
		move();					// Daca a trecut suficient timp 
								// deplaseaza proiectilul.
}

void Projectile::move()
{
	// Se realizeaza deplasarea proiectilului.
	erase(); // Se sterge proiectilul de pe ecran.
	y += dy; // Se modifica pozitia proiectilului.
	move_timer -= MOVE_TIME;

	if (y < 1 || y >= Game::SCREEN_HEIGHT - 1)
	{
		// Daca proiectilul iese din chenar acesta este sters.
		is_removed = true;
		return;
	}

	draw(); // Afiseaza proiectilul pe ecran in noua pozitie.
}

void Projectile::draw()
{
	// Afiseaza proiectilul pe ecran.
	if (y < 1 || y >= Game::SCREEN_HEIGHT - 1)
		return;
	Console::render('|', y, Game::FRAME_START + x);
}

void Projectile::erase()
{
	// Sterge proiectilul de pe ecran.
	if (y < 1 || y >= Game::SCREEN_HEIGHT - 1)
		return;
	Console::render(' ', y, Game::FRAME_START + x);
}

int Projectile::getX()
{
	// Inapoiaza pozitia proiectilului pe orizontala.
	return x;
}

int Projectile::getY()
{
	// Inapoiaza pozitia proiectilului pe verticala.
	return y;
}
int Projectile::getDamage()
{
	// Inapoiaza daunele provocate de proiectil.
	return damage;
}

int Projectile::getOwner()
{
	// Inapoiaza valoarea -1 daca proiectilul a fost lansat de jucator
	// sau 1 daca proiectilul a fost lansat de un inamic.
	return dy;
}