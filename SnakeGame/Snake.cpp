#include "Snake.h"

Snake::Snake(int margin)
{
	this->head = new Cell(margin + 5, margin + 5);
	this->direction = 0;
	this->addToTail(margin + 4, margin + 5);
	this->addToTail(margin + 3, margin + 5);
}

int Snake::getDirection()
{
	return this->direction;
}

int Snake::getHeadX()
{
	return this->head->getCordX();
}

int Snake::getHeadY()
{
	return this->head->getCordY();
}

int Snake::getTailX(int i)
{
	return this->tail[i]->getCordX();
}

int Snake::getTailY(int i)
{
	return this->tail[i]->getCordY();
}

int Snake::getTailSize()
{
	return this->tail.size();
}

void Snake::setDirection(int direction)
{
	this->direction = direction;
}

void Snake::updateCells()
{
	for (int i = tail.size() - 1; i > 0; i--)
	{
		tail[i]->setCords(tail[i - 1]->getCordX(), tail[i - 1]->getCordY());
	}
	tail[0]->setCords(head->getCordX(), head->getCordY());

	head->moveCell(direction);
}

void Snake::addToTail()
{
	tail.push_back(new Cell(tail.back()->getCordX(), tail.back()->getCordY()));
}

void Snake::addToTail(int x, int y)
{
	tail.push_back(new Cell(x, y));
}

Snake::~Snake()
{
	for (int i = tail.size() - 1; i >= 0; i--)
		delete tail[i];

	delete head;
}


