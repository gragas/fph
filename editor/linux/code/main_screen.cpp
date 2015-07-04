#include "SDL/SDL.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "text.h"
#include "utils.h"
#include "text_utils.h"
#include "main_screen.h"
#include "text_input.h"
#include "map_utils.h"
#include "button.h"

SDL_Surface *Main_Screen::i_background = NULL;
Text Main_Screen::t_filename_label;
Text_Input Main_Screen::ti_filename;
std::string Main_Screen::s_filename;
Text Main_Screen::t_tile_label;
Text_Input Main_Screen::ti_tile;
Text_Input *Main_Screen::ptr_ti_selected_text_input = NULL;
std::string Main_Screen::s_selected_tile;
std::vector<Text_Input*> Main_Screen::text_inputs;
Button Main_Screen::save_button;
Button Main_Screen::tiles_button;
Button Main_Screen::one_button;
Button Main_Screen::two_button;
Button Main_Screen::climate_button;
SDL_Surface **Main_Screen::ptr_selected_surface = NULL;
std::string ( *Main_Screen::ptr_selected_array )[32 * 3][20 * 3];

bool Main_Screen::load()
{
  Main_Screen::i_background = utils::load_image( "data/images/main_screen/background.png" );
  Main_Screen::t_filename_label.init( "Filename:", 0, 0, 715, 5 );
  Main_Screen::ti_filename.init( "test.map", 0, 2, 795, 5, 30 );
  Main_Screen::text_inputs.push_back( &Main_Screen::ti_filename );
  Main_Screen::s_filename = "test.map";
  Main_Screen::t_tile_label.init( "Tile:", 0, 0, 715, 25 );
  Main_Screen::ti_tile.init( "lava.png", 0, 2, 760, 25, 30 );
  Main_Screen::text_inputs.push_back( &Main_Screen::ti_tile );
  Main_Screen::s_selected_tile = "lava.png";
  Main_Screen::save_button.init( 715, utils::SCREEN_HEIGHT - 37,
				 "data/images/main_screen/save_button_pressed.png",
				 "data/images/main_screen/save_button.png",
				 false );
  Main_Screen::tiles_button.init( 715, 50,
				 "data/images/main_screen/tiles_button_pressed.png",
				 "data/images/main_screen/tiles_button.png",
				 false );
  Main_Screen::one_button.init( 752, 50,
				 "data/images/main_screen/one_button_pressed.png",
				 "data/images/main_screen/one_button.png",
				 false );
  Main_Screen::two_button.init( 789, 50,
				 "data/images/main_screen/two_button_pressed.png",
				 "data/images/main_screen/two_button.png",
				 false );
  Main_Screen::climate_button.init( 826, 50,
				    "data/images/main_screen/climate_button_pressed.png",
				    "data/images/main_screen/climate_button.png",
				    false );
  
  Main_Screen::ptr_selected_surface = &map_utils::surface_tiles;
  Main_Screen::ptr_selected_array = &map_utils::array_tiles;

  map_utils::init( );
 
  return true;
}

