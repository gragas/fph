#include "SDL/SDL.h"
#include <string>
#include <iostream>

#include "utils.h"
#include "load.h"
#include "solo_game.h"

SDL_Surface *Load::i_background = NULL;

bool Load::load()
{
  // Load::i_background = utils::load_image( "data/images/load/background.png" );
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
    else if( event.type == SDL_KEYDOWN )
    {
      switch( event.key.keysym.sym )
      {
      case SDLK_ESCAPE:
	utils::quit = true;
	break;
      case SDLK_RETURN:
	if( Load::free() == false )
	{
	  std::cout << "ERROR: Failed ot free Load resources" << std::endl;
	  utils::quit = true;
	}
	utils::update = SoloGame::update;
	utils::logic = SoloGame::logic;
	utils::blit = SoloGame::blit;
	SoloGame::load( "Tom" );
	break;
      default:
	break;
      }
    }
  }
}

void Load::blit( SDL_Surface* screen )
{
  // utils::apply_surface( 0, 0, Load::i_background, screen );
}
