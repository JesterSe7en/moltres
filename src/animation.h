#ifndef INCLUDE_SRC_ANIMATION_H_
#define INCLUDE_SRC_ANIMATION_H_

#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
  Vector2i origin;
  int offset;
} AnimationInfo;

AnimationInfo ani_info(Vector2i *, int);

#endif // INCLUDE_SRC_ANIMATION_H_
