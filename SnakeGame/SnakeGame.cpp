#include <iostream>
#include <windows.h>
#include "Cell.h"
#include "Fruit.h"
#include "Snake.h"
#include "Drawer.h"
#include <ctime>
#include <fstream>

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
struct highscore {
	int hscore = 0;
	std::string name = "None";
};

Snake* snakePointer;
Fruit* fruitPointer;
bool gameOver;
unsigned int score;
time_t start;
int tailGhostX = -1;
int tailGhostY = -1;
highscore highscoresTable[10];
highscore currentScore;

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

void highscoresFileSetup()
{
	std::ifstream highscores("highscores.txt");
	std::string line;
	int i = 0;
	if(highscores.is_open())
		while (!highscores.eof())
		{
			if (i >= 10)
				break;
			highscores >> highscoresTable[i].name;
			highscores >> highscoresTable[i].hscore;
			i++;
		}
	highscores.close();
}

void highscoreSave()
{
	std::ofstream file("highscores.txt");
	system("CLS");
	int i;
	std::string oldName;
	int oldScore;

	for (i = 0; i < 10; i++)
	{
		if (score > highscoresTable[i].hscore)
		{
			oldName = highscoresTable[i].name;
			oldScore = highscoresTable[i].hscore;
			std::string newHighscoreName = "";
			std::cout << "Type your name: ";
			std::cin >> newHighscoreName;
			highscoresTable[i].name = newHighscoreName;
			highscoresTable[i].hscore = score;
			break;
		}
	}
	i++;
	for (i+1; i < 10; i++)
	{
		int helpInt;;
		std::string helpString;
		helpInt = highscoresTable[i].hscore;
		helpString = highscoresTable[i].name;
		highscoresTable[i].hscore = oldScore;
		highscoresTable[i].name = oldName;
		oldScore = helpInt;
		oldName = helpString;
	}
	
	for (int i = 0; i < 10; i++)
	{
		file << highscoresTable[i].name << " " << highscoresTable[i].hscore << std::endl;
	}

	file.close();
}

void launch()
{
	highscoresFileSetup();
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
	for (int i = 0; i < 10; i++)
		Drawer::drawHighscores(i, highscoresTable[i].hscore, highscoresTable[i].name, WIDTH, MARGIN);

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
	if (GetKeyState(VK_ESCAPE) & 0x8000)
	{
		system("CLS");
		exit(0);
	}
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
	highscoreSave();

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