bool Main_Screen::free()
{
  SDL_FreeSurface( Main_Screen::i_background );
  Main_Screen::t_filename_label.free();
  Main_Screen::ti_filename.free();
  Main_Screen::t_tile_label.free();
  Main_Screen::ti_tile.free();
  map_utils::free_chunks();
  Main_Screen::save_button.free();
  Main_Screen::tiles_button.free();
  Main_Screen::one_button.free();
  Main_Screen::two_button.free();
  Main_Screen::climate_button.free();
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
    else if( event.type == SDL_MOUSEMOTION )
    {
      Main_Screen::save_button.update( event.motion.x, event.motion.y );
      Main_Screen::tiles_button.update( event.motion.x, event.motion.y );
      Main_Screen::one_button.update( event.motion.x, event.motion.y );
      Main_Screen::two_button.update( event.motion.x, event.motion.y );
      Main_Screen::climate_button.update( event.motion.x, event.motion.y );
    }
    else if( event.type == SDL_MOUSEBUTTONDOWN ) 
    {
      if( event.button.button == SDL_BUTTON_LEFT )
      {
	Main_Screen::save_button.update( true );
	Main_Screen::tiles_button.update( true );
	Main_Screen::one_button.update( true );
	Main_Screen::two_button.update( true );
	Main_Screen::climate_button.update( true );
      }
    }
    else if( event.type == SDL_MOUSEBUTTONUP )
    {
      if( event.button.button == SDL_BUTTON_LEFT )
      {
	Main_Screen::save_button.update( false );
	Main_Screen::tiles_button.update( false );
	Main_Screen::one_button.update( false );
	Main_Screen::two_button.update( false );
	Main_Screen::climate_button.update( false );
	if( event.button.x < 704 )
	{
	  int x = utils::SCREEN_WIDTH - ( map_utils::camera_cx - map_utils::camera_x ) + map_utils::camera_x_trans + event.button.x;
	  int y = utils::SCREEN_HEIGHT - ( map_utils::camera_cy - map_utils::camera_y ) + map_utils::camera_y_trans + event.button.y;
	  utils::apply_surface( x - x % 32,
				y - y % 32,
				map_utils::imported_tiles[ s_selected_tile ],
				*Main_Screen::ptr_selected_surface );
	  ( *Main_Screen::ptr_selected_array )[ x / 32 ][ y / 32 ] = s_selected_tile;
	  
	}
	else
	{
	  bool clicked_a_text_input = false;
	  for( auto &text_input : text_inputs )
	  {
	    if( text_input->within( event.button.x, event.button.y ) )
	    {
	      Main_Screen::ptr_ti_selected_text_input = text_input;
	      clicked_a_text_input = true;
	    }
	  }
	  if( not clicked_a_text_input )
	  {
	    Main_Screen::ptr_ti_selected_text_input = NULL;
	  }
	  if( Main_Screen::save_button.within )
	  {
	    
	    map_utils::save_area( map_utils::camera_cx_coord, 
				  map_utils::camera_cy_coord,
				  Main_Screen::s_filename.substr( 
				    0, Main_Screen::s_filename.length() - 4 
				    ),
				  true );
	  }
	  else if( Main_Screen::tiles_button.within )
	  {
	    Main_Screen::ptr_selected_surface = &map_utils::surface_tiles;
	    Main_Screen::ptr_selected_array = &map_utils::array_tiles;
	    map_utils::blit_climate_surface = false;
	  }
	  else if( Main_Screen::one_button.within )
	  {
	    Main_Screen::ptr_selected_surface = &map_utils::surface_one;
	    Main_Screen::ptr_selected_array = &map_utils::array_one;
	    map_utils::blit_climate_surface = false;
	  }
	  else if( Main_Screen::two_button.within )
	  {
	    Main_Screen::ptr_selected_surface = &map_utils::surface_two;
	    Main_Screen::ptr_selected_array = &map_utils::array_two;
	    map_utils::blit_climate_surface = false;
	  }
	  else if( Main_Screen::climate_button.within )
	  {
	    Main_Screen::ptr_selected_surface = &map_utils::surface_climate;
	    Main_Screen::ptr_selected_array = &map_utils::array_climate;
	    map_utils::blit_climate_surface = true;
	  }
	}
      }
      else if( event.button.button == SDL_BUTTON_RIGHT )
      {
	if( event.button.x < 704 )
	{
	  int x = utils::SCREEN_WIDTH - ( map_utils::camera_cx - map_utils::camera_x ) + map_utils::camera_x_trans + event.button.x;
	  int y = utils::SCREEN_HEIGHT - ( map_utils::camera_cy - map_utils::camera_y ) + map_utils::camera_y_trans + event.button.y;
	  SDL_Rect area;
	  area.x = x - x % 32;
	  area.y = y - y % 32;
	  area.w = 32;
	  area.h = 32;
	  SDL_FillRect( *Main_Screen::ptr_selected_surface, &area, SDL_MapRGBA( (*Main_Screen::ptr_selected_surface)->format, 0x00, 0x00, 0x00, 0x00 ) );
	  ( *Main_Screen::ptr_selected_array )[ x / 32 ][ y / 32 ] = "-";
	}
      }
    }
    else if( event.type == SDL_KEYDOWN )
    {
      switch( event.key.keysym.sym )
      {
      case SDLK_ESCAPE: 
	utils::quit = true;
	break;
      case SDLK_RETURN:
	if( map_utils::imported_tiles[ Main_Screen::ti_tile.get_text( ) ] != NULL )
	{
	  Main_Screen::s_selected_tile = Main_Screen::ti_tile.get_text( );
	  Main_Screen::ptr_ti_selected_text_input = NULL;
	  Main_Screen::ti_tile.init( Main_Screen::ti_tile.get_text( ),
				     Main_Screen::ti_tile.get_size( ),
				     2,
				     Main_Screen::ti_tile.get_x( ),
				     Main_Screen::ti_tile.get_y( ),
				     Main_Screen::ti_tile.get_max_chars( ) );
	}
	else
	{
	  Main_Screen::ti_tile.init( Main_Screen::ti_tile.get_text( ),
				     Main_Screen::ti_tile.get_size( ),
				     3,
				     Main_Screen::ti_tile.get_x( ),
				     Main_Screen::ti_tile.get_y( ),
				     Main_Screen::ti_tile.get_max_chars( ) );
	}
	if( Main_Screen::ti_filename.get_text().substr( 
	      Main_Screen::ti_filename.get_text().length() - 4, 4 ).compare( ".map" ) == 0 )
	{
	  Main_Screen::s_filename = Main_Screen::ti_filename.get_text();
	  Main_Screen::ptr_ti_selected_text_input = NULL;
	  Main_Screen::ti_filename.init( Main_Screen::ti_filename.get_text( ),
					 Main_Screen::ti_filename.get_size( ),
					 2,
					 Main_Screen::ti_filename.get_x( ),
					 Main_Screen::ti_filename.get_y( ),
					 Main_Screen::ti_filename.get_max_chars( ) );  
	}
	else
	{
	  Main_Screen::ti_filename.init( Main_Screen::ti_filename.get_text( ),
					 Main_Screen::ti_filename.get_size( ),
					 3,
					 Main_Screen::ti_filename.get_x( ),
					 Main_Screen::ti_filename.get_y( ),
					 Main_Screen::ti_filename.get_max_chars( ) );  
	}
      default:
	if( Main_Screen::ptr_ti_selected_text_input != NULL )
	{
	  Main_Screen::ptr_ti_selected_text_input->append( int( event.key.keysym.mod ),
							   int( event.key.keysym.sym ) );
	}
	break;
      }
    }
  }
}

