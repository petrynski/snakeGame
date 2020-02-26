#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->cords[0] = x;
	this->cords[1] = y;
}

int Cell::getCordX()
{
	return this->cords[0];
}

int Cell::getCordY()
{
	return this->cords[1];
}

void Cell::setCords(int x, int y)
{
	this->cords[0] = x;
	this->cords[1] = y;
}

void Cell::moveCell(int moveDirection)
{
	switch (moveDirection)
	{
	case 0:
		this->cords[0]++;
		break;

	case 1:
		this->cords[0]--;
		break;

	case 2:
		this->cords[1]++;
		break;

	case 3:
		this->cords[1]--;
		break;

	default:

		break;
	}
}