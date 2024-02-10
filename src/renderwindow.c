#include "renderwindow.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

SDL_Window *create_sdl_window(const char *title, int width, int height) {
  SDL_Window *window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_SHOWN);
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

void clear_renderer(SDL_Renderer *renderer) { SDL_RenderClear(renderer); }

void render(SDL_Renderer *renderer, SDL_Texture *texture) {
  if (renderer == NULL || texture == NULL) {
    fprintf(stderr, "Cannot render texture: renderer or texture is NULL\n");
    return;
  }

  if (SDL_RenderCopy(renderer, texture, NULL, NULL) != 0) {
    fprintf(stderr, "Cannot render texture: %s\n", SDL_GetError());
  };
}

void display(SDL_Renderer *renderer) { SDL_RenderPresent(renderer); }

void cleanup_render_window(RenderWindow *renderwindow) {
  SDL_DestroyRenderer(renderwindow->renderer);
  SDL_DestroyWindow(renderwindow->window);

  renderwindow->renderer = NULL;
  renderwindow->window = NULL;
}
