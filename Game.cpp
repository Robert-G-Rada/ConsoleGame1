#include "Game.h"

Game::Game()
{
	tick_rate = 30;
	startMessage(); // Se afiseaza mesajul de inceput.

	restart = true;
	// Jocul reporneste de cate ori alege utilizatorul.
	while (restart)
	{
		long long score = 0;
		clearScreen(); // Se sterge tot textul de pe ecran
		init();        // Se initializeaza jocul
		score = run(); // Jocul porneste, iar la final se inapoiaza scorul jucatorului.
		clearScreen(); // Se sterge textul de pe ecran
		deleteStuff(); // Se sterg toate obiectele
		endMessage(score); // Se afiseaza mesajul de sfarsit
	}
}

void Game::init()
{
	// Se initializeaza obiectul si se afiseaza chenarul.

	srand(time(NULL));
	running = true;
	frame_start = (SCREEN_WIDTH - FRAME_WIDTH - 1) / 2;

	drawFrame();

	clock1 = new Clock(tick_rate);
	map1 = new Map(300);
}

void Game::deleteStuff()
{
	// Se sterg toate obiectele.
	map1->deleteStuff();

	delete clock1;
	delete map1;
}

long long Game::run()
{
	// Ruleaza jocul.
	long long score = 0;

	while (running)
	{
		// Actualizeaza ceasul.
		clock1->update();

		if (clock1->tick())
		{
			map1->update(); // Actualizeaza harta si obiectele de pe harta.
			score = map1->getScore(); // Actualizeaza scorul.
			if (map1->isEnded()) // Verifica daca jocul trebuie oprit.
				running = false;
		}
	}

	return score;
}

void Game::drawFrame()
{
	// Deseneaza chenarul.

	int x1, x2;
	x1 = (SCREEN_WIDTH - FRAME_WIDTH - 1) / 2 - 1;
	x2 = x1 + FRAME_WIDTH + 1;

	for (int i = x1; i <= x2; i++)
	{
		Console::render(BLOCK , 0, i);
		Console::render(BLOCK, SCREEN_HEIGHT - 1, i);
	}
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		Console::render(BLOCK, i, x1);
		Console::render(BLOCK, i, x2);
	}
}

void Game::startMessage()
{
	// Afiseaza mesajul de inceput.
	Console::render("SET SCREEN BUFFER SIZE AND WINDOW SIZE TO:", 1, 0);
	Console::render("WIDTH = 70", 2, 0);
	Console::render("HEIGHT = 40", 3, 0);
	Console::render("PRESS ANY KEY TO CONTINUE", 4, 0);
	Console::render("CONTROLS:", 7, 0);
	Console::render("MOVE = ARROW KEYS / A & D:", 8, 0);
	Console::render("SHOOT = X / K", 9, 0);

	// Asteapta pana cand se apasa o tasta.
	while (!_kbhit());
	int input = Console::getInput();
	if (input == '=')
		tick_rate = 60;
	else if (input == '-')
		tick_rate = 45;
}

void Game::endMessage(long long score)
{
	// Afiseaza mesajul de sfarsit.
	Console::render("GAME OVER", SCREEN_HEIGHT / 2 - 6, SCREEN_WIDTH / 2 - 5, "RED");
	Console::render("YOUR SCORE : " + Console::toString(score), SCREEN_HEIGHT / 2 - 3, SCREEN_WIDTH / 2 - 7, "BLUE");
	Console::render("PLAY AGAIN?", SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 - 6);
	Console::render("PRESS Y/N", SCREEN_HEIGHT / 2 + 3, SCREEN_WIDTH / 2 - 5);

	int input;
	while (1)
	{
		if (_kbhit())
		{
			input = Console::getInput();
			if (input == (int)'Y' || input == (int)'y')
			{
				// Daca jucatorul a apasat tasta "Y" reporneste jocul.
				restart = true;
				break;
			}
			else if (input == (int)'N' || input == (int)'n')
			{
				// Daca jucatorul a apasat tasta "N" inchide programul.
				restart = false;
				break;
			}
		}
	}
}

void Game::clearScreen()
{
	// Se sterge tot textul de pe ecran inlocuind fiecare caracter cu caracterul ' '.
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
			std::cout << ' ';
		std::cout << '\n';
	}
}