void Main_Screen::blit( SDL_Surface* screen )
{
  int x_position = -utils::SCREEN_WIDTH + ( map_utils::camera_cx - map_utils::camera_x ) - map_utils::camera_x_trans;
  int y_position = -utils::SCREEN_HEIGHT + ( map_utils::camera_cy - map_utils::camera_y ) - map_utils::camera_y_trans;
  map_utils::update_map( Main_Screen::s_filename.substr(0, Main_Screen::s_filename.length() - 4 ), true );
  utils::apply_surface( x_position, y_position, map_utils::surface_tiles, screen );
  utils::apply_surface( x_position, y_position, map_utils::surface_one, screen );
  // If there is a character, draw them here, between one and two
  utils::apply_surface( x_position, y_position, map_utils::surface_two, screen );
  if( map_utils::blit_climate_surface )
  {
    utils::apply_surface( x_position, y_position, map_utils::surface_climate, screen );
  }
  utils::apply_surface( 0, 0, Main_Screen::i_background, screen );
  Main_Screen::t_filename_label.blit( screen );
  Main_Screen::ti_filename.blit( screen );
  Main_Screen::t_tile_label.blit( screen );
  Main_Screen::ti_tile.blit( screen );
  Main_Screen::save_button.draw( screen );
  Main_Screen::tiles_button.draw( screen );
  Main_Screen::one_button.draw( screen );
  Main_Screen::two_button.draw( screen );
  Main_Screen::climate_button.draw( screen );
}
