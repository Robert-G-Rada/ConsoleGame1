#ifndef CONSOLE_H
#define CONSOLE_H

class Console
{
public:
	Console();
	static void setColor(int color);
	static void setCursor(int i, int j);
	static int getInput();
protected:
private:
};

#endif // CONSOLE_H
