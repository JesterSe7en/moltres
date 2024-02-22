#include "main.h"
#include "animation.h"
#include "entity.h"
#include "renderwindow.h"
#include "utils.h"
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

static int last_frame_time = 0;
static int global_fps = 0;

void InitSubsystems(void) {
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

void ProcessInputs(bool *game_is_running) {
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

void Update(RenderWindow *render_window) {
  float delta_t = (SDL_GetTicks64() - last_frame_time) / 1000.0f;
  last_frame_time = SDL_GetTicks64();

  // ---- fps Display ----
  static Uint32 frames = 0;
  static Uint32 last_time = 0;
  // cache player entity
  static Entity *player = NULL;
  static AnimationInfo *ai = NULL;

  frames++;
  Uint32 current_time = SDL_GetTicks64();
  if (player == NULL) {
    player = (Entity *) HashtableGet(&render_window->entity_ht_, "player");
    ai = (AnimationInfo *) HashtableGet(&player->anim_info_ht, "run");
  }

  if (ai != NULL) {
    ai->elapsed_time += delta_t;

    float total_duration = ai->total_frames * ai->frame_duration;

    if (total_duration > 0 && ai->elapsed_time >= total_duration) {
      ai->elapsed_time = fmodf(ai->elapsed_time, total_duration);
    }

    ai->cur_frame = (int) (ai->elapsed_time / ai->frame_duration);

    player->current_frame.x = ai->origin.x + ai->offset.x * ai->cur_frame;
    player->current_frame.y = ai->origin.y + ai->offset.y * ai->cur_frame;
    player->current_frame.w = ai->size.x;
    player->current_frame.h = ai->size.y;
  }

  if (current_time - last_time >= 1000) {
    global_fps = frames / ((current_time - last_time) / 1000.0f);

    // Reset counters for the next second
    frames = 0;
    last_time = current_time;
  }
}

void SetupEntities(RenderWindow *render_window) {

  SDL_Renderer *renderer = render_window->renderer_;
  SDL_Window *window = render_window->window_;

  PathBuilder builder = {NULL, 0};
  int w, h;

  // ---- Background ----
  SDL_GetWindowSize(window, &w, &h);
  append(&builder, "..");
  append(&builder, "assets");
  append(&builder, "oak_woods");
  append(&builder, "background");
  append(&builder, "background_layer_1.png");
  printf("%s\n", builder.buffer);

  SDL_Texture *background_texture = LoadTexture(renderer, builder.buffer);
  // SDL_Texture *background_texture = LoadTexture(
  //     renderer, "..\\assets\\oak_woods\\background\\background_layer_1.png");
  Entity *background = EntityCreate(V2F(0, 0), V2I(0, 0), w, h, 1, background_texture);
  AddEntityToRenderWindow(render_window, "background", background);

  clear(&builder);
  append(&builder, "..");
  append(&builder, "assets");
  append(&builder, "oak_woods");
  append(&builder, "background");
  append(&builder, "background_layer_2.png");
  SDL_Texture *background2_texture = LoadTexture(renderer, builder.buffer);
  Entity *background2 = EntityCreate(V2F(0, 0), V2I(0, 0), w, h, 1, background2_texture);
  AddEntityToRenderWindow(render_window, "background2", background2);

  clear(&builder);
  append(&builder, "..");
  append(&builder, "assets");
  append(&builder, "oak_woods");
  append(&builder, "background");
  append(&builder, "background_layer_3.png");
  SDL_Texture *background3_texture = LoadTexture(renderer, builder.buffer);
  Entity *background3 = EntityCreate(V2F(0, 0), V2I(0, 0), w, h, 1, background3_texture);
  AddEntityToRenderWindow(render_window, "background3", background3);

  //---- Floor ----
  clear(&builder);
  append(&builder, "..");
  append(&builder, "assets");
  append(&builder, "oak_woods");
  append(&builder, "oak_floor.png");
  SDL_Texture *oak_floor_texture = LoadTexture(renderer, builder.buffer);
  SDL_QueryTexture(oak_floor_texture, NULL, NULL, &w, &h);
  Entity *oak_floor = EntityCreate(V2F(100, 100), V2I(0, 0), w, h, 1, oak_floor_texture);
  AddEntityToRenderWindow(render_window, "floor", oak_floor);

  //---- Player ----
  clear(&builder);
  append(&builder, "..");
  append(&builder, "assets");
  append(&builder, "knight");
  append(&builder, "_Idle.png");
  Entity *player = EntityCreate(V2F(200, 100), V2I(44, 42), 21, 38, 1, NULL);
  SDL_Texture *idle_spritesheet = LoadTexture(renderer, builder.buffer);
  AnimationInfoProperties props = {
      .origin = V2I(44, 42),
      .offset = V2I(120, 0),
      .size = V2I(21, 38),
      .fps = 10,
      .total_frames = 5,
  };
  EntityAddAnimation(player, "idle", idle_spritesheet, &props);
  clear(&builder);
  append(&builder, "..");
  append(&builder, "assets");
  append(&builder, "knight");
  append(&builder, "_Run.png");
  SDL_Texture *run_spritesheet = LoadTexture(renderer, builder.buffer);
  AnimationInfoProperties props_run = {
      .origin = V2I(41, 40),
      .offset = V2I(120, 0),
      .size = V2I(37, 40),
      .fps = 10,
      .total_frames = 10,
  };
  EntityAddAnimation(player, "run", run_spritesheet, &props_run);
  AddEntityToRenderWindow(render_window, "player", player);
}

void RenderFps(RenderWindow *render_window) {
  SDL_Color sdl_color = {255, 0, 0, 255}; // red
  char fps[32];
  snprintf(fps, sizeof(fps), "%d", global_fps);
  int text_w, text_h;
  TTF_SizeText(render_window->font_, fps, &text_w, &text_h);

  SDL_Surface *surface = TTF_RenderText_Solid(render_window->font_, fps, sdl_color);

  SDL_Texture *fps_texture = SDL_CreateTextureFromSurface(render_window->renderer_, surface);

  int screen_h;
  SDL_GetWindowSize(render_window->window_, NULL, &screen_h);

  //  bottom left of the screen
  SDL_Rect target = {0, screen_h - text_h, text_w, text_h};
  (void)SDL_RenderCopy(render_window->renderer_, fps_texture, NULL, &target);
}

int main(int argc, char *argv[]) {

  InitSubsystems();

  RenderWindow *render_window = RenderWindowCreate("Game v1.0", 800, 600);

  bool game_is_running = true;

  SetupEntities(render_window);
  PathBuilder builder = {NULL, 0};
  append(&builder, "..");
  append(&builder, "assets");
  append(&builder, "fonts");
  append(&builder, "VCR_OSD_MONO.ttf");
  LoadFont(render_window, builder.buffer, 14);

  while (game_is_running) {
    (void)SDL_RenderClear(render_window->renderer_);

    ProcessInputs(&game_is_running);
    Update(render_window);
    RenderAll(render_window);
#ifdef MOLTRES_DEBUG
    RenderFps(render_window);
#endif
    Display(render_window);
  }

  // clean up entities
  CleanupEntities(render_window);
  CleanupRenderWindow(render_window);
  render_window = NULL;

  SDL_Quit();

  return EXIT_SUCCESS;
}
