#include "Player.h"

Player::Player(Map *map1)
{
	// Se actualizeaza obiectul de tip "Player".
	this->map1 = map1;
	this->x = Game::FRAME_WIDTH / 2;
	this->y = Game::SCREEN_HEIGHT - 4;
	health = MAX_HEALTH;

	body.push_back(std::make_pair(0, 0));
	body.push_back(std::make_pair(0, -1));
	body.push_back(std::make_pair(-1, -1));
	body.push_back(std::make_pair(1, -1));

	gun = new Gun(-1, map1);

	drawPlayer();     // Se afiseaza nava jucatorului.
	drawHPBarFrame(); // Se afiseaza chenarul barei de viata.
	updateHPBar();    // Se afiseaza bara de viata.
}

void Player::update()
{
	// Se actualizeaza arma jucatorului.
	gun->update();

	if (_kbhit()) // Verifica daca a fost apasata o tasta.
	{
		switch (Console::getInput())
		{
		case 75: case 'A': case 'a': // Daca a fost apasata tasta 'A' sau sageata
									 // stanga deplaseaza jucatorul la stanga.
			move(-1);
			break;
		case 77: case 'D': case 'd': // Daca a fost apasata tasta 'D' sau sageata
									 // dreapta deplaseaza jucatorul la dreapta.
			move(1);
			break;
		case 'x': case 'X': case 'j': case 'J':	// Daca a fost apasata tasta 'X' sau 
												// tasta 'J' lanseaza un proiectil
			gun->shoot(x, y-1);
			break;
		}
	}
}

bool Player::checkHit(int x, int y, int damage)
{
	// Verifica daca jucatorul este lovit de obiectul aflat la pozitia (x, y) 
	// care poate provoca daune de valoare "damage".
	for (auto &it : body)
	{
		if (x + it.first == this->x && y + it.second == this->y)
		{
			// Daca jucatorul a fost lovit modifica valoare vietii.
			changeHealth(damage);
			return true;
		}
	}
	
	return false;
}

void Player::move(int x) // Muta jucatorul la stanga sau la dreapta.
{
	// Daca jucatorul ar iesi din chenar nu il misca.
	if (this->x + x < 1 || this-> x + x > Game::FRAME_WIDTH - 2)
		return;
	deletePlayer(); // Sterge nava jucatorului de pe ecran.
	this->x += x;   // Modifica pozitia jucatorului.
	drawPlayer();   // Afiseaza nava jucatorului in noua pozitie.
}

void Player::updateHPBar()
{
	// Afiseaza bara de viata pe ecran.
	int x = Game::FRAME_START / 4;
	int y = Game::SCREEN_HEIGHT / 2;

	Console::render("          ", y, x);
	for (int i = 0; i < health; i++)
	{
		Console::render(Game::BLOCK, y, x + i, "RED");
	}
}

void Player::changeHealth(int damage)
{
	health -= damage; // Modifica valoarea vietii jucatorului.
	updateHPBar();    // Afiseaza bara de viata dupa modificari.
	if (health <= 0)  // Daca viata jucatorului a ajuns la 0 opreste jocul.
		map1->endGame();
}

void Player::deleteStuff()
{
	while (!body.empty()) // Sterge corpul navei.
		body.pop_back();
	delete gun; // Sterge arma jucatorului.
}

void Player::drawPlayer()
{
	/*
		Afiseaza nava jucatorului pe ecran.
		Aceasta va fi de forma: 
								 #
								###
	*/
	int x = this->x + Game::FRAME_START;
	int y = Game::SCREEN_HEIGHT - 3;
	Console::render("#", y, x);
	y++;
	x--;
	for (int i = 1; i <= 3; i++, x++)
	{
		Console::render("#", y, x);
	}
}

void Player::drawHPBarFrame()
{
	/*
		Afiseaza chenarul barei de viata pe ecran.
		Acesta va fi de forma:
								|----------|
								|          |
								|----------|					
	*/
	int x = Game::FRAME_START / 4 - 1;
	int y = Game::SCREEN_HEIGHT / 2 - 1;
	
	Console::render("HP", y - 1, x + 5);
	Console::render("|----------|", y, x);
	Console::render("|          |", y + 1, x);
	Console::render("|----------|", y + 2, x);
}

void Player::deletePlayer()
{
	// Sterge nava jucatorului de pe ecran.
	int x = this->x + Game::FRAME_START;
	int y = Game::SCREEN_HEIGHT - 3;
	Console::render(" ", y, x);
	y++;
	x--;
	for (int i = 1; i <= 3; i++, x++)
	{
		Console::render(" ", y, x);
		std::cout << ' ';
	}
}

