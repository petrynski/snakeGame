#pragma once
#include"Snake.h"
class Fruit
{
private:
	int cordX, cordY;
public:
	Fruit()
	{
		cordX = (rand()%51)+3;
		cordY = (rand()%21)+3;
	}

	void setNewPosition()
	{
		cordX = (rand() % 50) + 4;
		cordY = (rand() % 20) + 4;
	}

	int getPositionX()
	{
		return cordX;
	}

	int getPositionY()
	{
		return cordY;
	}
};

