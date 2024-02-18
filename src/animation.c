#include "animation.h"
#include "vector.h"

AnimationInfo *animation_info_create(Vector2i origin, Vector2i offset,
                                     int total_frames, float fps,
                                     float total_time) {
  AnimationInfo *info = malloc(sizeof(AnimationInfo));
  info->origin = origin;
  info->offset = offset;
  info->total_frames = total_frames;
  info->fps = fps;
  info->total_time = total_time;

  info->cur_frame = 0; // default to first frame
  info->frame_duration = 1.0f / fps;
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
