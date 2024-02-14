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

/**
 * Initializes an entity
 *
 * @param position Vector2F the position of the entity
 * @param cur_frame_x the x position of the current frame in the animation
 * @param cur_frame_y the y position of the current frame in the animation
 * @param scale the scale of the entity in window
 * @param SDL_Texture* The SDL texture of the entity
 * @return bool False if entity could not be initialized properly
 */
bool entity_init(Entity *entity, Vector2f position, float cur_frame_x,
                 float cur_frame_y, float scale, SDL_Texture *texture);
void cleanup_entity(Entity *);

#endif // INCLUDE_SRC_ENTITY_H_
