#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "utils.h"

bool quit = false;

SDL_Surface *load_image( std::string filename )
{
  SDL_Surface* loadedImage = NULL;
  
  SDL_Surface* optimizedImage = NULL;
  
  loadedImage = IMG_Load( filename.c_str() );
  
  if( loadedImage != NULL )
  {
    optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
    SDL_FreeSurface( loadedImage );
  }
  
  return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
  SDL_Rect offset; 
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface( source, NULL, destination, &offset );
}
