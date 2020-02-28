#include "Drawer.h"

void Drawer::drawArena(int width, int height, int margin)
{
	system("CLS");
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(output, 7);
	std::string border = "";

	SetConsoleCursorPosition(output, { (SHORT)margin, (SHORT)margin });
	for (int i = 0; i <= width; i++)
	{
		border += "-";
	}
	std::cout << border;

	for (SHORT i = margin + 1; i < (margin + height); i++)
	{
		SetConsoleCursorPosition(output, { (SHORT)margin , i });
		printf("|");
		SetConsoleCursorPosition(output, { (SHORT)(margin + width), i });
		printf("|");
	}

	SetConsoleCursorPosition(output, { (SHORT)margin, (SHORT)(height + margin) });
	std::cout << border;

}

void Drawer::drawSnakeHead(int headX, int headY)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(output, 2);
	SetConsoleCursorPosition(output, { (SHORT)headX, (SHORT)headY });
	printf("@");
}

void Drawer::drawSnakeTail(int tailX, int tailY)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(output, 2);
	SetConsoleCursorPosition(output, { (SHORT)tailX, (SHORT)tailY });
	printf("O");
}

void Drawer::drawFruit(int fruitX, int fruitY)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(output, 4);
	SetConsoleCursorPosition(output, { (SHORT)fruitX, (SHORT)fruitY });
	printf("$");
}

void Drawer::drawSideMenu(int score, int time, int width, int margin)
{
	short X = margin * 2 + width;
	short Y = margin;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, { X, Y });
	SetConsoleTextAttribute(output, 10);

	printf("Snake game!");
	SetConsoleCursorPosition(output, { X, Y+1 });
	printf("Score: %d, Time %d", score, time);

	SetConsoleCursorPosition(output, { X, Y + 5 });
	printf("Author: Michal Petrynski");

}


void Drawer::drawSnakeDead(int X, int Y)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(output, 12);
	SetConsoleCursorPosition(output, { (SHORT)X, (SHORT)Y });
	printf("X");
}


void Drawer::clear(int X, int Y)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, { (SHORT)X, (SHORT)Y });
	printf(" ");
	SetConsoleCursorPosition(output, {0, 0});
}