#include <iostream>
#include "SDL/SDL.h"
#include "utils.h"
#include "button.h"
#include "main_menu.h"
#include "load.h"

SDL_Surface *Main_Menu::i_background = NULL;
SDL_Surface *Main_Menu::i_title = NULL;
Button Main_Menu::exit_button;

bool Main_Menu::load()
{
  Main_Menu::i_background = utils::load_image( "data/images/main_menu/background.png" );
  Main_Menu::i_title = utils::load_image( "data/images/main_menu/title2.png" );
  Main_Menu::exit_button.init( utils::SCREEN_WIDTH / 2, utils::SCREEN_HEIGHT * 3 / 4,
			       "data/images/main_menu/exit_button_pressed.png",
			       "data/images/main_menu/exit_button_unpressed.png" );

  
  if( Main_Menu::i_background == NULL or
      Main_Menu::i_title == NULL)
  {
    return false;
  }
  
  // If everything loaded fine
  return true;
}

bool Main_Menu::free()
{
  SDL_FreeSurface( Main_Menu::i_background );
  SDL_FreeSurface( Main_Menu::i_title );
  exit_button.free();
  return true;
}

void Main_Menu::logic( SDL_Event &event )
{
  while( SDL_PollEvent( &event ) )
  {
    if( event.type == SDL_QUIT )
    {
      utils::quit = true;
    } 
    else if( event.type == SDL_KEYDOWN )
    {
      switch( event.key.keysym.sym )
      {
      case SDLK_ESCAPE:
	utils::quit = true;
	break;
      case SDLK_RETURN:
	if( Main_Menu::free() == false )
	{
	  std::cout << "ERROR: Failed to free Main_Menu resources" << std::endl;
	  utils::quit = true;
	}
	utils::logic = Load::logic;
	utils::blit = Load::blit;
	Load::load();
	break;
      default:
	break;
      }
    }
    else if( event.type == SDL_MOUSEMOTION )
    {
      exit_button.update( event.motion.x, event.motion.y );
    }
    else if( event.type == SDL_MOUSEBUTTONDOWN )
    {
      if( event.button.button == SDL_BUTTON_LEFT )
      {
	exit_button.update( true );
      }
    }
    else if( event.type == SDL_MOUSEBUTTONUP )
    {
      if( event.button.button == SDL_BUTTON_LEFT )
      {
	exit_button.update( false );
	if( exit_button.within )
	{
	  utils::quit = true;
	}
      }
    }
  }
}

void Main_Menu::blit( SDL_Surface* screen )
{
  utils::apply_surface( 0, 0, Main_Menu::i_background, screen );  
  utils::apply_surface( screen->w / 2 - Main_Menu::i_title->w / 2,
		 screen->h / 3 - Main_Menu::i_title->h / 2, 
		 Main_Menu::i_title, screen );
  exit_button.draw( screen );
}
