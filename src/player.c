#include "player.h"
#include "animation.h"
#include "hashtable.h"
#include <stdio.h>

Player player_create(Vector2f *spawn_point) {
  Player player;
  player.spawn_point = *spawn_point;

  player.animations = hashtable_create();

  HashTable *ht = player.animations;

  printf("adding animations to hashtable\n");
  hashtable_add(ht, "idle", "heheh im idling...");
  printf("added idle\n");
  printf("adding runinng to hashtable\n");
  hashtable_add(ht, "running", "heheh im running  pee pee poo poo...");
  printf("added running\n");
  printf("adding jumping to hashtable\n");
  hashtable_add(ht, "jumping", "heheh im jumping...");
  printf("adding done\n");

  // search for running key, print out the value
  printf("search for running: message = %s\n",
         (const char *)hashtable_get(ht, "running"));

  player.current_animation = NULL;

  printf("Size of player in bytes: %lu bytes\n", sizeof(Player));

  return player;
}
