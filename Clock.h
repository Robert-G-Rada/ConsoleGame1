#ifndef CLOCK_H
#define CLOCK_H

#include <ctime>

class Clock
{
public:
	Clock(int tick_time);
	void update();
	bool tick();
protected:
private:
	int ticks;
	int tick_time;
	clock_t last_tick;
};

#endif // CLOCK_H
