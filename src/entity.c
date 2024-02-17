#include "entity.h"
#include "animation.h"
#include "hashtable.h"
#include "vector.h"
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

//  TODO: Can do Entity entity = *entity_create_dynamic(...) to accomplish the
// same thing...maybe
//
Entity *entity_create(Vector2f position, Vector2i origin, int width, int height,
                      float scale, SDL_Texture *texture) {
  Entity *entity = malloc(sizeof(Entity));
  entity->position = position;
  entity->scale = scale;
  entity->current_frame.x = origin.x;
  entity->current_frame.y = origin.y;
  entity->current_frame.w = width;
  entity->current_frame.h = height;
  entity->texture = texture;
  entity->curr_anim = NULL;
  entity->anim_info_ht = NULL;
  return entity;
}

void entity_add_animation(Entity *entity, Vector2i origin, Vector2i offset,
                          int total_frames, float fps, float total_time,
                          char *anim_name, SDL_Texture *spritesheet) {
  if (entity->anim_info_ht == NULL) {
    entity->anim_info_ht = hashtable_create();
  }

  AnimationInfo *ai =
      animation_info_create(origin, offset, total_frames, fps, total_time);
  hashtable_add(&entity->anim_info_ht, anim_name, ai);
}

void cleanup_entity(Entity *entity) {
  if (entity == NULL) {
    fprintf(stderr, "Could not destroy entity: entity is NULL\n");
    return;
  }

  if (entity->texture != NULL) {
    SDL_DestroyTexture(entity->texture);
  }

  // destroy all animation infos
  HashTable *ht = entity->anim_info_ht;
  if (ht != NULL && ht->size > 0) {
    HashTableIterator it = hashtable_iterator_create(ht);
    while (hashtable_iterator_has_next(&it)) {
      Entry *entry = hashtable_iterator_next(&it);
      AnimationInfo *ai = (AnimationInfo *)entry->value;
      if (ai != NULL) {
        animation_info_destroy(ai);
      }
    }
  }

  // destroy the animation info hashtable itself
  if (entity->anim_info_ht != NULL) {
    hashtable_destroy(entity->anim_info_ht);
  }

  free(entity);
  entity = NULL;
}
