#include "SDL/SDL.h"
#include <string>

#include "utils.h"
#include "load.h"

SDL_Surface *Load::i_background = NULL;

bool Load::load()
{
  Load::i_background = utils::load_image( "data/images/load/background.png" );
  return true;
}

bool Load::free()
{
  SDL_FreeSurface( Load::i_background );
  return true;
}

void Load::logic( SDL_Event& event )
{
  while( SDL_PollEvent( &event ) )
  {
    if( event.type == SDL_QUIT )
    {
      utils::quit = true;
    }
  }
}

void Load::blit( SDL_Surface* screen )
{
  utils::apply_surface( 0, 0, Load::i_background, screen );
}
