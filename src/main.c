#include "main.h"
#include "renderwindow.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void init_subsystems(void) {
  // SDL returns 1 and SDL_image returns 0 on failure
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Cannot initialize SDL: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  if (!IMG_Init(IMG_INIT_PNG)) {
    fprintf(stderr, "Cannot initialize SDL image: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]) {
  RenderWindow render_window;
  init_subsystems();

  render_window.window = create_sdl_window("Game v1.0", 800, 600);
  render_window.renderer = create_sdl_renderer(render_window.window);

  bool game_is_running = true;

  SDL_Event event;

  while (game_is_running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        game_is_running = false;
      }
    }
  }

  cleanup_render_window(&render_window);

  SDL_Quit();

  return EXIT_SUCCESS;
}
