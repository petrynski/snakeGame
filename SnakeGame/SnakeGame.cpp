#include <iostream>
#include <windows.h>
#include "Cell.h"
#include "Fruit.h"
#include "Snake.h"
#include "Drawer.h"
#include <ctime>

#define MARGIN  3
#define WIDTH   50
#define HEIGHT  20
 
enum direction{
RIGHT = 0,
LEFT = 1,
DOWN = 2,
UP = 3
};

Snake* snakePointer;
Fruit* fruitPointer;
bool gameOver;
unsigned int score;
time_t start;

bool checkCollision()
{
	for (int i = 0; i < snakePointer->getTailSize(); i++)
	{
		if ((snakePointer->getHeadX() == snakePointer->getTailX(i)) && (snakePointer->getHeadY() == snakePointer->getTailY(i)))
			return true;
	}

	if ((snakePointer->getHeadX() <= MARGIN) || (snakePointer->getHeadX() >= MARGIN+WIDTH))
		return true;

	else if ((snakePointer->getHeadY() <= MARGIN) || (snakePointer->getHeadY() >= MARGIN+HEIGHT))
		return true;

	else
		return false;
}

void launch()
{
	time(&start);
	score = 0;
	gameOver = false;
	snakePointer = new Snake();
	fruitPointer = new Fruit(WIDTH, HEIGHT, MARGIN);
}

//void draw()
//{
//	system("CLS");
//
//	//	Drawing snake
//	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD position = { snakePointer->getHeadX(), snakePointer->getHeadY() };
//	SetConsoleCursorPosition(output, position);
//	std::cout<<'#';
//
//	for (int i = 0; i < snakePointer->getTailSize(); i++)
//	{
//		position = { (SHORT)snakePointer->getTailX(i), (SHORT)snakePointer->getTailY(i) };
//		SetConsoleCursorPosition(output, position);
//		std::cout << '0';
//	}
//
//	//	Drawing game arena
//	SetConsoleCursorPosition(output, { 3,3 });
//	for (int i = 0; i < 52; i++)
//	{
//		std::cout << '-';
//	}
//
//	for (SHORT i = 4; i < 24; i++)
//	{
//		SetConsoleCursorPosition(output, { 3 , i });
//		std::cout << '|';
//		SetConsoleCursorPosition(output, { 54 , i });
//		std::cout << '|';
//	}
//
//	SetConsoleCursorPosition(output, { 3,24 });
//	for (SHORT i = 0; i < 52; i++)
//	{
//		std::cout << '-';
//	}
//
//	//	Drawing fruit
//	position = { (SHORT)fruitPointer->getPositionX(), (SHORT)fruitPointer->getPositionY() };
//	SetConsoleCursorPosition(output, position);
//	std::cout << '%';
//}

void draw()
{
	Drawer::drawArena(WIDTH, HEIGHT, MARGIN);
	Drawer::drawFruit(fruitPointer->getPositionX(), fruitPointer->getPositionY());
	Drawer::drawSnakeHead(snakePointer->getHeadX(), snakePointer->getHeadY());
	for (int i = 0; i < snakePointer->getTailSize(); i++)
		Drawer::drawSnakeTail(snakePointer->getTailX(i), snakePointer->getTailY(i));
	Drawer::drawSideMenu(score, (int)difftime(time(nullptr),start), WIDTH, MARGIN);
}

void checkInput()
{
	if (GetKeyState(VK_RIGHT) & 0x8000)
		snakePointer->setDirection(direction(RIGHT));
	if (GetKeyState(VK_LEFT) & 0x8000)
		snakePointer->setDirection(direction(LEFT));
	if (GetKeyState(VK_DOWN) & 0x8000)
		snakePointer->setDirection(direction(DOWN));
	if (GetKeyState(VK_UP) & 0x8000)
		snakePointer->setDirection(direction(UP));
}

void updateGame()
{
	if ((snakePointer->getHeadX() == fruitPointer->getPositionX()) && (snakePointer->getHeadY() == fruitPointer->getPositionY()))
	{
		fruitPointer->setNewPosition();
		snakePointer->addToTail();
		score++;
	}
	
	if (checkCollision())
	{
		gameOver = true;
	}

	snakePointer->updateCells();
	Sleep(30);	//	Most likely will be needed, but creates lags
}

int outro()
{
	delete snakePointer;
	delete fruitPointer;
	char anwser;
	while (1) {
		system("CLS");
		std::cout << "Do you want to try again? (T/F)" << std::endl;
		std::cin >> anwser;
		std::cin.ignore(INT_MAX,'\n');	// Flushing std In
		switch (anwser)
		{
		case 't':
		case 'T':
			return 1;
			break;		// it's useless, but for the sake of all...

		case 'f':
		case 'F':
			return 0;
		}
	}
}

int main()
{
start:
	launch();
	while (!gameOver)
	{
		draw();
		checkInput();
		updateGame();
	}
	if (outro())
		goto start;

	return 0;
}
