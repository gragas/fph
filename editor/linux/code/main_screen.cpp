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

SDL_Surface *Main_Screen::i_background = NULL;
Text Main_Screen::t_filename_label;
Text_Input Main_Screen::ti_filename;
std::string Main_Screen::s_filename;
Text Main_Screen::t_tile_label;
Text_Input Main_Screen::ti_tile;
Text_Input *Main_Screen::ptr_ti_selected_text_input = NULL;
std::string Main_Screen::s_selected_tile;
std::vector<Text_Input*> Main_Screen::text_inputs;

bool Main_Screen::load()
{
  Main_Screen::i_background = utils::load_image( "data/images/main_screen/background.png" );
  Main_Screen::t_filename_label.init( "Filename:", 0, 0, 715, 5 );
  Main_Screen::ti_filename.init( "test.map", 0, 2, 795, 5, 30 );
  Main_Screen::text_inputs.push_back( &Main_Screen::ti_filename );
  Main_Screen::s_filename = "test.map";
  Main_Screen::t_tile_label.init( "Tile:", 0, 0, 715, 25 );
  Main_Screen::ti_tile.init( "grass.png", 0, 2, 760, 25, 30 );
  Main_Screen::text_inputs.push_back( &Main_Screen::ti_tile );
  Main_Screen::s_selected_tile = "grass.png";

  map_utils::init( );
  map_utils::load_plugins( );
  map_utils::update_map( );
 
  return true;
}

bool Main_Screen::free()
{
  SDL_FreeSurface( Main_Screen::i_background );
  Main_Screen::t_filename_label.free();
  Main_Screen::ti_filename.free();
  Main_Screen::t_tile_label.free();
  Main_Screen::ti_tile.free();
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
	if( event.button.x < 704 )
	{
	  /* if floor mode */
	  utils::apply_surface( utils::SCREEN_WIDTH + event.button.x - (event.button.x % 32),
				utils::SCREEN_HEIGHT + event.button.y - (event.button.y % 32),
				map_utils::imported_tiles[ s_selected_tile ],
				map_utils::surface_tiles );
	}
	else
	{
	  for( auto &text_input : text_inputs )
	  {
	    if( text_input->within( event.button.x, event.button.y ) )
	    {
	      Main_Screen::ptr_ti_selected_text_input = text_input;
	    }
	  }
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
  utils::apply_surface( -1 * utils::SCREEN_WIDTH, -1 * utils::SCREEN_HEIGHT, map_utils::surface_tiles, screen );
  utils::apply_surface( 0, 0, Main_Screen::i_background, screen );
  Main_Screen::t_filename_label.blit( screen );
  Main_Screen::ti_filename.blit( screen );
  Main_Screen::t_tile_label.blit( screen );
  Main_Screen::ti_tile.blit( screen );
}
