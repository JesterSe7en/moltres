#include "entity.h"

/**
 * Creates a new entity. Defaults current frame to 0,0 with scale of 1.
 *
 * @param x the x position of the entity in window
 * @param y the y position of the entity in window
 * @param SDL_Texture* The SDL texture of the entity
 * @return Entity* New entity
 */
Entity *create_entity(float x, float y, SDL_Texture *texture) {
  Entity *entity = (Entity *)malloc(sizeof(Entity));
  // location on screen is the entity
  entity->x = x;
  entity->y = y;

  entity->scale = 1;

  // this is the size of the source texture
  entity->current_frame.x = 0;
  entity->current_frame.y = 0;
  if (SDL_QueryTexture(texture, NULL, NULL, &entity->current_frame.w,
                       &entity->current_frame.h) != 0) {
    fprintf(stderr, "Could not query texture during entity creation: %s\n",
            SDL_GetError());
    free(entity);
    return NULL;
  }

  entity->texture = texture;
  return entity;
}

/**
 * Creates a new entity. Defaults current frame to 0,0.
 *
 * @param x the x position of the entity in window
 * @param y the y position of the entity in window
 * #param scale the scale of the entity in window
 * @param SDL_Texture* The SDL texture of the entity
 * @return Entity* New entity
 */
Entity *create_scaled_entity(float x, float y, float scale,
                             SDL_Texture *texture) {
  Entity *entity = (Entity *)malloc(sizeof(Entity));
  // location on screen is the entity
  entity->x = x;
  entity->y = y;

  entity->scale = scale;

  // this is the size of the source texture
  entity->current_frame.x = 0;
  entity->current_frame.y = 0;
  if (SDL_QueryTexture(texture, NULL, NULL, &entity->current_frame.w,
                       &entity->current_frame.h) != 0) {
    fprintf(stderr, "Could not query texture during entity creation: %s\n",
            SDL_GetError());
    free(entity);
    return NULL;
  }

  entity->texture = texture;
  return entity;
}

void destroy_entity(Entity *entity) {
  if (entity->texture != NULL) {
    SDL_DestroyTexture(entity->texture);
  }
  free(entity);
}
