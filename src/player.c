#include "player.h"
#include "animation.h"
#include <stdio.h>

Player player_create(Vector2f *spawn_point) {
  Player player;
  player.spawn_point = *spawn_point;

  // initialize animations array of 3 for now
  player.animations = (AnimationInfo *)malloc(3 * sizeof(AnimationInfo));

  // point to the first one
  player.current_animation = &player.animations[0];

  printf("Size of player in bytes: %lu bytes\n", sizeof(Player));

  return player;
}
