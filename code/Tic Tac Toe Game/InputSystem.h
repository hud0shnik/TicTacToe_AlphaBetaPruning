#pragma once

#include <iostream>

#include <string>

using namespace std;
 
class InputSystem { 
  public:
    void InputPosition(int & x, int & y);
  void Settings(int & x_gridSize, int & y_gridSize, int & countToWin);
  void InputAction(int & act);
};