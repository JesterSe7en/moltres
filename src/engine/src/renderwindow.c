#include "renderwindow.h"
#include "entity.h"
#include "hashtable.h"
#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdio.h>

SDL_Window *CreateSdlWindow(const char *title, int width, int height) {
  SDL_Window *window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  if (window == NULL) { fprintf(stderr, "Cannot create SDL window_: %s\n", SDL_GetError()); }
  return window;
}

SDL_Renderer *CreateSdlRenderer(SDL_Window *window) {
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == NULL) { fprintf(stderr, "Cannot create SDL renderer_: %s\n", SDL_GetError()); }
  return renderer;
}

RenderWindow *RenderWindowCreate(const char *title, int width, int height) {
  RenderWindow *render_window = malloc(sizeof(RenderWindow));
  render_window->window_ = CreateSdlWindow(title, width, height);
  render_window->renderer_ = CreateSdlRenderer(render_window->window_);
  render_window->entity_ht_ = HashtableCreate();
  return render_window;
}

SDL_Texture *LoadTexture(SDL_Renderer *renderer, const char *file_path) {
  if (renderer == NULL) {
    fprintf(stderr, "Cannot load texture: SDL renderer_ is NULL\n");
    return NULL;
  }

  SDL_Texture *texture = IMG_LoadTexture(renderer, file_path);
  if (texture == NULL) { fprintf(stderr, "Cannot load image as texture: %s\n", SDL_GetError()); }

  return texture;
}

/**
 * Load texture as surface then as texture
 *
 * @param renderer SDL Renderer
 * @param file_path Path to image
 * @return SDL_Texture The texture from source image
 */
SDL_Texture *LoadTextureFromMemory(SDL_Renderer *renderer, const char *file_path) {
  if (renderer == NULL) {
    fprintf(stderr, "Cannot load texture: SDL renderer_ is NULL\n");
    return NULL;
  }
  SDL_Surface *surface = IMG_Load(file_path);
  if (surface == NULL) {
    fprintf(stderr, "Cannot load image as surface: %s\n", SDL_GetError());
    return NULL;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == NULL) { fprintf(stderr, "Cannot load image as texture: %s\n", SDL_GetError()); }
  return texture;
}

void LoadFont(RenderWindow *render_window, const char *font_path, int font_size) {
  TTF_Font *font = TTF_OpenFont(font_path, font_size);
  if (font == NULL) { fprintf(stderr, "Cannot load font_: %s\n", TTF_GetError()); }
  render_window->font_ = font;
}

void Render(SDL_Renderer *renderer, Entity *entity) {
  if (entity == NULL) {
    fprintf(stderr, "Cannot Render entity: entity is NULL\n");
    return;
  }

  if (renderer == NULL || entity->texture == NULL) {
    fprintf(stderr, "Cannot Render target entity: renderer_ or texture is NULL\n");
    return;
  }

  SDL_Texture *texture = entity->texture;
  SDL_Rect current_frame = entity->current_frame;
  SDL_Rect src, dest;

  src.x = current_frame.x;
  src.y = current_frame.y;
  src.w = current_frame.w;
  src.h = current_frame.h;

  dest.x = entity->position.x * entity->scale;
  dest.y = entity->position.y * entity->scale;
  dest.w = src.w * entity->scale;
  dest.h = src.h * entity->scale;

  if (SDL_RenderCopy(renderer, texture, &src, &dest) != 0) {
    fprintf(stderr, "Cannot Render texture: %s\n", SDL_GetError());
  }
}

void RenderAll(RenderWindow *render_window) {
  HashTable *ht = render_window->entity_ht_;

  HashTableIterator it = HashtableIteratorCreate(ht);
  while (HashtableIteratorHasNext(&it)) {
    Entry *entry = HashtableIteratorNext(&it);
    if (entry == NULL) {
      fprintf(stderr, "Cannot render entity: entry is NULL\n");
      continue;
    }
    Entity *entity = (Entity *) entry->value;
    Render(render_window->renderer_, entity);
  }
}

void AddEntityToRenderWindow(RenderWindow *render_window, const char *entity_name, Entity *entity) {
  HashtableAdd(&render_window->entity_ht_, entity_name, entity);
}

Entity *GetEntityFromRenderWindow(RenderWindow *render_window, const char *entity_name) {
  return HashtableGet(&render_window->entity_ht_, entity_name);
}

void Display(RenderWindow *render_window) { SDL_RenderPresent(render_window->renderer_); }

void CleanupEntities(RenderWindow *render_window) {
  HashTableIterator it = HashtableIteratorCreate(render_window->entity_ht_);
  while (HashtableIteratorHasNext(&it)) {
    Entry *entry = HashtableIteratorNext(&it);
    Entity *entity = (Entity *) entry->value;
    CleanupEntity(entity);
    entity = NULL;
  }
}

void CleanupRenderWindow(RenderWindow *render_window) {
  SDL_DestroyRenderer(render_window->renderer_);
  SDL_DestroyWindow(render_window->window_);

  render_window->renderer_ = NULL;
  render_window->window_ = NULL;
  if (render_window->font_ != NULL) {
    TTF_CloseFont(render_window->font_);
    render_window->font_ = NULL;
  }
  HashtableDestroy(render_window->entity_ht_);
  free(render_window);
  render_window = NULL;
}
