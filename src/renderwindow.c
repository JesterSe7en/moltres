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

RenderWindow render_window_create(const char *title, int width, int height) {
  RenderWindow renderwindow;
  renderwindow.window = create_sdl_window(title, width, height);
  renderwindow.renderer = create_sdl_renderer(renderwindow.window);
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

void render(SDL_Renderer *renderer, Entity *entity) {
  if (renderer == NULL || entity->texture == NULL) {
    fprintf(stderr,
            "Cannot render target entity: renderer or texture is NULL\n");
    return;
  }

  SDL_Texture *texture = entity->texture;
  SDL_Rect current_frame = entity->current_frame;

  SDL_Rect src = {current_frame.x, current_frame.y, current_frame.w,
                  current_frame.h};
  SDL_Rect dest = {entity->x * entity->scale, entity->y * entity->scale,
                   src.w * entity->scale, src.h * entity->scale};

  if (SDL_RenderCopy(renderer, texture, &src, &dest) != 0) {
    fprintf(stderr, "Cannot render texture: %s\n", SDL_GetError());
  };
}

void add_entity_to_render_window(RenderWindow *render_window,
                                 const char *entity_name, Entity *entity) {
  printf("Adding %s to render window\n", entity_name);
  hashtable_add(render_window->entity_ht, entity_name, entity);
  render(render_window->renderer, entity);
}

Entity *get_entity_from_render_window(RenderWindow *renderwindow,
                                      const char *entity_name) {
  return hashtable_get(renderwindow->entity_ht, entity_name);
}

void display(RenderWindow *render_window) {
  SDL_RenderPresent(render_window->renderer);
}

void cleanup_render_window(RenderWindow *renderwindow) {
  SDL_DestroyRenderer(renderwindow->renderer);
  SDL_DestroyWindow(renderwindow->window);

  renderwindow->renderer = NULL;
  renderwindow->window = NULL;
}
