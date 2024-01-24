#ifndef DOOMY_H
#define DOOMY_H

#include <iostream>
#include <vector>
#include "mathy.h"
#include <SDL2/SDL.h>

// header file is what others need to know

// everything here is in pixels
#define XBLOCKS 10
#define YBLOCKS 10
#define SCREENWIDTH 500
#define SCREENHEIGHT 500
#define BLOCKWIDTH (SCREENWIDTH/XBLOCKS)
#define BLOCKHEIGHT (SCREENHEIGHT/YBLOCKS)
#define BLOCKSONSCREENWIDTH (SCREENWIDTH/BLOCKWIDTH)
#define BLOCKSONSCREENHEIGHT (SCREENHEIGHT/BLOCKHEIGHT)

// in pixels
#define FOVRADIUS 5*BLOCKWIDTH
// taking in account the radius is bigger than a block's side
#define FOV_RADIUS_IN_BLOCKS ceil(FOVRADIUS/BLOCKHEIGHT)
#define FOVANGLE 120
#define RAYDEFAULTLEN FOVRADIUS

// TODO: change this
extern SDL_Color colors[3];

// need to add extern for vars
extern int grid [XBLOCKS][YBLOCKS];

point step (ray& r);

void draw_line_on_screen (SDL_Renderer*& renderer, SDL_Color c, ray& r);

void cast_rays (point& starting_pos);

void step_and_draw_all (SDL_Renderer*& renderer);

// returns point for step
point step (ray& r);

void draw_line_on_screen (ray& r, SDL_Color c, SDL_Renderer*& renderer);

#endif // DOOMY_H