#include "main.h"
#include "entity.h"

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

  SDL_RenderClear(renderer);

  for (int i = 0; i < entity_count; i++) {
    render(renderer, &entities[i]);
  }
}

void render_entity(SDL_Renderer *renderer, Entity *entity) {
  SDL_RenderClear(renderer);
  render(renderer, entity);
}

int main(int argc, char *argv[]) {
  init_subsystems();

  RenderWindow render_window = render_window_create("Game v1.0", 800, 600);

  Entity oak_floor;
  SDL_Texture *oak_floor_texture =
      load_texture(render_window.renderer, "assets/oak_woods/oak_floor.png");
  entity_init_static(&oak_floor, v2f(100, 100), v2i(0, 0), 28, 28, 1,
                     oak_floor_texture);

  Entity player;
  SDL_Texture *idle_spritesheet =
      load_texture(render_window.renderer, "assets/knight/_Idle.png");
  entity_init_dynamic(&player, v2f(100, 100), v2i(44, 42), 21, 38, v2i(120, 0),
                      1, "idle", idle_spritesheet);
  SDL_Texture *jump_spritesheet =
      load_texture(render_window.renderer, "assets/knight/_Jump.png");
  entity_add_animation(&player, v2i(42, 42), v2i(120, 0), "jump",
                       jump_spritesheet);
  SDL_Texture *run_spritesheet =
      load_texture(render_window.renderer, "assets/knight/_Run.png");
  entity_add_animation(&player, v2i(42, 42), v2i(120, 0), "run",
                       run_spritesheet);

  printf("Number of animation associated with player: %zu\n",
         player.anim_info_ht->count);
  printf("Hash table size: %zu\n", player.anim_info_ht->size);

  bool game_is_running = true;

  SDL_Event event;
  while (game_is_running) {
    process_inputs(&game_is_running);
    update();
    render_entity(render_window.renderer, &oak_floor);

    display(render_window.renderer);
  }

  // clean up entities
  cleanup_entity(&oak_floor);
  cleanup_render_window(&render_window);

  SDL_Quit();

  return EXIT_SUCCESS;
}
