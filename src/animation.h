#ifndef INCLUDE_SRC_ANIMATION_H_
#define INCLUDE_SRC_ANIMATION_H_

#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @struct AnimationInfo
 * @brief Stores information about an animation
 */
typedef struct AnimationInfo {
  Vector2i origin;          /**< x,y coordinates of the starting frame */
  Vector2i offset;          /**< x,y offset between each frame */
  SDL_Texture *spritesheet; /**< spritesheet of the animation */
} AnimationInfo;

#endif // INCLUDE_SRC_ANIMATION_H_
