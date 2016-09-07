#include "Console.h"

Console::Console()
{
	//ctor
}

/*
	Cele patru functii "render" sunt folosite pentru a afisa text pe ecran.
	Pentru aceasta mai intai se muta cursorul in pozitia in care vrem sa apara textul, 
	apoi este setata culoarea dorita si se afiseaza textul.
	La sfarsit, cursorul si culoarea sunt setate la valorile initiale pentru a nu crea probleme.
*/
void Console::render(char output, int i, int j, std::string color)
{
	setCursor(i, j);
	setColor(color);
	std::cout << output;
	setColor("WHITE");
	setCursor(0, 0);
}

void Console::render(std::string output, int i, int j, std::string color)
{
	setCursor(i, j);
	setColor(color);
	std::cout << output;
	setColor("WHITE");
	setCursor(0, 0);
}

void Console::render(std::string output, int i, int j)
{
	setCursor(i, j);
	std::cout << output;
	setCursor(0, 0);
}

void Console::render(char output, int i, int j)
{
	setCursor(i, j);
	std::cout << output;
	setCursor(0, 0);
}

void Console::setColor(std::string color)
{
	/*
		Se schimba culoarea textului din consola.
		Se foloseste functia "getColor" pentru a obtine numarul asociat culorii dorite.
	*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), getColor(color));
}
 
int Console::getColor(std::string color)
{
	/*
		"getColor" inapoiaza numarul asociat culorii reprezentate prin variabila de tip string "color".
	*/
	for (auto &it : color)
		it = tolower(it);
	
	if (color == "black")
		return 0;
	if (color == "dark blue")
		return 1;
	if (color == "dark green")
		return 2;
	if (color == "dark cyan")
		return 3;
	if (color == "dark red")
		return 4;
	if (color == "dark pink")
		return 5;
	if (color == "dark yellow")
		return 6;
	if (color == "dark white")
		return 7;
	if (color == "grey")
		return 8;
	if (color == "blue")
		return 9;
	if (color == "green")
		return 10;
	if (color == "cyan")
		return 11;
	if (color == "red")
		return 12;
	if (color == "pink")
		return 13;
	if (color == "yellow")
		return 14;
	if (color == "white")
		return 15;

	return 15;
}

void Console::setCursor(int i, int j)
{
	/*
		Se muta cursorul in pozitia (j, i).
	*/
	COORD cPos;
	cPos.X = j;
	cPos.Y = i;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cPos);
}

int Console::getInput()
{
	/*
		Se inapoiaza valoarea tastei care a fost apasata, 
		sau 0 in cazul in care nu a fost apasata nicio tasta.
	*/
	int input;
	if (_kbhit())
	{
		input = _getch();

		if (input == 0 || input == 224) input = _getch();
		return input;
		// 75 = left | 72 = up | 77 = right | 80 = down
	}
	return 0;
}

std::string Console::toString(long long x)
{
	/*
		Se transforma numarul "x" intr-un sir de caractere 
		pentru a putea fi afisat cu ajutorul functiei "render".
	*/
	std::string ret;

	long long y = x;
	long long p10 = 1;
	int digits = 0;
	/*
		Se numara cifrele lui "x" si se calculeaza puterea lui 10 
		la care trebuie impartit pentru a obtine prima cifra.
	*/
	while (y > 0)
	{
		p10 *= 10;
		y /= 10;
		digits++;
	}

	// Pentru cazul in care numarul este 0
	if (digits == 0)
		digits = 1;

	// Se adauga fiecare cifra a lui "x" intr-un sir.
	while (x > 0)
	{
		p10 /= 10;
		ret.push_back((x / p10) + '0');
		x %= p10;
		digits--;
	}
	
	/*
	 Se completeaza sirul cu 0 pana cand numarul de caractere
	 din sir este egal cu numarul de cifre al lui "x".
	*/
	while (digits--)
		ret.push_back('0');

	return ret;
}