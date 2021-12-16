#include "ViewPort.h"

void ViewPort::WinnerPrint(int mode) {
  cout << "����� ����!" << endl;
  if (mode == 1) {
    cout << "�������: �����!" << endl;
  } else if (mode == 2) {
    cout << "�������: ���������!" << endl;
  }
}

void ViewPort::PrintGame(char ** grid, int x, int y) {
  cout << "    === ������� ���� === " << endl;

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
  cout << "�������� �����������: _ - ������ �����, X - ����� ���� ������, 0 - ����� ���� ����������" << endl;
  cout << "========================================================================================" << endl;
}

void ViewPort::MenuEndGamase() {
  cout << "�������� ��������: " << endl <<
    "(0) ��������� ����" << endl <<
    "(1) ������������� ����" << endl;
}