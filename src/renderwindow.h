#ifndef INCLUDE_MOLTRES_RENDERWINDOW_H_
#define INCLUDE_MOLTRES_RENDERWINDOW_H_

#include "entity.h"
#include "hashtable.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  HashTable *entity_ht;
  TTF_Font *font;
} RenderWindow;

/**
 * Create render window
 *
 * @param title The title of render window
 * @param width The width of render window
 * @param height The height of render window
 * @return RenderWindow
 */
RenderWindow render_window_create(const char *title, int width, int height);

/**
 * Load texture drectly from file
 *
 * @param renderer SDL Renderer
 * @param file_path Path to image
 * @return SDL_Texture The texture from source image
 */
SDL_Texture *load_texture(SDL_Renderer *renderer, const char *file_path);

void load_font(RenderWindow *render_window, const char *font_path);

/**
 * Renders the entity using the SDL renderer
 *
 * @param renderer The SDL renderer
 * @param entity The entity to render
 */
void render(SDL_Renderer *renderer, Entity *entity);

/**
 * Renders all entities in the render window
 *
 * @param render_window The render window
 */
void render_all(RenderWindow *render_window);

/**
 * Draws the render window
 *
 * @param render_window The render window
 */
void display(RenderWindow *render_window);

/**
 * Add an entity to the render window
 *
 * @param render_window The render window
 * @param entity_name The name of the entity
 * @param entity The entity to add
 */
void add_entity_to_render_window(RenderWindow *render_window,
                                 const char *entity_name, Entity *entity);

/**
 * Get an entity from the render window
 *
 * @param render_window The render window
 * @param entity_name The name of the entity
 * @param entity The entity to get
 */
Entity *get_entity_from_render_window(RenderWindow *renderwindow,
                                      const char *entity_name);

void cleanup_entities(RenderWindow *render_window);

void cleanup_render_window(RenderWindow *render_window);

#endif // INCLUDE_MOLTRES_RENDERWINDOW_H_
