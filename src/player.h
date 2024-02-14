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

/**
 * Creates a new player with the given spawn point.
 *
 * @param spawn_point The spawn point of the player.
 */
Player player_create(Vector2f spawn_point);

/**
 * Adds an animation to the player.
 *
 * @param player The player.
 * @param name The name of the animation.
 * @param
 */
void player_addAnimation(Player *player, const char *animation_name,
                         AnimationInfo *animation_info);

#endif // INCLUDE_SRC_PLAYER_H_
