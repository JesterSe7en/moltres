#ifndef INCLUDE_SRC_PLAYER_H_
#define INCLUDE_SRC_PLAYER_H_

#include "animation.h"
#include "hashtable.h"
#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct Player {
  Vector2f spawn_point;
  AnimationInfo *current_animation;
  HashTable *animations;
} Player;

Player player_create(Vector2f *);
void player_addAnimation(Player *, const char *, AnimationInfo *);

#endif // INCLUDE_SRC_PLAYER_H_
