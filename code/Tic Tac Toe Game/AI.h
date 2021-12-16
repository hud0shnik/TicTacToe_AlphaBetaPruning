#pragma once
#include "Move.h"

// ����� ��� ��
class AI {
  // ���� ������
  private:
    char ** map;
  Vector2 size;

  // ������ ������
  Vector2 GetMove();
  bool IsEmptyCell(Vector2 p);
  Vector2 GetEmptyCell();
  vector < Vector2 > GetEmptyCells();
  void Init(char ** _map, Vector2 size);
  Move SimulationMove(Vector2 p);
  bool CheckWinner();
  bool CkeckList(vector < char > list);

  public:
    AI();
  ~AI();

  Vector2 GetBestMove(char ** _map, Vector2 _size);
};