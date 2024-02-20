#include "entity.h"
#include "animation.h"
#include "hashtable.h"
#include "vector.h"
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

//  TODO: Can do Entity entity = *entity_create_dynamic(...) to accomplish the
// same thing...maybe
//
Entity *EntityCreate(Vector2F position, Vector2I screen_origin, int width,
                     int height, float scale, SDL_Texture *texture) {
  Entity *entity = malloc(sizeof(Entity));
  entity->position = position;
  entity->scale = scale;
  entity->current_frame.x = screen_origin.x;
  entity->current_frame.y = screen_origin.y;
  entity->current_frame.w = width;
  entity->current_frame.h = height;
  entity->texture = texture;
  entity->curr_anim = NULL;
  entity->anim_info_ht = NULL;
  return entity;
}

void EntityAddAnimation(Entity *entity, char *anim_name,
                        SDL_Texture *spritesheet,
                        AnimationInfoProperties *props) {
  if (entity->anim_info_ht == NULL) {
    entity->anim_info_ht = HashtableCreate();
  }

  AnimationInfo *ai = AnimationInfoCreate(*props);
  HashtableAdd(&entity->anim_info_ht, anim_name, ai);
  entity->curr_anim = anim_name;
  entity->texture = spritesheet;
}

void CleanupEntity(Entity *entity) {
  if (entity == NULL) {
    fprintf(stderr, "Could not destroy entity: entity is NULL\n");
    return;
  }

  if (entity->texture != NULL) {
    SDL_DestroyTexture(entity->texture);
  }

  // destroy all animation info
  HashTable *ht = entity->anim_info_ht;
  if (ht != NULL && ht->size > 0) {
    HashTableIterator it = HashtableIteratorCreate(ht);
    while (HashtableIteratorHasNext(&it)) {
      Entry *entry = HashtableIteratorNext(&it);
      AnimationInfo *ai = (AnimationInfo *)entry->value;
      if (ai != NULL) {
        AnimationInfoDestroy(ai);
        ai = NULL;
      }
    }
  }

  // destroy the animation info hashtable itself
  if (entity->anim_info_ht != NULL) {
    HashtableDestroy(entity->anim_info_ht);
  }

  free(entity);
}
