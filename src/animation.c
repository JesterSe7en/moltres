#include "animation.h"
#include "vector.h"

AnimationInfo *create_animation_info(Vector2i origin, Vector2i offset,
                                     float frame_duration, int max_frame) {
  AnimationInfo *info = malloc(sizeof(AnimationInfo));
  info->origin = origin;
  info->offset = offset;
  info->frame_duration = frame_duration;
  info->max_frame = max_frame;
  info->current_frame = 0;
  return info;
}

void destroy_animation_info(AnimationInfo *animation_info) {
  if (animation_info == NULL) {
    fprintf(stderr, "Cannot destroy NULL animation_info.\n");
    return;
  }
  free(animation_info);
  animation_info = NULL;
}
