#include "ViewPort.h"

void ViewPort::WinnerPrint(int mode) {
  cout << "Game over" << endl;
  if (mode == 1) {
    cout << "You win!!!" << endl;
  } else if (mode == 2) {
    cout << "You lose..." << endl;
  }
}

void ViewPort::PrintGame(char ** grid, int x, int y) {
  cout << "    === TicTacToe === " << endl;

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

  cout << "===================================" << endl;
  cout << "_ - empty cell, X - Player, 0 - Bot" << endl;
  cout << "===================================" << endl;
}

void ViewPort::MenuEndGamase() {
  cout << "Chose: " << endl <<
    "(0) Exit" << endl <<
    "(1) One more time" << endl;
}