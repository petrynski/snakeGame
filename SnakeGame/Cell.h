#pragma once
class Cell
{
private:
	int cords[2];

public:
	Cell(int x, int y);
	int getCordX();
	int getCordY();
	void setCords(int x, int y);
	void moveCell(int moveDirection);
};

