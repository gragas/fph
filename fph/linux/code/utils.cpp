#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>
#include "utils.h"

namespace utils
{
  const int SCREEN_WIDTH = 1024;
  const int SCREEN_HEIGHT = 640;
  const int SCREEN_BPP = 32;
  const int FRAMES_PER_SECOND = 60;
  const bool CAP_FRAME_RATE = false;

  bool quit = false;

  void (*logic)( SDL_Event& event ) = NULL;
  void (*blit)( SDL_Surface* screen ) = NULL;

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
    else
    {
      std::cout << "Error loading image " << filename << std::endl;
      quit = true;
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

  void clear( SDL_Surface* screen )
  {
    SDL_FillRect( screen, &screen->clip_rect,
		  SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
  }
  
  void clearA( SDL_Surface* screen )
  {
    SDL_FillRect( screen, &screen->clip_rect,
		  SDL_MapRGBA( screen->format, 0x00, 0x00, 0x0, 0x00 ) );
  }
}
