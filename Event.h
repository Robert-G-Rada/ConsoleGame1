#ifndef EVENT_H
#define EVENT_H

#include "Map.h"

class Map;

class Event
{
public:
	Event(int position, Map *map1, int type, int x);
	void trigger();
	int getPosition();
private:
	int position;
	int type;
	int x;
	Map *map1;
private:
};

#endif // EVENT_H
