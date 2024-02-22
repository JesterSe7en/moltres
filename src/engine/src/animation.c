#include "animation.h"

AnimationInfo *AnimationInfoCreate(AnimationInfoProperties properties) {
  AnimationInfo *info = malloc(sizeof(AnimationInfo));
  info->origin = properties.origin;
  info->offset = properties.offset;
  info->size = properties.size;
  info->total_frames = properties.total_frames;

  info->cur_frame = 0; // default to first frame
  info->frame_duration = 1.0f / properties.fps;
  return info;
}

void AnimationInfoDestroy(AnimationInfo *animation_info) {
  if (animation_info == NULL) {
    (void) fprintf(stderr, "Cannot destroy NULL animation_info.\n");
    return;
  }
  free(animation_info);
}
