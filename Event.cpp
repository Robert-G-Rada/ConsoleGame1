#include "Event.h"

Event::Event(int position, Map *map1, int type, int x)
{
	// Se initializeaza obiectul.
	this->type = type;
	this->x = x;
	this->map1 = map1;
	this->position = position;
}

void Event::trigger()
{
	// Se adauga un obiect de tip "Enemy" in map1 a carui 
	// caracteristici depind de tipul evenimentului.
	switch (type)
	{
	case 1:
		map1->addEnemy(Enemy(map1, x));
		break;
	case 2:
		map1->addEnemy(Enemy(map1, x, 20, "BLUE"));
		break;
	case 3:
		map1->addEnemy(Enemy(map1, x, 30, "YELLOW"));
		break;
	case 4:
		map1->addEnemy(Enemy(map1, x, 40, "GREEN"));
		break;
	case 5:
		map1->addEnemy(Enemy(map1, x, 50, "RED"));
	}
}

int Event::getPosition()
{
	// Se inapoiaza pozitia pe harta la care are loc evenimentul
	return position;
}