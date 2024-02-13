#include "player.h"
#include "animation.h"
#include "hashtable.h"
#include <stdio.h>

Player player_create(Vector2f *spawn_point) {
  Player player;
  player.spawn_point = *spawn_point;

  player.animations = hashtable_create();

  player.current_animation = NULL;

  printf("Size of player in bytes: %lu bytes\n", sizeof(Player));

  return player;
}
