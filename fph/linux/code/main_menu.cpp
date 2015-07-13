#include <iostream>
#include "SDL/SDL.h"
#include "utils.h"
#include "button.h"
#include "main_menu.h"
#include "load.h"

SDL_Surface *Main_Menu::i_background = NULL;
SDL_Surface *Main_Menu::i_title = NULL;
Button Main_Menu::exit_button;
Button Main_Menu::options_button;
Button Main_Menu::multiplayer_button;
Button Main_Menu::load_button;
Button Main_Menu::new_button;

bool Main_Menu::load()
{
  Main_Menu::i_background = utils::load_image(
    "data/images/main_menu/background.png" );
  Main_Menu::i_title = utils::load_image(
    "data/images/main_menu/title2.png" );
  Main_Menu::exit_button.init(
    utils::SCREEN_WIDTH / 2, utils::SCREEN_HEIGHT * 3 / 4,
    "data/images/main_menu/exit_button_pressed.png",
    "data/images/main_menu/exit_button_unpressed.png" );
  Main_Menu::options_button.init(
    utils::SCREEN_WIDTH / 2, utils::SCREEN_HEIGHT * 3 / 4 - 37,
    "data/images/main_menu/options_button_pressed.png",
    "data/images/main_menu/options_button_unpressed.png" );
  Main_Menu::multiplayer_button.init(
    utils::SCREEN_WIDTH / 2, utils::SCREEN_HEIGHT * 3 / 4 - 74,
    "data/images/main_menu/multiplayer_button_pressed.png",
    "data/images/main_menu/multiplayer_button_unpressed.png" );
  Main_Menu::load_button.init(
    utils::SCREEN_WIDTH / 2, utils::SCREEN_HEIGHT * 3 / 4 - 111,
    "data/images/main_menu/load_button_pressed.png",
    "data/images/main_menu/load_button_unpressed.png" );
  Main_Menu::new_button.init(
    utils::SCREEN_WIDTH / 2, utils::SCREEN_HEIGHT * 3 / 4 - 148,
    "data/images/main_menu/new_button_pressed.png",
    "data/images/main_menu/new_button_unpressed.png" );

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
  options_button.free();
  multiplayer_button.free();
  load_button.free();
  new_button.free();
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
      SDL_GetMouseState( &utils::mouse_x, &utils::mouse_y );
    }
    else if( event.type == SDL_MOUSEBUTTONDOWN )
    {
      if( event.button.button == SDL_BUTTON_LEFT )
      {
	exit_button.update( true );
	options_button.update( true );
	multiplayer_button.update( true );
	load_button.update( true );
	new_button.update( true );
      }
    }
    else if( event.type == SDL_MOUSEBUTTONUP )
    {
      if( event.button.button == SDL_BUTTON_LEFT )
      {
	exit_button.update( false );
	options_button.update( false );
	multiplayer_button.update( false );
	load_button.update( false );
	new_button.update( false );

	if( exit_button.within )
	{
	  utils::quit = true;
	}
	else if( options_button.within )
	{

	}
	else if( multiplayer_button.within )
	{

	}
	else if( load_button.within )
	{
	  if( Main_Menu::free() == false )
	  {
	    std::cout << "ERROR: Failed to free Main_Menu resources" << std::endl;
	    utils::quit = true;
	  }
	  utils::logic = Load::logic;
	  utils::blit = Load::blit;
	  Load::load();	  
	}
	else if( new_button.within )
	{

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
  options_button.draw( screen );
  multiplayer_button.draw( screen );
  load_button.draw( screen );
  new_button.draw( screen );
}
