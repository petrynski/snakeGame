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
	Snake();
	int getDirection();
	int getHeadX();
	int getHeadY();
	int getTailX(int i);
	int getTailY(int i);
	int getTailSize();
	void setDirection(int direction);
	void updateCells();
	void addToTail();
	void addToTail(int x, int y);
	~Snake();
};

