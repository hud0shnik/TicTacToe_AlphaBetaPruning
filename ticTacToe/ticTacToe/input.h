#include "input.h"

void InputSystem::InputPosition(int& x, int& y) {
	cout << "Ваш ход (x, y): ";
	cin >> x >> y;

	// Так как ввод от 1
	x--;
	y--;

	system("cls");
}

void InputSystem::Settings(int& x_gridSize, int& y_gridSize, int countToWin) {
	cout << "Введите размер игрового поля (x, y): ";
	cin >> x_gridSize >> y_gridSize;
	cout << "Введите размер для победы: ";
	cin >> countToWin;

	system("cls");
}

void InputSystem::InputAction(int& act) {
	cout << "Ваш выбор: ";
	cin >> act;
	system("cls");
}
