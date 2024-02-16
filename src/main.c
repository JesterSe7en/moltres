#include "main.h"
#include "entity.h"
#include "renderwindow.h"
#include <SDL2/SDL_ttf.h>

static int last_frame_time = 0;

void init_subsystems(void) {
  // SDL returns 1 and SDL_image returns 0 on failure
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Cannot initialize SDL: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    fprintf(stderr, "Cannot initialize SDL image: %s\n", SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
  }

  if (TTF_Init() != 0) {
    fprintf(stderr, "Cannot initialize SDL TTF: %s\n", SDL_GetError());
    IMG_Quit();
    SDL_Quit();
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

  // ---- fps display ----
  static Uint32 frames = 0;
  static Uint32 lastTime = 0;

  frames++;
  Uint32 currentTime = SDL_GetTicks64();

  if (currentTime - lastTime >= 1000) {
    float fps = frames / ((currentTime - lastTime) / 1000.0f);

    printf("FPS: %.2f\n", fps);

    // Reset counters for the next second
    frames = 0;
    lastTime = currentTime;
  }
}

void setup_entites(RenderWindow *render_window) {

  SDL_Texture *oak_floor_texture =
      load_texture(render_window->renderer, "assets/oak_woods/oak_floor.png");
  Entity *oak_floor = entity_create_static(v2f(100, 100), v2i(0, 0), 28, 28, 1,
                                           oak_floor_texture);
  add_entity_to_render_window(render_window, "floor", oak_floor);

  // Entity player;
  // SDL_Texture *idle_spritesheet =
  //     load_texture(render_window->renderer, "assets/knight/_Idle.png");
  // entity_init_dynamic(&player, v2f(100, 100), v2i(44, 42), 21, 38, v2i(120,
  // 0),
  //                     0.5, 1, "idle", idle_spritesheet);
  // SDL_Texture *jump_spritesheet =
  //     load_texture(render_window->renderer, "assets/knight/_Jump.png");
  // entity_add_animation(&player, v2i(0, 0), v2i(20, 20), 0.5, "jump",
  //                      jump_spritesheet);
  // SDL_Texture *run_spritesheet =
  //     load_texture(render_window->renderer, "assets/knight/_Run.png");
  // entity_add_animation(&player, v2i(0, 0), v2i(20, 20), 0.5, "run",
  //                      run_spritesheet);
  // add_entity_to_render_window(render_window, "player", &player);
}

int main(int argc, char *argv[]) {
  init_subsystems();

  RenderWindow render_window = render_window_create("Game v1.0", 800, 600);

  bool game_is_running = true;

  setup_entites(&render_window);
  load_font(&render_window, "assets/fonts/JosefinSans-Regular.ttf");

  SDL_Event event;
  float fps;
  while (game_is_running) {
    process_inputs(&game_is_running);
    update();
    render_all(&render_window);

    // SDL_Color sdlcolor = {255, 0, 0, 255}; // red
    // SDL_Surface *surface =
    //     TTF_RenderText_Solid(render_window.font, fps, sdlcolor);
    //
    // SDL_Texture *fps_texture =
    //     SDL_CreateTextureFromSurface(render_window.renderer, surface);
    //
    display(&render_window);
  }

  // clean up entities
  cleanup_entities(&render_window);
  cleanup_render_window(&render_window);

  SDL_Quit();

  return EXIT_SUCCESS;
}
