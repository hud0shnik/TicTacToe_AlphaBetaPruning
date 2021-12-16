#include "ViewPort.h"

void ViewPort::WinnerPrint(int mode)
{
	cout << "Конец игры!" << endl;
	if (mode == 1) {
		cout << "Победил: игрок!" << endl;
	}
	else if(mode == 2) {
		cout << "Победил: компьютер!" << endl;
	}
}

void ViewPort::PrintGame(char** grid, int x, int y)
{
	cout << "    === Игровое поле === " << endl;

	cout << " ";
	for (int i = 0; i < x; i++) {
		cout << " " << i + 1;
	}
	cout << endl;

	for (int i = 0; i < x; i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < y; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}	

	cout << "========================================================================================" << endl;
	cout << "Условные обозначения: _ - пустое место, X - место хода игрока, 0 - место хода компьютера" << endl;
	cout << "========================================================================================" << endl;
}

void ViewPort::MenuEndGamase()
{
	cout << "Выберите действие: " << endl
		<< "(0) Завершить игру" << endl
		<< "(1) Перезапустить игру" << endl;
}
