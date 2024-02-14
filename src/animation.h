#ifndef INCLUDE_SRC_ANIMATION_H_
#define INCLUDE_SRC_ANIMATION_H_

#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @struct AnimationInfo
 * @brief Stores information about an animation
 */
typedef struct {
  Vector2i origin; /**< x,y coordinates of the top left corner - first frame */
  Vector2i offset; /**< x,y offset coordinates for the next frames */
  SDL_Texture *spritsheet; /**< The spritesheet to find these frames */
} AnimationInfo;

AnimationInfo ani_info(Vector2i *, Vector2i *, SDL_Texture *);

#endif // INCLUDE_SRC_ANIMATION_H_
