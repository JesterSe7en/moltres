#include "animation.h"

/**
 * Creates an AnimationInfo struct with the given origin and offset.
 *
 * @param origin The origin of the animation
 * @param offset The offset of the animation
 * @return The AnimationInfo struct
 */
AnimationInfo ani_info(Vector2i *origin, int offset) {
  return (AnimationInfo){.origin = *origin, .offset = offset};
}
