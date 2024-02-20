#include "entity.h"
#include "renderwindow.h"
#include "vector.h"

#ifdef _WIN32
#include <SDL2/SDL_main.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
