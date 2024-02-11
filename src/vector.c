#include "vector.h"

Vector2F v2f(float x, float y) {
  Vector2F v = {x, y};
  return v;
}

// another way to return back a vector via compound literal
Vector2i v2i(int x, int y) { return (Vector2i){.x = x, .y = y}; }
