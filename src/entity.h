#ifndef INCLUDE_SRC_ENTITY_H_
#define INCLUDE_SRC_ENTITY_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

typedef struct {
  float x, y;
  float scale;
  SDL_Rect current_frame;
  SDL_Texture *texture;
} Entity;

bool init_entity(Entity *entity, float x, float y, float target_x,
                 float target_y, float scale, SDL_Texture *texture);
void cleanup_entity(Entity *);

#endif // INCLUDE_SRC_ENTITY_H_
