#include "main.h"
#include "entity.h"
#include "renderwindow.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

static int last_frame_time = 0;
static int global_fps = 0;

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

void update(RenderWindow *render_window) {
  float deltaT = (SDL_GetTicks64() - last_frame_time) / 1000.0f;

  // FIXME: maybe either use the static lastTime in this function or the global
  last_frame_time = SDL_GetTicks64();

  // ---- fps display ----
  static Uint32 frames = 0;
  static Uint32 lastTime = 0;
  // cache player entity
  static Entity *player = NULL;
  static AnimationInfo *ai = NULL;

  frames++;
  Uint32 currentTime = SDL_GetTicks64();
  // if (player == NULL) {
  //   player = (Entity *)hashtable_get(&render_window->entity_ht, "player");
  //   ai = (AnimationInfo *)hashtable_get(&player->anim_info_ht, "idle");
  // }

  if (currentTime - lastTime >= 1000) {
    global_fps = frames / ((currentTime - lastTime) / 1000.0f);

    // Reset counters for the next second
    frames = 0;
    lastTime = currentTime;
  }

  // if (player != NULL) {
  //   if (currentTime - lastTime >= ai->frame_duration) {
  //     // go to next animation frame.
  //     player->current_frame.x = ai->origin.x + ai->offset.x * ai->cur_frame;
  //     player->current_frame.y = ai->origin.y + ai->offset.y * ai->cur_frame;
  //     printf("Source rect: x:%d y:%d w:%d h:%d\n", player->current_frame.x,
  //            player->current_frame.y, player->current_frame.w,
  //            player->current_frame.h);
  //     if (ai->cur_frame >= ai->total_frames) {
  //       ai->cur_frame = 0;
  //     } else {
  //       ai->cur_frame++;
  //     }
  //   }
  // }
  // lastTime = currentTime;
}

void setup_entites(RenderWindow *render_window) {

  // oak_floor.png is just one tile
  SDL_Texture *oak_floor_texture =
      load_texture(render_window->renderer, "assets/oak_woods/oak_floor.png");
  int w, h;
  SDL_QueryTexture(oak_floor_texture, NULL, NULL, &w, &h);
  Entity *oak_floor =
      entity_create(v2f(100, 100), v2i(0, 0), w, h, 1, oak_floor_texture);
  add_entity_to_render_window(render_window, "floor", oak_floor);

  // SDL_Texture *idle_spritesheet =
  //     load_texture(render_window->renderer, "assets/knight/_Idle.png");
  // Entity *player =
  //     entity_create(v2f(200, 100), v2i(44, 42), 21, 28, 1, idle_spritesheet);
  // entity_add_animation(player, v2i(44, 42), v2i(120, 0), 10, 24, 5, "idle",
  //                      idle_spritesheet);
  // add_entity_to_render_window(render_window, "player", player);
  // SDL_Texture *jump_spritesheet =
  //     load_texture(render_window->renderer, "assets/knight/_Jump.png");
  // entity_add_animation(&player, v2i(0, 0), v2i(20, 20), 0.5, "jump",
  //                      jump_spritesheet);
  // SDL_Texture *run_spritesheet =
  //     load_texture(render_window->renderer, "assets/knight/_Run.png");
  // entity_add_animation(&player, v2i(0, 0), v2i(20, 20), 0.5, "run",
  //                      run_spritesheet);
  // add_entity_to_render_window(render_window, "player", &player);
  //
}

void render_fps(RenderWindow *render_window) {
  SDL_Color sdlcolor = {255, 0, 0, 255}; // red
  char fps[32];
  snprintf(fps, sizeof(fps), "FPS: %d", global_fps);
  int w, h;
  TTF_SizeText(render_window->font, fps, &w, &h);

  SDL_Surface *surface =
      TTF_RenderText_Solid(render_window->font, fps, sdlcolor);

  SDL_Texture *fps_texture =
      SDL_CreateTextureFromSurface(render_window->renderer, surface);

  SDL_Rect target = {200, 200, w, h};
  SDL_RenderCopy(render_window->renderer, fps_texture, NULL, &target);
}

int main(int argc, char *argv[]) {
  init_subsystems();

  RenderWindow *render_window = render_window_create("Game v1.0", 800, 600);

  bool game_is_running = true;

  setup_entites(render_window);
  load_font(render_window, "assets/fonts/JosefinSans-Regular.ttf");

  SDL_Event event;
  float fps;
  while (game_is_running) {
    SDL_RenderClear(render_window->renderer);

    process_inputs(&game_is_running);
    update(render_window);
    render_all(render_window);
#ifdef DEBUG
    render_fps(render_window);
#endif
    display(render_window);
  }

  // clean up entities
  cleanup_entities(render_window);
  cleanup_render_window(render_window);

  SDL_Quit();

  return EXIT_SUCCESS;
}
