#ifndef MOLTRES_SRC_VECTOR_H_
#define MOLTRES_SRC_VECTOR_H_

typedef struct Vector2f {
  float x, y;
} Vector2F;

typedef struct Vector2i {
  int x, y;
} Vector2I;

// for convenience
static inline Vector2F V2F(float x, float y) {
  Vector2F v = {x, y};
  return v;
}

static inline Vector2I V2I(int x, int y) {
  Vector2I v = {x, y};
  return v;
}

#endif // MOLTRES_SRC_VECTOR_H_
