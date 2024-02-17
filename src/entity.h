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
  float x, y;
  float scale;
  SDL_Rect current_frame;
  SDL_Texture *texture;
  char *curr_anim;         /**< set this to NULL if there is no animation */
  HashTable *anim_info_ht; /**< Stores animation info structs */

  SDL_Color color;
  const char *text;
} Entity;

typedef struct EntityProperties {
  float x;
} EntityProperties; // follow in line with Vulkan

/**
 * Initializes a static entity - aka no animations
 *
 * @param position Vector2F the position of the entity
 * @param origin Vector2F the top left corner to source texture
 * @param width the width in pixels to source from texture
 * @param height the height in pixels to source from texture
 * @param scale the scale of the entity in window
 * @param texutre The SDL texture of the entity
 * @return bool False if entity could not be initialized properly
 */
/* bool entity_init_static(Entity *entity, Vector2f position, Vector2i origin,
 */
/*                         int width, int height, float scale, */
/*                         SDL_Texture *texture); */
/* // FIXME: maybe put all of this parameters in a struct? getting unwieldy */

/**
 * Initializes a dynamic entity - aka has animation(s).  Must initialize with at
 * least one animation
 *
 * @param position Vector2F the position of the entity
 * @param origin Vector2i the top left corner to source texture
 * @param width the width in pixels to source from texture
 * @param height the height in pixels to source from texture
 * @param offset the x,y offset of the animation
 * @param scale the scale of the entity in window
 * @param anim_name the name of the animation
 * @param texture The SDL texture of the animation
 * @return bool False if entity could not be initialized properly
 */
/* bool entity_init_dynamic(Entity *entity, Vector2f position, Vector2i origin,
 */
/*                          int width, int height, Vector2i offset, */
/*                          float frame_duration, float scale, char *anim_name,
 */
/*                          SDL_Texture *spritesheet); */
/**
 * Creates a static entity - heap allocated
 *
 * @param position Vector2F the position of the entity
 * @param origin Vector2i the top left corner to source texture
 * @param width the width in pixels to source from texture
 * @param height the height in pixels to source from texture
 * @param scale the scale of the entity in window
 * @param texture The SDL texture of the entity
 */
Entity *entity_create_static(Vector2f position, Vector2i origin, int width,
                             int height, float scale, SDL_Texture *texture);

/**
 * Creates a dynamic entity - heap allocated
 *
 * @param position Vector2F the position of the entity
 * @param origin Vector2i the top left corner to source texture
 * @param width the width in pixels to source from texture
 * @param height the height in pixels to source from texture
 * @param offset the x,y offset of the animation
 * @param frame_duration the duration of each frame
 * @param scale the scale of the entity in window
 * @param anim_name the name of the animation
 * @param max_frames the total number of frames for an animation
 * @param texture The SDL texture of the animation
 */
Entity *entity_create_dynamic(Vector2f position, Vector2i origin, int width,
                              int height, Vector2i offset, float frame_duration,
                              float scale, char *anim_name, int max_frames,
                              SDL_Texture *spritesheet);

/**
 * Adds an animation to an entity
 *
 * @param entity The entity to add the animation to
 * @param origin Vector2I the top left corner to source texture
 * @param offset Vector2I the x,y offset of the animation
 * @param frame_duration The duration of each frame
 * @param anim_name The name of the animation
 * @param spritesheet The SDL texture of the animation
 */
void entity_add_animation(Entity *entity, Vector2i origin, Vector2i offset,
                          float frame_duration, char *anim_name,
                          SDL_Texture *spritesheet);

void cleanup_entity(Entity *);

#endif // INCLUDE_SRC_ENTITY_H_
