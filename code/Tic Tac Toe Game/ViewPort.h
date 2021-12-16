#pragma once
#include <iostream>
#include <string>
using namespace std;
 
class ViewPort { 
  public:
    void WinnerPrint(int mode);
  void PrintGame(char ** grid, int x, int y);
  void MenuEndGamase();
};