#include "SDL/SDL.h"
#include "utils.h"
#include "main_menu.h"

 SDL_Surface *i_splash_background;
SDL_Surface *i_splash_title;

bool l_main_menu()
{
  i_splash_background = load_image( "data/images/splash/background.png" );
  i_splash_title = load_image( "data/images/splash/title2.png" );
  
  if( i_splash_background == NULL ||
      i_splash_title == NULL)
  {
    return false;
  }
  
  // If everything loaded fine
  return true;
}

bool f_main_menu()
{
  SDL_FreeSurface( i_splash_background );
  SDL_FreeSurface( i_splash_title );
}

void logic_main_menu( SDL_Event &event )
{
  while( SDL_PollEvent( &event ) )
  {
    if( event.type == SDL_QUIT )
    {
      quit = true;
    } else if( event.type == SDL_KEYDOWN )
    {
      switch( event.key.keysym.sym )
      {
      case SDLK_ESCAPE: quit = true;
      }
    } else if( event.type == SDL_MOUSEMOTION )
    {
      // setup the enum
    } else if( event.type == SDL_MOUSEBUTTONDOWN )
    {
      if( event.button.button == SDL_BUTTON_LEFT )
      {
	// mouse down
      }
    } else if( event.type == SDL_MOUSEBUTTONUP )
    {
      if( event.button.button == SDL_BUTTON_LEFT )
      {
	// mouse up
      }
    }
  }
}

void b_main_menu( SDL_Surface* screen )
{
    apply_surface( 0, 0, i_splash_background, screen );  
    apply_surface( screen->w / 2 - i_splash_title->w / 2,  screen->h / 3 - i_splash_title->h / 2, i_splash_title, screen );
}
