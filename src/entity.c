#include "entity.h"
#include "animation.h"
#include "hashtable.h"
#include "vector.h"
#include <stdio.h>

bool entity_init_static(Entity *entity, Vector2f position, Vector2i origin,
                        int width, int height, float scale,
                        SDL_Texture *texture) {
  if (entity == NULL) {
    fprintf(stderr, "Could not initialize entity: entity is NULL\n");
    return false;
  }

  entity->x = position.x;
  entity->y = position.y;
  entity->scale = scale;
  entity->current_frame.x = origin.x;
  entity->current_frame.y = origin.y;
  entity->current_frame.w = width;
  entity->current_frame.h = height;

  // if we are using the entire loaded texture, we can query it like this
  // if (SDL_QueryTexture(texture, NULL, NULL, &entity->current_frame.w,
  //                      &entity->current_frame.h) != 0) {
  //   fprintf(stderr,
  //           "Could not query texture during entity initialization: %s\n",
  //           SDL_GetError());
  //   return false;
  // }

  entity->texture = texture;
  entity->curr_anim = NULL;
  entity->anim_info_ht = NULL;
  return true;
}

bool entity_init_dynamic(Entity *entity, Vector2f position, Vector2i origin,
                         int width, int height, Vector2i offset,
                         float frame_duration, float scale, char *anim_name,
                         SDL_Texture *spritesheet) {
  if (entity == NULL) {
    fprintf(stderr, "Could not initialize entity: entity is NULL\n");
    return false;
  }

  entity->x = position.x;
  entity->y = position.y;
  entity->scale = scale;
  entity->current_frame.x = origin.x;
  entity->current_frame.y = origin.y;
  entity->current_frame.w = width;
  entity->current_frame.h = height;
  entity->texture = NULL;
  entity->curr_anim = anim_name;
  entity->anim_info_ht = hashtable_create();
  AnimationInfo ai = {origin, offset, frame_duration, spritesheet};
  hashtable_add(entity->anim_info_ht, anim_name, &ai);

  return true;
}

Entity *entity_create_static(Vector2f position, Vector2i origin, int width,
                             int height, float scale, SDL_Texture *texture) {
  Entity *entity = malloc(sizeof(Entity));
  entity->x = position.x;
  entity->y = position.y;
  entity->scale = scale;
  entity->current_frame.x = origin.x;
  entity->current_frame.y = origin.y;
  entity->current_frame.w = width;
  entity->current_frame.h = height;
  entity->texture = texture;
  entity->curr_anim = NULL;
  entity->anim_info_ht = NULL;
  return entity;
}

Entity *entity_create_dynamic(Vector2f position, Vector2i origin, int width,
                              int height, Vector2i offset, float frame_duration,
                              float scale, char *anim_name,
                              SDL_Texture *spritesheet) {
  Entity *entity = malloc(sizeof(Entity));
  entity->x = position.x;
  entity->y = position.y;
  entity->scale = scale;
  entity->current_frame.x = origin.x;
  entity->current_frame.y = origin.y;
  entity->current_frame.w = width;
  entity->current_frame.h = height;
  entity->texture = NULL;
  entity->curr_anim = anim_name;

  AnimationInfo *ai =
      create_animation_info(origin, offset, frame_duration, spritesheet);
  hashtable_add(entity->anim_info_ht, anim_name, &ai);
  return entity;
}

void entity_add_animation(Entity *entity, Vector2i origin, Vector2i offset,
                          float frame_duration, char *anim_name,
                          SDL_Texture *spritesheet) {
  AnimationInfo ai = {origin, offset, frame_duration, spritesheet};
  hashtable_add(entity->anim_info_ht, anim_name, &ai);
}

void cleanup_entity(Entity *entity) {
  if (entity == NULL) {
    fprintf(stderr, "Could not destroy entity: entity is NULL\n");
    return;
  }

  if (entity->texture != NULL) {
    SDL_DestroyTexture(entity->texture);
  }

  if (entity->anim_info_ht != NULL) {
    hashtable_destroy(entity->anim_info_ht);
  }

  free(entity);
}
