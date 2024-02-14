#ifndef INCLUDE_SRC_VECTOR_H_
#define INCLUDE_SRC_VECTOR_H_

typedef struct Vector2f {
  float x, y;
} Vector2f;

typedef struct Vector2i {
  int x, y;
} Vector2i;

// for convenience
static inline Vector2f v2f(float x, float y) {
  Vector2f v = {x, y};
  return v;
}

static inline Vector2i v2i(int x, int y) {
  Vector2i v = {x, y};
  return v;
}

#endif // INCLUDE_SRC_VECTOR_H_
