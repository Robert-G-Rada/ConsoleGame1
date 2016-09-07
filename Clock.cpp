#include "Clock.h"
#include <ctime>

Clock::Clock(int tick_time)
{
	this->tick_time = tick_time;
	/*
		tick_time = de cate ori "ticaie" ceasul intr-o secunda, 
		adica de cate ori pe secunda se face actualizarea jocului.
		Eu am ales ca jocul sa fie actualizat de 30 de ori pe secunda.
	*/
	last_tick = clock();
	ticks = 0;
}

void Clock::update()
{
	/*
		Se verifica daca a trecut suficient timp de la ultima actualizare a jocului.
	*/
	clock_t current_time = clock();
	if (current_time - last_tick >= 1000 / tick_time)
	{
		ticks++;
		last_tick = current_time;
	}
}

bool Clock::tick()
{
	/*
		Daca jocul trebuie actualizat aceasta functie va inapoia valoarea "true",
		in caz contror va inapoia valoarea "false".
	*/
	if (ticks > 0)
	{
		ticks--;
		return true;
	}
	return false;
}
