#include "SDL/SDL.h"
#include <string>

#include "utils.h"
#include "map_utils.h"
#include "player.h"
#include "solo_game.h"

SDL_Surface * SoloGame::i_background = NULL;

bool SoloGame::load( std::string character_name )
{
  // i_background = utils::load_image( "data/images/solo_game/ ... " );
    
  map_utils::init();
  Player::load( character_name );

  return true;
}

bool SoloGame::free()
{
  SDL_FreeSurface( SoloGame::i_background );
  return true;
}

void SoloGame::logic( SDL_Event& event )
{
  while( SDL_PollEvent( &event ) )
  {
    if( event.type == SDL_QUIT )
    {
      utils::quit = true;
    }
    else if( event.type == SDL_KEYUP )
    {
      switch( event.key.keysym.sym )
      {
      case SDLK_ESCAPE:
	utils::quit = true;
	break;
      default:
	break;
      }
    }
  }
}

void SoloGame::blit( SDL_Surface * destination )
{  
  int x_position = -utils::SCREEN_WIDTH + \
    ( map_utils::camera_cx - map_utils::camera_x ) - \
    map_utils::camera_x_trans;
  int y_position = -utils::SCREEN_HEIGHT + \
    ( map_utils::camera_cy - map_utils::camera_y ) - \
    map_utils::camera_y_trans;

//  utils::apply_surface( 
//    x_position, y_position,
//    map_utils::surface_tiles,
//    destination );
//  utils::apply_surface( 
//    x_position, y_position,
//    map_utils::surface_one,
//    destination );
  utils::apply_surface(
    x_position, y_position,
    map_utils::surface_bottom,
    destination );
  // If there is a character, draw them here, between one and two
  Player::blit( destination );
  utils::apply_surface( 
    x_position, y_position,
    map_utils::surface_two,
    destination );
}

void SoloGame::update( )
{
  utils::keystates = SDL_GetKeyState( NULL );
  Player::update();
  map_utils::update_map( "test", true );
}
