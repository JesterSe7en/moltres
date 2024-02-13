#ifndef INCLUDE_SRC_PLAYER_H_
#define INCLUDE_SRC_PLAYER_H_

#include "animation.h"
#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
  Vector2f spawn_point;
  AnimationInfo *current_animation;
  AnimationInfo *animations;
} Player;

Player player_create(Vector2f *);

#endif // INCLUDE_SRC_PLAYER_H_