#include "Clock.h"
#include <ctime>

Clock::Clock(int tick_time)
{
	this->tick_time = tick_time;
	last_tick = clock();
	ticks = 0;
}

void Clock::update()
{
	clock_t current_time = clock();
	if (current_time - last_tick >= 1000 / tick_time)
	{
		ticks++;
		last_tick = current_time;
	}
}

bool Clock::tick()
{
	if (ticks > 0)
	{
		ticks--;
		return true;
	}
	return false;
}
