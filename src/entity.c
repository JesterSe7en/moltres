#include "entity.h"
#include "animation.h"
#include "hashtable.h"
#include "vector.h"
#include <stdio.h>

bool entity_init_static(Entity *entity, Vector2f position, Vector2i origin,
                        int width, int height, float scale,
                        SDL_Texture *texture) {
  if (entity == NULL) {
    fprintf(stderr, "Could not initialize entity: entity is NULL\n");
    return false;
  }

  entity->x = position.x;
  entity->y = position.y;
  entity->scale = scale;
  entity->current_frame.x = origin.x;
  entity->current_frame.y = origin.y;
  entity->current_frame.w = width;
  entity->current_frame.h = height;

  // if we are using the entire loaded texture, we can query it like this
  // if (SDL_QueryTexture(texture, NULL, NULL, &entity->current_frame.w,
  //                      &entity->current_frame.h) != 0) {
  //   fprintf(stderr,
  //           "Could not query texture during entity initialization: %s\n",
  //           SDL_GetError());
  //   return false;
  // }

  entity->texture = texture;
  entity->curr_anim = NULL;
  entity->anim_info_ht = NULL;
  return true;
}

bool entity_init_dynamic(Entity *entity, Vector2f position, Vector2i origin,
                         int width, int height, Vector2i offset, float scale,
                         char *anim_key, SDL_Texture *spritesheet) {
  if (entity == NULL) {
    fprintf(stderr, "Could not initialize entity: entity is NULL\n");
    return false;
  }

  entity->x = position.x;
  entity->y = position.y;
  entity->scale = scale;
  entity->current_frame.x = origin.x;
  entity->current_frame.y = origin.y;
  entity->current_frame.w = width;
  entity->current_frame.h = height;
  entity->texture = NULL;
  entity->curr_anim = anim_key;
  entity->anim_info_ht = hashtable_create();
  AnimationInfo ai = {origin, offset, spritesheet};
  hashtable_add(entity->anim_info_ht, anim_key, &ai);

  return true;
}

void cleanup_entity(Entity *entity) {
  if (entity == NULL) {
    fprintf(stderr, "Could not destroy entity: entity is NULL\n");
    return;
  }

  if (entity->texture != NULL) {
    SDL_DestroyTexture(entity->texture);
  }
}
