#include "AI.h"

Vector2 AI::GetMove() { 
  vector < Move > moves;
  vector < Vector2 > points;
  points = GetEmptyCells();
   
  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(points), std::end(points), rng);
  std::random_shuffle(points.begin(), points.end());
   
  for (Vector2 p: points) {
    moves.push_back(SimulationMove(p));
  }
   
  bool found = false;
  Move move;
  for (int i = 0; i < moves.size(); i++) {
    if (moves[i].estimation > 0) {
      move = moves[i];
      found = true;
      break;
    }
  }
   
  if (found) {
    return move.p;
  } else { 
    if (points.size() != 0)
      return GetEmptyCell();
    return Vector2(-1, -1);
  }
}

bool AI::IsEmptyCell(Vector2 p) {
  if (map[p.x][p.y] != '_')
    return false;

  return true;
}

Vector2 AI::GetEmptyCell() {
  for (int i = 0; i < size.x; i++)
    for (int j = 0; j < size.y; j++)
      if (map[i][j] == '_')
        return Vector2(i, j);

  return Vector2(-1, -1);
}

vector < Vector2 > AI::GetEmptyCells() {
  vector < Vector2 > points;
  Vector2 point;

  for (int i = 0; i < size.x; i++)
    for (int j = 0; j < size.y; j++)
      if (map[i][j] == '_') {
        point.x = i;
        point.y = j;
        points.push_back(point);
      }

  return points;
}

void AI::Init(char ** _map, Vector2 _size) {
  size.x = _size.x;
  size.y = _size.y;

  map = new char * [size.x];
  for (int i = 0; i < size.x; i++)
    map[i] = new char[size.y];

  for (int i = 0; i < size.x; i++)
    for (int j = 0; j < size.y; j++)
      map[i][j] = _map[i][j];
}

Move AI::SimulationMove(Vector2 p) { 
  map[p.x][p.y] = '0';
  Move m(p);
   
  if (CheckWinner())
    m.estimation = 1;
  else  
    m.estimation = 0;
   
  map[p.x][p.y] = '_';

  return m;
}

bool AI::CheckWinner() {
  vector < char > list;
  int stateIA = 0;
  int statePL = 0;
   
  for (int i = 0; i < size.x; i++) {
    for (int j = 0; j < size.y; j++) {
      list.push_back(map[i][j]);
    }
     
    if (CkeckList(list)) {
      stateIA++;
    } else {
      statePL++;
    }

    list.clear();
  }
   
  for (int i = 0; i < size.x; i++) {
    for (int j = 0; j < size.y; j++) {
      list.push_back(map[j][i]);
    }

    if (CkeckList(list)) {
      stateIA++;
    } else {
      statePL++;
    }

    list.clear();
  }
   
  for (int i = 0; i < size.x; ++i) {
    for (int j = 0; i + j < size.y; ++j) {
      list.push_back(map[i + j][j]);
    }

    if (CkeckList(list)) {
      stateIA++;
    } else {
      statePL++;
    }

    list.clear();
  }
   
  for (int i = 1; i < size.x; ++i) {
    for (int j = 0; i + j < size.y; ++j) {
      list.push_back(map[i + j][j]);
    }

    if (CkeckList(list)) {
      stateIA++;
    } else {
      statePL++;
    }

    list.clear();
  }
   
  for (int j = size.y; j > 0; --j) {
    for (int i = 0; i < size.x; ++i) {
      if (size.x - j - i >= 0) {
        list.push_back(map[i][size.x - j - i]);
      }
    }

    if (CkeckList(list)) {
      stateIA++;
    } else {
      statePL++;
    }

    list.clear();
  }
   
  for (int j = 0; j < size.y; ++j) {
    for (int i = 0; i < size.x; ++i) {
      if (size.x + j - i < size.x) {
        if (size.x - j - i >= 0) {
          list.push_back(map[i][size.x + j - i]);
        }
      }
    }

    if (CkeckList(list)) {
      stateIA++;
    } else {
      statePL++;
    }

    list.clear();
  }
   
  if (stateIA > statePL)
    return true;
  else
    return false;
}

bool AI::CkeckList(vector < char > list) { 

  int countPl = 0;
  int countAI = 0;

  if (list.size() == 0)
    return false;

  for (int i = 0; i < list.size(); i++) {
    if (list[i] == 'X') {
      countPl++;

      if (i < list.size() - 1) {
        if (list[i + 1] != 'X') {
          countPl = 0;
        } else {
          if (i == list.size() - 1) {
            countPl++;
          }
        }
      }
    }

    if (list[i] == '0') {
      countAI++;

      if (i < list.size() - 1) {
        if (list[i + 1] != '0') {
          countAI = 0;
        } else {
          if (i == list.size() - 1) {
            countAI++;
          }
        }
      }
    }
  }

  return countAI >= countPl;
}

AI::AI() {
  map = new char * [0];
  size.x = 0;
  size.y = 0;
}

AI::~AI() {
  for (int i = 0; i < size.x; i++)
    delete[] map[i];

  delete[] map;
}

Vector2 AI::GetBestMove(char ** _map, Vector2 _size) {
  Init(_map, _size);
   
  if (GetEmptyCells().size() == 0) {
    return Vector2(-1, -1);  
  }
   
  return GetMove();
}