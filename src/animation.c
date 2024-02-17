#include "animation.h"
#include "vector.h"

AnimationInfo *create_animation_info(Vector2i origin, Vector2i offset,
                                     float frame_duration, int total_frames) {
  AnimationInfo *info = malloc(sizeof(AnimationInfo));
  info->origin = origin;
  info->offset = offset;
  info->frame_duration = frame_duration;
  info->total_frames = total_frames;
  info->cur_frame = 0;
  return info;
}

AnimationInfo *animation_info_create(Vector2i origin, Vector2i offset,
                                     int total_frames, float fps,
                                     float total_time) {
  return NULL;
}

void destroy_animation_info(AnimationInfo *animation_info) {
  if (animation_info == NULL) {
    fprintf(stderr, "Cannot destroy NULL animation_info.\n");
    return;
  }
  free(animation_info);
  animation_info = NULL;
}
