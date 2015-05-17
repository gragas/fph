#include "SDL/SDL.h"
#include <string>

#ifndef UTILS_H
#define UTILS_H

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_BPP;
extern const int FRAMES_PER_SECOND;

extern bool quit;

SDL_Surface *load_image( std::string filename );
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination);

#endif
