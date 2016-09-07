#include "Player.h"

Player::Player(Game *game, Map *map1)
{
	this->game = game;
	this->map1 = map1;
	this->x = Game::FRAME_WIDTH / 2;
	this->y = Game::SCREEN_HEIGHT - 4;
	health = 10;

	gun = new Gun(-1, map1);

	drawPlayer();
}

void Player::update()
{
	gun->update();

	if (_kbhit())
	{
		switch (Console::getInput())
		{
		case 75: case 97: // left
			move(-1);
			break;
		case 77: case 100: //right
			move(1);
			break;
		case 106: case 122: // Z
			break;
		case 107: case 120: // X
			gun->shoot(x, y-1);
			break;
		}
	}
}

bool Player::checkHit(int x, int y, int damage)
{
	if (x == this->x && y == this->y)
	{
		health -= damage;
		if (health <= 0)
			map1->endGame();
		return true;
	}
	return false;
}

void Player::move(int x)
{
	if (this->x + x < 1 || this-> x + x > Game::FRAME_WIDTH - 2)
		return;
	deletePlayer();
	this->x += x;
	drawPlayer();
}

void Player::drawPlayer()
{
	int x = this->x + Game::FRAME_START;
	int y = Game::SCREEN_HEIGHT - 3;
	Console::setCursor(y, x);
	std::cout << '#';
	y++;
	x--;
	for (int i = 1; i <= 3; i++, x++)
	{
		Console::setCursor(y, x);
		std::cout << '#';
	}
	Console::setCursor(0, 0);
}

void Player::deletePlayer()
{
	int x = this->x + Game::FRAME_START;
	int y = Game::SCREEN_HEIGHT - 3;
	Console::setCursor(y, x);
	std::cout << ' ';
	y++;
	x--;
	for (int i = 1; i <= 3; i++, x++)
	{
		Console::setCursor(y, x);
		std::cout << ' ';
	}
	Console::setCursor(0, 0);
}
