#include "Move.h"

Move::Move(Vector2 _p) {
  p.x = _p.x;
  p.y = _p.y;

  estimation = 0;
}

Move::Move() {
  p.x = -1;
  p.y = -1;

  estimation = 0;
}

int Move::CompareTo(Move other) {
  auto res = CompareTo(other);
  if (res == 0 && p.x == 1 && p.y == 1) return 1; 
  return res;
}

bool operator == (const Vector2 & p1,
  const Vector2 & p2) {
  if (p1.x != p2.x || p1.y != p2.y)
    return false;
  return true;
}