#pragma once
#include"Snake.h"

class Fruit
{
private:
	int margin, width, height;
	int cordX, cordY;
public:
	Fruit(int width, int height, int margin)
	{
		this->setArea(width, height, margin);
		cordX = (rand() % (width - 1)) + margin + 1;
		cordY = (rand() % (height - 1)) + margin + 1;
	}

	void setNewPosition()
	{
		cordX = (rand() % (width - 1)) + margin + 1;
		cordY = (rand() % (height - 1)) + margin + 1;
	}

	int getPositionX()
	{
		return cordX;
	}

	int getPositionY()
	{
		return cordY;
	}

	void setArea(int width, int height, int margin)
	{
		this->width = width;
		this->height = height;
		this->margin = margin;
	}
};