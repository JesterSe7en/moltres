#include "renderwindow.h"
#include <SDL2/SDL_error.h>
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

void cleanup_render_window(RenderWindow *renderwindow) {
  SDL_DestroyRenderer(renderwindow->renderer);
  SDL_DestroyWindow(renderwindow->window);

  renderwindow->renderer = NULL;
  renderwindow->window = NULL;
}
