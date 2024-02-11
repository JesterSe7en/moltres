#ifndef INCLUDE_SRC_ENTITY_H_
#define INCLUDE_SRC_ENTITY_H_

#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

typedef struct {
  Vector2F position;
  float x, y;
  float scale;
  SDL_Rect current_frame;
  SDL_Texture *texture;
} Entity;

bool init_entity(Entity *, Vector2F, float, float, float, SDL_Texture *texture);
void cleanup_entity(Entity *);

#endif // INCLUDE_SRC_ENTITY_H_
