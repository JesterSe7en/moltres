#include "entity.h"

Entity *create_entity(float x, float y, SDL_Texture *texture) {
  Entity *entity = (Entity *)malloc(sizeof(Entity));
  entity->x = x;
  entity->y = y;
  entity->current_frame.x = 0;
  entity->current_frame.y = 0;
  entity->current_frame.w = 24;
  entity->current_frame.h = 24;
  entity->texture = texture;
  return entity;
}

void destroy_entity(Entity *entity) {
  if (entity->texture != NULL) {
    SDL_DestroyTexture(entity->texture);
  }
  free(entity);
}
