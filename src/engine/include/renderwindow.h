#ifndef MOLTRES_SRC_RENDERWINDOW_H_
#define MOLTRES_SRC_RENDERWINDOW_H_

#include "entity.h"
#include "hashtable.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

/**
 * @struct RenderWindow
 * @brief Represents a render window.
 */
typedef struct {
  SDL_Window *window_;     /**< Pointer to the SDL window */
  SDL_Renderer *renderer_; /**< Pointer to the SDL renderer */
  HashTable *entity_ht_;   /**< Hash table for storing entities */
  TTF_Font *font_;         /**< Pointer to the TTF font */
} RenderWindow;

/**
 * @brief Creates a new render window.
 * @param title The title of the render window.
 * @param width The width of the render window.
 * @param height The height of the render window.
 * @return Pointer to the newly created render window.
 */
RenderWindow *RenderWindowCreate(const char *title, int width, int height);

/**
 * @brief Loads a texture directly from a file.
 * @param renderer Pointer to the SDL renderer.
 * @param file_path Path to the image file.
 * @return Pointer to the texture loaded from the image.
 */
SDL_Texture *LoadTexture(SDL_Renderer *renderer, const char *file_path);

/**
 * @brief Loads a font for the render window.
 * @param render_window Pointer to the render window.
 * @param font_path Path to the font file.
 * @param font_size The size of the font.
 */
void LoadFont(RenderWindow *render_window, const char *font_path, int font_size);

/**
 * @brief Renders an entity using the SDL renderer.
 * @param renderer Pointer to the SDL renderer.
 * @param entity Pointer to the entity to render.
 */
void Render(SDL_Renderer *renderer, Entity *entity);

/**
 * @brief Renders all entities in the render window.
 * @param render_window Pointer to the render window.
 */
void RenderAll(RenderWindow *render_window);

/**
 * @brief Draws the render window.
 * @param render_window Pointer to the render window.
 */
void Display(RenderWindow *render_window);

/**
 * @brief Adds an entity to the render window.
 * @param render_window Pointer to the render window.
 * @param entity_name The name of the entity.
 * @param entity Pointer to the entity to add.
 */
void AddEntityToRenderWindow(RenderWindow *render_window, const char *entity_name, Entity *entity);

/**
 * @brief Retrieves an entity from the render window.
 * @param render_window Pointer to the render window.
 * @param entity_name The name of the entity.
 * @return Pointer to the retrieved entity, or NULL if not found.
 */
Entity *GetEntityFromRenderWindow(RenderWindow *render_window, const char *entity_name);

/**
 * @brief Cleans up all entities in the render window.
 * @param render_window Pointer to the render window.
 */
void CleanupEntities(RenderWindow *render_window);

/**
 * @brief Cleans up the render window and frees associated memory.
 * @param render_window Pointer to the render window.
 */
void CleanupRenderWindow(RenderWindow *render_window);

#endif // MOLTRES_SRC_RENDERWINDOW_H_
