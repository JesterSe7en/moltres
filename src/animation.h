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
  int total_frames;     /**< total number of frames in the animation */
  float fps;            /**< frame rate of the animation */
  float total_time;     /**< total time of the animation in seconds */
  int cur_frame; /**< current frame of the animation [0, total_frames - 1] */

} AnimationInfo;

AnimationInfo *animation_info_create(Vector2i origin, Vector2i offset,
                                     int total_frames, float fps,
                                     float total_time);

AnimationInfo *create_animation_info(Vector2i origin, Vector2i offset,
                                     float frame_duration, int total_frames);

void destroy_animation_info(AnimationInfo *animation_info);
#endif // INCLUDE_SRC_ANIMATION_H_
