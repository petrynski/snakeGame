#include <iostream>
#include <windows.h>
#include "Cell.h"
#include "Fruit.h"
#include "Snake.h"
#include "Drawer.h"
#include <ctime>

//TODO 
//	Highscores
//	Two Players Mode
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
int tailGhostX = -1;
int tailGhostY = -1;

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
	snakePointer = new Snake(MARGIN);
	fruitPointer = new Fruit(WIDTH, HEIGHT, MARGIN);

	//Draws arena once to optimise game update iteration
	Drawer::drawArena(WIDTH, HEIGHT, MARGIN);
}

void draw()
{
	//Drawer is also used:
	//	1) To draw arena in launch function
	//	2) To draw dead snake cells in deadAnimation function
	Drawer::drawFruit(fruitPointer->getPositionX(), fruitPointer->getPositionY());
	Drawer::drawSnakeHead(snakePointer->getHeadX(), snakePointer->getHeadY());
	for (int i = 0; i < snakePointer->getTailSize(); i++)
		Drawer::drawSnakeTail(snakePointer->getTailX(i), snakePointer->getTailY(i));
	Drawer::drawSideMenu(score, (int)difftime(time(nullptr),start), WIDTH, MARGIN);

	//Clears image where tail was before
	if(tailGhostX!=-1&&tailGhostY!=-1)
		Drawer::clear(tailGhostX,tailGhostY);
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
		return;
	}

	// Takes coordinates of the cell that will be empty
	tailGhostX = snakePointer->getTailX(snakePointer->getTailSize() - 1);
	tailGhostY = snakePointer->getTailY(snakePointer->getTailSize() - 1);

	snakePointer->updateCells();
	Sleep(100);	//	Makes game go slower
}

void deadAnimation()
{
	Drawer::drawArena(WIDTH, HEIGHT, MARGIN);
	Drawer::drawSideMenu(score, difftime(time(nullptr), start), WIDTH, MARGIN);
	for (int j = 0; j < snakePointer->getTailSize(); j++)
		Drawer::drawSnakeDead(snakePointer->getTailX(j), snakePointer->getTailY(j));
	Drawer::drawSnakeDead(snakePointer->getHeadX(), snakePointer->getHeadY());

	for (int i = snakePointer->getTailSize() - 1; i >= 0; i--)
	{
		Sleep(100);
		Drawer::clear(snakePointer->getTailX(i), snakePointer->getTailY(i));
	}
	

}

int outro()
{
	delete snakePointer;
	delete fruitPointer;
	char anwser;
	while (1) {
		system("CLS");
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(output, 7);
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
	deadAnimation();
	if (outro())
		goto start;

	return 0;
}
