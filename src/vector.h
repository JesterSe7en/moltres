#ifndef INCLUDE_SRC_VECTOR_H_
#define INCLUDE_SRC_VECTOR_H_

typedef struct {
  float x, y;
} Vector2f;

typedef struct {
  int x, y;
} Vector2i;

Vector2f v2f(float x, float y);
Vector2i v2i(int x, int y);

#endif // INCLUDE_SRC_VECTOR_H_
