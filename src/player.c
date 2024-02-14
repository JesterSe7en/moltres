#include "player.h"
#include "animation.h"
#include "hashtable.h"
#include <stdio.h>

Player player_create(Vector2f spawn_point) {
  Player player;

  player.spawn_point = spawn_point;
  player.animations = hashtable_create();
  player.current_animation = NULL;

  return player;
}

void player_addAnimation(Player *player, const char *key,
                         AnimationInfo *ani_info) {
  // TODO: implement add animation
  printf("Adding animation to player\n");

  return;
}
