#ifndef MOLTRES_SRC_ENTITY_H_
#define MOLTRES_SRC_ENTITY_H_

#include "animation.h"
#include "hashtable.h"
#include "vector.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include <stdbool.h>

/**
 * @struct Entity
 * @brief Represents an entity in the game world.
 */
typedef struct Entity {
  Vector2F position;       /**< Initial position of the entity in 2D space */
  float scale;             /**< Scaling factor applied to the entity */
  SDL_Rect current_frame;  /**< Current frame of the entity */
  SDL_Texture *texture;    /**< SDL texture representing the entity */
  char *curr_anim;         /**< Name of the current animation */
  HashTable *anim_info_ht; /**< Hash table storing animation info */
  SDL_Color color;         /**< Color of the entity */
  const char *text;        /**< Text associated with the entity */
} Entity;

/**
 * @brief Create a new entity.
 * @param position Initial position of the entity in 2D space.
 * @param screen_origin The origin position of the entity in screen space.
 * @param width Width of the entity.
 * @param height Height of the entity.
 * @param scale Scaling factor applied to the entity.
 * @param texture SDL_Texture representing the texture applied to the entity.
 * @return Pointer to the newly created entity.
 */
Entity *EntityCreate(Vector2F position, Vector2I screen_origin, int width, int height, float scale,
                     SDL_Texture *texture);

/**
 * @brief Add an animation to an entity.
 * @param entity Pointer to the entity to which the animation will be added.
 * @param anim_name Name of the animation for reference and retrieval.
 * @param spritesheet SDL_Texture representing the spritesheet containing the
 * animation frames.
 * @param props AnimationInfoProperties struct containing the properties of the
 * new animation.
 */
void EntityAddAnimation(Entity *entity, char *anim_name, SDL_Texture *spritesheet, AnimationInfoProperties *props);

/**
 * @brief Clean up an entity, freeing associated memory.
 * @param entity Pointer to the entity to be cleaned up.
 */
void CleanupEntity(Entity *entity);

#endif // MOLTRES_SRC_ENTITY_H_
