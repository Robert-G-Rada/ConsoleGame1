#include "Event.h"

Event::Event(int position, Map *map1, int type, int x)
{
	this->type = type;
	this->x = x;
	this->map1 = map1;
	this->position = position;
}

void Event::trigger()
{
	switch (type)
	{
	case 1:
		map1->addEnemy(Enemy(map1, x));
		break;
	}
}

int Event::getPosition()
{
	return position;
}