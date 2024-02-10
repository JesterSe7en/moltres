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
  RenderWindow render_window = {NULL, NULL};
  init_subsystems();

  render_window.window = create_sdl_window("Game v1.0", 800, 600);
  render_window.renderer = create_sdl_renderer(render_window.window);

  SDL_Delay(1000);

  SDL_Texture *oak_floor_texture =
      load_texture(render_window.renderer, "assets/oak_woods/oak_floor.png");

  bool game_is_running = true;

  SDL_Event event;

  while (game_is_running) {

    // process events
    // update
    // render

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
      case SDL_WINDOWEVENT_CLOSE:
        game_is_running = false;
        break;
      }

      const Uint8 *key_state = SDL_GetKeyboardState(NULL);
      if (key_state[SDL_SCANCODE_ESCAPE]) {
        game_is_running = false;
      }
    }

    clear_renderer(render_window.renderer);
    render(render_window.renderer, oak_floor_texture);
    display(render_window.renderer);
  }

  cleanup_render_window(&render_window);

  SDL_Quit();

  return EXIT_SUCCESS;
}
