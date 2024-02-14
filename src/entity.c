#include "entity.h"
#include "hashtable.h"
#include "vector.h"
#include <stdio.h>

bool entity_init(Entity *entity, Vector2f position, float cur_frame_x,
                 float cur_frame_y, float scale, SDL_Texture *texture) {
  if (entity == NULL) {
    fprintf(stderr, "Could not initialize entity: entity is NULL\n");
    return false;
  }

  entity->x = position.x;
  entity->y = position.y;
  entity->scale = scale;
  entity->current_frame.x = cur_frame_x;
  entity->current_frame.y = cur_frame_y;
  if (SDL_QueryTexture(texture, NULL, NULL, &entity->current_frame.w,
                       &entity->current_frame.h) != 0) {
    fprintf(stderr,
            "Could not query texture during entity initialization: %s\n",
            SDL_GetError());
    return false;
  }

  entity->texture = texture;
  entity->anim_info_ht = hashtable_create();
  entity->curr_anim = NULL;
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
