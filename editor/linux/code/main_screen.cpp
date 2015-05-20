#include "SDL/SDL.h"
#include <string>

#include "utils.h"
#include "main_screen.h"

SDL_Surface *Main_Screen::i_background = NULL;

bool Main_Screen::load()
{
  Main_Screen::i_background = utils::load_image( "data/images/load/background.png" );
  return true;
}

bool Main_Screen::free()
{
  SDL_FreeSurface( Main_Screen::i_background );
  return true;
}

void Main_Screen::logic( SDL_Event& event )
{
  while( SDL_PollEvent( &event ) )
  {
    if( event.type == SDL_QUIT )
    {
      utils::quit = true;
    }
  }
}

void Main_Screen::blit( SDL_Surface* screen )
{
  utils::apply_surface( 0, 0, Main_Screen::i_background, screen );
}
