#include "entity.h"
#include "vector.h"
#include <stdio.h>

/**
 * Initializes an entity
 *
 * @param position Vector2F the position of the entity
 * @param cur_frame_x the x position of the current frame in the animation
 * @param cur_frame_y the y position of the current frame in the animation
 * #param scale the scale of the entity in window
 * @param SDL_Texture* The SDL texture of the entity
 * @return bool False if entity could not be initialized
 */
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
