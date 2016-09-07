#include "Gun.h"

Gun::Gun(int owner, Map *map1)
{
	/*
	   Se initializeaza obiectul.
	   Variabila "owner" are valoarea -1 daca arma apartine jucatorului
	   si valoarea 1 daca apartine unui inamic.
	*/
	if (owner == -1)
	{
		timer = ATTACK_TIME;
		speed = 60;
	}
	else
	{
		timer = rand()%ATTACK_TIME;
		speed = 10;
	}
	this->owner = owner;
	this->map1 = map1;
}

void Gun::update()
{
	/* 
		Se actualizeaza arma.
		Daca variabila "timer" ajunge la valoarea fixa "ATTACK_TIME", 
		atunci arma poate fi folosita.
	*/
	timer += speed;
	if (timer >= ATTACK_TIME)
		timer = ATTACK_TIME;
}

void Gun::shoot(int x, int y)
{
	// Lanseaza un proiectil la pozitia (x, y).
	if (timer >= ATTACK_TIME)
	{
		map1->addProjectile(Projectile(x, y, owner));
		timer = 0;
	}
}

bool Gun::isReady()
{
	// Daca arma este pregatita de a trage se inapoiaza valoarea "true".
	if (timer >= ATTACK_TIME)
		return true;
	return false;
}