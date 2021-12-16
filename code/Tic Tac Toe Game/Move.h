#pragma once

#include <vector>
#include <algorithm>
#include <random>
using namespace std;

struct Vector2 {
	int x,
		y;

	Vector2(int _x, int _y) :x(_x), y(_y) {}
	Vector2() : x(0), y(0) {}
	Vector2(const Vector2& p) : x(p.x), y(p.y) {}
	friend bool operator== (const Vector2& p1, const Vector2& p2);
};

class Move {
public:
	Move(Vector2 _p);
	Move();

	Vector2 p;			// координата
	float estimation;	// оценка хода

	int CompareTo(Move other);
};