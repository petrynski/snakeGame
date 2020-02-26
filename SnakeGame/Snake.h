#pragma once
#include "Cell.h"
#include <vector>

class Snake
{
private:
	Cell* head;
	std::vector <Cell*> tail;
	int direction;				// 0 right, 1 left, 2 down, 3 up

public:
	Snake()
	{
		this->head = new Cell(5, 5);
		this->direction = 0;
		this->addToTail(4, 5);
		this->addToTail(3, 5);
	}
	
	int getDirection()
	{
		return this->direction;
	}
	
	int getHeadX()
	{
		return this->head->getCordX();
	}
	
	int getHeadY()
	{
		return this->head->getCordY();
	}

	int getTailX(int i)
	{
		return this->tail[i]->getCordX();
	}

	int getTailY(int i)
	{
		return this->tail[i]->getCordY();
	}

	int getTailSize()
	{
		return this->tail.size();
	}

	void setDirection(int direction) 
	{
		this->direction = direction;
	}

	void updateCells()
	{
		for (int i = tail.size() - 1; i > 0; i--)
		{
			tail[i]->setCords(tail[i - 1]->getCordX(), tail[i - 1]->getCordY());
		}
		tail[0]->setCords(head->getCordX(), head->getCordY());

		head->moveCell(direction);
	}

	void addToTail()
	{
		tail.push_back(new Cell(tail.back()->getCordX(), tail.back()->getCordY()));
	}

	void addToTail(int x, int y)
	{
		tail.push_back(new Cell(x, y));
	}

	~Snake() 
	{
		for (int i = tail.size() - 1; i >= 0; i--)
			delete tail[i];

		delete head;
	}
};

