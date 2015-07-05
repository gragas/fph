// This file borrows heavily from http://lazyfoo.net/SDL_tutorials/
// Author: Thomas Fischer, and the author of that site^

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

#include "timer.h"
#include "utils.h"
#include "main_menu.h"

SDL_Surface *screen = NULL;

SDL_Event event;

bool init()
{
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
  {
    return 1;
  }
  
  screen = SDL_SetVideoMode( utils::SCREEN_WIDTH, utils::SCREEN_HEIGHT,
			     utils::SCREEN_BPP, SDL_SWSURFACE );  
  // If there was an error while setting up the screen
  if( screen == NULL )
  {
    return 1;
  }
  
  SDL_WM_SetCaption( "Filius Philosophorum", NULL );
  
  // If everything initialized fine
  return true;
}

int main( int argc, char* args [] )
{    

  if( init() == false )
  {
    return 1;
  }
  
  if( Main_Menu::load() == false)
  {
    return 1;
  }
  
  int frame = 0;
  Timer fps;
  
  utils::logic = Main_Menu::logic;
  utils::blit = Main_Menu::blit;
  
  while( utils::quit == false )
  {    
    utils::logic( event );
    
    utils::clear( screen );
    
    utils::blit( screen );

    // Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
      return 1;
    }

    // if( fps.get_ticks() < 1000 / utils::FRAMES_PER_SECOND )
    // {
    //   SDL_Delay( ( 1000 / utils::FRAMES_PER_SECOND ) - fps.get_ticks() );
    // }
  }

  // // Free the surfaces and quit SDL
  // if( f_main_menu() == false )
  // {
  //   return 1;
  // }
  
  SDL_Quit();
  
  return 0;
}
