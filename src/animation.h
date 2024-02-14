#ifndef INCLUDE_SRC_ANIMATION_H_
#define INCLUDE_SRC_ANIMATION_H_

#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @struct AnimationInfo
 * @brief Stores information about an animation
 */
typedef struct AnimationInfo AnimationInfo;

/**
 * @brief Create AnimationInfo struct
 * @param origin Initial coordinates of the top left corner
 * @param offset Offset coordinates for the next frames
 * @param spritesheet The spritesheet to find these frames
 * @return Pointer to the created AnimationInfo struct
 */
AnimationInfo *anim_info_create(Vector2i origin, Vector2i offset,
                                SDL_Texture *spritesheet);

#endif // INCLUDE_SRC_ANIMATION_H_
