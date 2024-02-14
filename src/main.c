#include "main.h"
#include "animation.h"
#include "entity.h"
#include "player.h"
#include "renderwindow.h"
#include "vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int last_frame_time = 0;

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

void process_inputs(bool *game_is_running) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
    case SDL_WINDOWEVENT_CLOSE:
      printf("Window close event received, exiting game...\n");
      *game_is_running = false;
      break;
    }

    const Uint8 *key_state = SDL_GetKeyboardState(NULL);
    if (key_state[SDL_SCANCODE_ESCAPE]) {
      printf("Escape key pressed, exiting game...\n");
      *game_is_running = false;
    }
  }
}

void update(void) {
  float deltaT = (SDL_GetTicks64() - last_frame_time) / 1000.0f;

  last_frame_time = SDL_GetTicks64();
}

void render_entities(SDL_Renderer *renderer, Entity *entities,
                     int entity_count) {

  clear_renderer(renderer);

  for (int i = 0; i < entity_count; i++) {
    render(renderer, &entities[i]);
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

  int entity_count = 3;
  Entity entities[entity_count];

  for (int i = 0; i < entity_count; i++) {
    if (!init_entity(&entities[i], v2f(0, 0), 0, 0, 1, oak_floor_texture)) {
      fprintf(stderr, "Cannot initialize entity: %s\n", SDL_GetError());
    }
  }

  Vector2f spawn_point = v2f(100, 100);
  Player player = player_create(&spawn_point);

  AnimationInfo *walk_anim = anim_info_create(
      v2i(44, 42), v2i(120, 0),
      IMG_LoadTexture(render_window.renderer, "assets/knight/_Walk.png"));

  // player needs initial spawn point
  // starting animation - pointer to specific animation info
  // all animations used by player - an array?

  bool game_is_running = true;

  SDL_Event event;
  while (game_is_running) {

    process_inputs(&game_is_running);
    update();
    render_entities(render_window.renderer, entities, entity_count);

    display(render_window.renderer);
  }

  // clean up entities
  for (int i = 0; i < entity_count; i++) {
    cleanup_entity(&entities[i]);
  }

  cleanup_render_window(&render_window);

  SDL_Quit();

  return EXIT_SUCCESS;
}
