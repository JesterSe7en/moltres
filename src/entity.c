#include "entity.h"

/**
 * Initializes an entity
 *
 * @param x the x position of the entity in window
 * @param y the y position of the entity in window
 * @param cur_frame_x the x position of the current frame in the animation
 * @param cur_frame_y the y position of the current frame in the animation
 * #param scale the scale of the entity in window
 * @param SDL_Texture* The SDL texture of the entity
 * @return bool False if entity could not be initialized
 */
bool init_entity(Entity *entity, float x, float y, float cur_frame_x,
                 float cur_frame_y, float scale, SDL_Texture *texture) {
  if (entity == NULL) {
    fprintf(stderr, "Could not initialize entity: entity is NULL\n");
    return false;
  }

  entity->x = x;
  entity->y = y;
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

void destroy_entity(Entity *entity) {
  if (entity == NULL) {
    fprintf(stderr, "Could not destroy entity: entity is NULL\n");
    return;
  }

  printf("Destroying entity at (%f, %f)\n", entity->x, entity->y);

  if (entity->texture != NULL) {
    SDL_DestroyTexture(entity->texture);
  }
  free(entity);
}
