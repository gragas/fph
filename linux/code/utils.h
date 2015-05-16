#include "SDL/SDL.h"
#include <string>

#ifndef UTILS_H
#define UTILS_H

extern bool quit;

SDL_Surface *load_image( std::string filename );
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination);

#endif
