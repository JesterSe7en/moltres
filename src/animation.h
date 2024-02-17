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
  Vector2i origin;      /**< x,y coordinates of the starting frame */
  Vector2i offset;      /**< x,y offset between each frame */
  float frame_duration; /**< duration of each frame in seconds */
  int max_frame;        /**< maximum number of frames in the animation */
} AnimationInfo;

AnimationInfo *create_animation_info(Vector2i origin, Vector2i offset,
                                     float frame_duration, int max_frame);
void destroy_animation_info(AnimationInfo *animation_info);
#endif // INCLUDE_SRC_ANIMATION_H_
