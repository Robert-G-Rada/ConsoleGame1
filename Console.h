#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>

class Console
{
public:
	Console();
	static void render(char output, int i, int j, std::string color);
	static void render(char output, int i, int j);
	static void render(std::string output, int i, int j, std::string color);
	static void render(std::string output, int i, int j);
	static std::string toString(long long x);
	static int getInput();
protected:
private:
	static int getColor(std::string color);
	static void setColor(std::string color);
	static void setCursor(int i, int j);
};

#endif // CONSOLE_H
