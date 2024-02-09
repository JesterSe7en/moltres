#ifndef INCLUDE_MOLTRES_RENDERWINDOW_H_
#define INCLUDE_MOLTRES_RENDERWINDOW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} RenderWindow;

SDL_Window *create_sdl_window(const char *, int, int);
SDL_Renderer *create_sdl_renderer(SDL_Window *);
void cleanup_render_window(RenderWindow *);

#endif // INCLUDE_MOLTRES_RENDERWINDOW_H_
