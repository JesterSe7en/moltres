#ifndef INCLUDE_MOLTRES_RENDERWINDOW_H_
#define INCLUDE_MOLTRES_RENDERWINDOW_H_

#include "entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
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

/**
 * Renders the entity using the SDL renderer
 *
 * @param renderer The SDL renderer
 * @param entity The entity to render
 */
void render(SDL_Renderer *renderer, Entity *entity);

/**
 * Draws the render window
 *
 * @param renderer The SDL renderer
 */
void display(SDL_Renderer *renderer);

void cleanup_render_window(RenderWindow *render_window);

#endif // INCLUDE_MOLTRES_RENDERWINDOW_H_
