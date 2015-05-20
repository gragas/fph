#include "SDL/SDL.h"
#include <string>

#include "utils.h"
#include "main_screen.h"

SDL_Surface *Main_Screen::i_background = NULL;
SDL_Surface *Main_Screen::i_red_select_square = NULL;
unsigned int Main_Screen::uint_selection = 0;

bool Main_Screen::load()
{
  Main_Screen::i_background = utils::load_image( "data/images/main_screen/background.png" );
  Main_Screen::i_red_select_square = utils::load_image( "data/images/main_screen/red_select_square.png" );
  return true;
}

bool Main_Screen::free()
{
  SDL_FreeSurface( Main_Screen::i_background );
  SDL_FreeSurface( Main_Screen::i_red_select_square );
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
    else if( event.type == SDL_MOUSEBUTTONDOWN ) 
    {
      //
    }
    else if( event.type == SDL_MOUSEBUTTONUP )
    {
      if( event.button.button == SDL_BUTTON_LEFT )
      {
	if( event.button.y > 15 && event.button.y < 79 )
        {
	  if( event.button.x > 751 && event.button.x < 815 )
	  {
	    Main_Screen::uint_selection = 1;
	  }
	  else if( event.button.x > 835 && event.button.x < 899 )
	  {
	    Main_Screen::uint_selection = 2;
	  }
	  else if( event.button.x > 920 && event.button.x < 984 )
	  {
	    Main_Screen::uint_selection = 3;
	  }
	}
      }
    }
  }
}

void Main_Screen::blit( SDL_Surface* screen )
{
  utils::apply_surface( 0, 0, Main_Screen::i_background, screen );
  switch(uint_selection)
  {
  case 0: // nothing selected
    break;
  case 1: // selected grass
    utils::apply_surface( 751, 15, Main_Screen::i_red_select_square, screen );
    break;
  case 2: // selected dirt
    utils::apply_surface( 835, 15, Main_Screen::i_red_select_square, screen );
    break;
  case 3: // selected sand
    utils::apply_surface( 920, 15, Main_Screen::i_red_select_square, screen );
    break;
  }
}
