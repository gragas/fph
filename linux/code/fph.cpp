// This file borrows heavily from http://lazyfoo.net/SDL_tutorials/
// Author: Thomas Fischer, and the author of that site^

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

#include "timer.h"
#include "utils.h"
#include "main_menu.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 55;

SDL_Surface *screen = NULL;

SDL_Event event;

void (*logic)( SDL_Event& ) = NULL;
void (*blit)( SDL_Surface* ) = NULL;

bool init()
{
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
  {
    return 1;
  }
  
  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
  
  // If there was an error while setting up the screen
  if( screen == NULL )
  {
    return 1;
  }
  
  SDL_WM_SetCaption( "Filius Philosophorum", NULL );
  
  // If everything initialized fine
  return true;
}

void clear_screen()
{
    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
}

int main( int argc, char* args [] )
{    

  if( init() == false )
  {
    return 1;
  }
  
  if( l_main_menu() == false)
  {
    return 1;
  }
  
  int frame = 0;
  Timer fps;
  
  logic = logic_main_menu;
  blit = b_main_menu;
  
  while( quit == false )
  {    
    logic( event );
    
    clear_screen();
    
    blit( screen );

    // Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
      return 1;
    }

    if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
    {
      SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
    }
  }

  // // Free the surfaces and quit SDL
  // if( f_main_menu() == false )
  // {
  //   return 1;
  // }
  
  SDL_Quit();
  
  return 0;
}
