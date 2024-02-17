#include "renderwindow.h"
#include "entity.h"
#include "hashtable.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

SDL_Window *create_sdl_window(const char *title, int width, int height) {
  SDL_Window *window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_SHOWN);

  SDL_SysWMinfo info;
  // Cannot just straight call GetWindowWMInfo, need to initialize the version
  SDL_VERSION(&info.version);
  if (!SDL_GetWindowWMInfo(window, &info)) {
    fprintf(stderr, "Cannot get window info: %s\n", SDL_GetError());
  }

  printf("Version: %d.%d\n", info.version.major, info.version.minor);
  printf("Subsystem: %d\n", info.subsystem);

  switch (info.subsystem) {
  case SDL_SYSWM_UNKNOWN:
    printf("Unknown subsystem\n");
    break;
  case SDL_SYSWM_X11:
    // Access X11-specific information in info.info.x11
    printf("X11 Window ID: %lu\n", info.info.x11.window);
    break;
  default:
    printf("Unsupported subsystem\n");
  }

  if (window == NULL) {
    fprintf(stderr, "Cannot create SDL window: %s\n", SDL_GetError());
  }
  return window;
}

SDL_Renderer *create_sdl_renderer(SDL_Window *window) {
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == NULL) {
    fprintf(stderr, "Cannot create SDL renderer: %s\n", SDL_GetError());
  }
  return renderer;
}

RenderWindow *render_window_create(const char *title, int width, int height) {
  RenderWindow *renderwindow = malloc(sizeof(RenderWindow));
  renderwindow->window = create_sdl_window(title, width, height);
  renderwindow->renderer = create_sdl_renderer(renderwindow->window);
  renderwindow->entity_ht = hashtable_create();
  return renderwindow;
}

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file_path) {
  if (renderer == NULL) {
    fprintf(stderr, "Cannot load texture: SDL renderer is NULL\n");
    return NULL;
  }

  SDL_Texture *texture = IMG_LoadTexture(renderer, file_path);
  if (texture == NULL) {
    fprintf(stderr, "Cannot load image as texture: %s\n", SDL_GetError());
  }

  return texture;
}

/**
 * Load texture as surface then as texture
 *
 * @param renderer SDL Renderer
 * @param file_path Path to image
 * @return SDL_Texture The texture from source image
 */
SDL_Texture *load_texture_from_memory(SDL_Renderer *renderer,
                                      const char *file_path) {
  if (renderer == NULL) {
    fprintf(stderr, "Cannot load texture: SDL renderer is NULL\n");
    return NULL;
  }
  SDL_Surface *surface = IMG_Load(file_path);
  if (surface == NULL) {
    fprintf(stderr, "Cannot load image as surface: %s\n", SDL_GetError());
    return NULL;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == NULL) {
    fprintf(stderr, "Cannot load image as texture: %s\n", SDL_GetError());
  }
  return texture;
}

void load_font(RenderWindow *render_window, const char *font_path) {
  TTF_Font *font = TTF_OpenFont(font_path, 24);
  if (font == NULL) {
    fprintf(stderr, "Cannot load font: %s\n", TTF_GetError());
  }
  render_window->font = font;
  printf("Loaded font: %s\n", font_path);
}

void render(SDL_Renderer *renderer, Entity *entity) {
  if (entity == NULL) {
    fprintf(stderr, "Cannot render entity: entity is NULL\n");
    return;
  }

  // if dynamic, check AnimationInfo for the source x and y from origin param
  if (renderer == NULL || entity->texture == NULL) {
    fprintf(stderr,
            "Cannot render target entity: renderer or texture is NULL\n");
    return;
  }

  SDL_Texture *texture = entity->texture;
  SDL_Rect current_frame = entity->current_frame;
  SDL_Rect src, dest;

  if (entity->anim_info_ht != NULL) {
    printf("Trying to render an animation, not implemented yet\n");
    // need to store current animation name
    char *current_animation_running = entity->curr_anim;
    // need to store what frame of the animation it is on, to determine how much
    AnimationInfo *ai =
        hashtable_get(&entity->anim_info_ht, current_animation_running);

    src.x = ai->origin.x;
    src.y = ai->origin.y;
    src.w = current_frame.w;
    src.h = current_frame.h;

    dest.x = entity->x * entity->scale;
    dest.y = entity->y * entity->scale;
    dest.w = src.w * entity->scale;
    dest.h = src.h * entity->scale;

    // offset we need
  } else {
    src.x = current_frame.x;
    src.y = current_frame.y;
    src.w = current_frame.w;
    src.h = current_frame.h;

    dest.x = entity->x * entity->scale;
    dest.y = entity->y * entity->scale;
    dest.w = src.w * entity->scale;
    dest.h = src.h * entity->scale;
  }

  if (SDL_RenderCopy(renderer, texture, &src, &dest) != 0) {
    fprintf(stderr, "Cannot render texture: %s\n", SDL_GetError());
  };
}

void render_all(RenderWindow *render_window) {
  HashTable *ht = render_window->entity_ht;

  HashTableIterator it = hashtable_iterator_create(ht);
  while (hashtable_iterator_has_next(&it)) {
    Entry *entry = hashtable_iterator_next(&it);
    Entity *entity = (Entity *)entry->value;
    render(render_window->renderer, entity);
  }
}

void add_entity_to_render_window(RenderWindow *render_window,
                                 const char *entity_name, Entity *entity) {
  hashtable_add(&render_window->entity_ht, entity_name, entity);
}

Entity *get_entity_from_render_window(RenderWindow *renderwindow,
                                      const char *entity_name) {
  return hashtable_get(&renderwindow->entity_ht, entity_name);
}

void display(RenderWindow *render_window) {
  SDL_RenderPresent(render_window->renderer);
}

void cleanup_entities(RenderWindow *render_window) {
  HashTableIterator it = hashtable_iterator_create(render_window->entity_ht);
  while (hashtable_iterator_has_next(&it)) {
    Entry *entry = hashtable_iterator_next(&it);
    Entity *entity = (Entity *)entry->value;
    cleanup_entity(entity);
  }
}

void cleanup_render_window(RenderWindow *render_window) {
  SDL_DestroyRenderer(render_window->renderer);
  SDL_DestroyWindow(render_window->window);

  render_window->renderer = NULL;
  render_window->window = NULL;
  if (render_window->font != NULL) {
    TTF_CloseFont(render_window->font);
    render_window->font = NULL;
  }
  hashtable_destroy(render_window->entity_ht);
  free(render_window);
  render_window = NULL;
}
