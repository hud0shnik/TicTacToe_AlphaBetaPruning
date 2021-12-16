#pragma once

#include <iostream>
#include <string>
using namespace std;

// Порт отображения состояния игры
class ViewPort
{
	// Методы класса
public:
	void WinnerPrint(int mode);
	void PrintGame(char** grid, int x, int y);
	void MenuEndGamase();
};

