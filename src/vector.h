#ifndef INCLUDE_SRC_VECTOR_H_
#define INCLUDE_SRC_VECTOR_H_

typedef struct Vector2F {
  float x, y;
} Vector2F;

typedef struct Vector2i {
  int x, y;
} Vector2i;

Vector2F v2f(float x, float y);
Vector2i v2i(int x, int y);

#endif // INCLUDE_SRC_VECTOR_H_
