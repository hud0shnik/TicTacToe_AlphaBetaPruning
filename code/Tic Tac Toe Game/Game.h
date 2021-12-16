#pragma once

#include "InputSystem.h"

#include "ViewPort.h"

#include "AI.h"

enum class Queue {
  player,
  AI
};

enum class GameState {
  inGame,
  start,
  end,
  playerWon,
  AIWom,
  exit
};

// ����
class Game {
  // ���� ������
  private:
    Vector2 gridSize;
  char ** gameGrid;
  int countToWin;
  Queue queue;
  GameState state;

  char AIMarker;
  AI ai;

  char playerMarker;
  Vector2 movePos;

  InputSystem input;
  ViewPort view;

  bool fisrtLounch;

  // ������ ������
  void NewGame();
  void GameEnd();
  void InitGameGrid(Vector2 size);
  void DefineQueue();
  void ClearGameGrid();
  bool CkeckList(vector < char > list);
  void CheckingGame();
  void NextStep();
  bool MakeMove(Vector2 pos, char marker);
  bool IsCellEmpty(Vector2 pos);
  void AI_SelectPosition();

  public:
    Game();
  ~Game();

  void Logic();
};