#ifndef INCLUDE_SRC_ENTITY_H_
#define INCLUDE_SRC_ENTITY_H_

#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

typedef struct Entity {
  Vector2f position;
  float x, y;
  float scale;
  SDL_Rect current_frame;
  SDL_Texture *texture;
} Entity;

bool entity_init(Entity *, Vector2f, float, float, float, SDL_Texture *texture);
void cleanup_entity(Entity *);

#endif // INCLUDE_SRC_ENTITY_H_
