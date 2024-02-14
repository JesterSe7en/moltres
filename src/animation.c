#include "animation.h"
#include "vector.h"

struct AnimationInfo {
  Vector2i origin;
  Vector2i offset;
  SDL_Texture *spritesheet;
};

/**
 * Creates an AnimationInfo struct with the given origin and offset.
 *
 * @param origin The origin of the animation
 * @param offset The offset of the animation
 * @return The AnimationInfo struct
 */
AnimationInfo *anim_info_create(Vector2i origin, Vector2i offset,
                                SDL_Texture *spritesheet) {
  return &((AnimationInfo){
      .origin = origin, .offset = offset, .spritesheet = spritesheet});
}
