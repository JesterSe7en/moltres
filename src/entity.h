#ifndef INCLUDE_SRC_ENTITY_H_
#define INCLUDE_SRC_ENTITY_H_

#include "animation.h"
#include "hashtable.h"
#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef struct Entity {
  Vector2f position;
  float scale;
  SDL_Rect current_frame;
  SDL_Texture *texture; //**< Can be spriteshit or just an singular texture */
  char *curr_anim;      /**< set this to NULL if there is no animation */
  HashTable *anim_info_ht; /**< Stores animation info structs */

  SDL_Color color;
  const char *text;
} Entity;

/* typedef struct EntityProperties { */
/* } EntityProperties; // follow in line with Vulkan */

/**
 * @brief Create a new entity.
 *
 * This function creates a new entity with the specified parameters and returns
 * a pointer to the created entity.
 *
 * @param position Initial position of the entity in 2D space.
 * @param screen_origin The origin position of the entity in screen space.
 * @param width Width of the entity.
 * @param height Height of the entity.
 * @param scale Scaling factor applied to the entity.
 * @param texture SDL_Texture representing the texture applied to the entity.
 *
 * @return Pointer to the newly created entity.
 */
Entity *entity_create(Vector2f position, Vector2i screen_origin, int width,
                      int height, float scale, SDL_Texture *texture);

/**
 * @brief Add an animation to an entity.
 *
 * This function adds an animation to the specified entity using the provided
 * parameters.
 *
 * @param entity Pointer to the entity to which the animation will be added.
 * @param origin The origin position of the animation frame in the spritesheet.
 * @param offset The offset between consecutive frames in the spritesheet.
 * @param total_frames The total number of frames in the animation.
 * @param fps Frames per second, specifying the animation speed.
 * @param total_time Total time for the animation to complete
 * @param anim_name Name of the animation for reference and retrieval.
 * @param spritesheet SDL_Texture representing the spritesheet containing
 * animation frames.
 */
void entity_add_animation(Entity *entity, Vector2i origin, Vector2i offset,
                          int total_frames, float fps, float total_time,
                          char *anim_name, SDL_Texture *spritesheet);

void cleanup_entity(Entity *);

#endif // INCLUDE_SRC_ENTITY_H_
