#include "InputSystem.h"

void InputSystem::InputPosition(int & x, int & y) {
  cout << "Your turn (x, y): ";
  cin >> x >> y;

  x--;
  y--;

  system("cls");
}

void InputSystem::Settings(int & x_gridSize, int & y_gridSize, int & countToWin) {
  cout << "Game size (x, y): ";
  cin >> x_gridSize >> y_gridSize;
  cout << "Win size: ";
  cin >> countToWin;

  system("cls");
}

void InputSystem::InputAction(int & act) {
  cout << "Your choise: ";
  cin >> act;
  system("cls");
}