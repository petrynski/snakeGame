#pragma once
#include <windows.h>
#include <iostream>
#include <string>

class Drawer
{
public:
	static void drawArena(int width, int height, int margin);
	static void drawSnakeHead(int headX, int headY);
	static void drawSnakeTail(int tailX, int tailY);
	static void drawFruit(int fruitX, int fruitY);
	static void drawSideMenu(int score, int time, int width, int margin);
	static void drawSnakeDead(int X, int Y);
	static void clear(int X, int Y);
	static void drawHighscores(int i, int score, std::string name, int width, int margin);
};

