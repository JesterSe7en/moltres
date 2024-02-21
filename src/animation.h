#ifndef MOLTRES_SRC_ANIMATION_H_
#define MOLTRES_SRC_ANIMATION_H_

#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

/**
 * @struct AnimationInfo
 * @brief Stores information about an animation
 */
typedef struct AnimationInfo {
  Vector2I origin;  /**< x,y coordinates of the starting frame */
  Vector2I offset;  /**< x,y offset between each frame */
  Vector2I size;    /**< width, height of each frame */
  int total_frames; /**< total number of frames in the animation */

  // derived values
  int cur_frame;        /**< current frame index of the animation [0, total_frames - 1] */
  float frame_duration; /**< duration of each frame in seconds */
  float elapsed_time;   /**< elapsed time of the animation in seconds */
} AnimationInfo;

typedef struct AnimationInfoProperties {
  Vector2I origin;
  Vector2I offset;
  Vector2I size;
  int total_frames;
  float fps;
  float total_time;
} AnimationInfoProperties;

/**
 * @brief Creates an AnimationInfo structure based on the provided properties
 * @param properties The properties for initializing the AnimationInfo structure
 * @return A pointer to the newly created AnimationInfo structure
 */
AnimationInfo *AnimationInfoCreate(AnimationInfoProperties properties);

void AnimationInfoDestroy(AnimationInfo *animation_info);
#endif // MOLTRES_SRC_ANIMATION_H_
