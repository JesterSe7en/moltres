#include "animation.h"

AnimationInfo *animation_info_create(AnimationInfoProperties *properties) {
  AnimationInfo *info = malloc(sizeof(AnimationInfo));
  info->origin = properties.origin;
  info->offset = properties.offset;
  info->size = properties.size;
  info->total_frames = properties.total_frames;
  info->fps = properties.fps;
  info->total_time = properties.total_time;

  info->cur_frame = 0; // default to first frame
  info->frame_duration = 1.0f / properties.fps;
  return info;
}

void animation_info_destroy(AnimationInfo *animation_info) {
  if (animation_info == NULL) {
    fprintf(stderr, "Cannot destroy NULL animation_info.\n");
    return;
  }
  free(animation_info);
  animation_info = NULL;
}
