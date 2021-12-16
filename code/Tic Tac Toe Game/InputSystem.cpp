#include "InputSystem.h"

void InputSystem::InputPosition(int & x, int & y) {
  cout << "������� ������� ���� (x, y): ";
  cin >> x >> y;

  x--;
  y--;

  system("cls");
}

void InputSystem::Settings(int & x_gridSize, int & y_gridSize, int & countToWin) {
  cout << "������� ������ �������� ���� (x, y): ";
  cin >> x_gridSize >> y_gridSize;
  cout << "������� ������ ��� ������: ";
  cin >> countToWin;

  system("cls");
}

void InputSystem::InputAction(int & act) {
  cout << "��� �����: ";
  cin >> act;
  system("cls");
}