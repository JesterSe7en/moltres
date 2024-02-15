#include "animation.h"
#include "vector.h"

AnimationInfo *create_animation_info(Vector2i origin, Vector2i offset,
                                     float frame_duration,
                                     SDL_Texture *spritesheet) {
  AnimationInfo *info = malloc(sizeof(AnimationInfo));
  info->origin = origin;
  info->offset = offset;
  info->frame_duration = frame_duration;
  info->spritesheet = spritesheet;
  return info;
}
