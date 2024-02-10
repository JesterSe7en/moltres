#ifndef INCLUDE_SRC_ENTITY_H_
#define INCLUDE_SRC_ENTITY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
  float x, y;
  float scale;
  SDL_Rect current_frame;
  SDL_Texture *texture;
} Entity;

Entity *create_entity(float, float, SDL_Texture *);
Entity *create_scaled_entity(float, float, float, SDL_Texture *);
void destroy_entity(Entity *entity);

#endif // INCLUDE_SRC_ENTITY_H_
