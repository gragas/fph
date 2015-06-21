#include "SDL/SDL.h"
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <map>
#include <math.h>
#include "map_utils.h"
#include "utils.h"

namespace map_utils
{

  std::vector<std::string> MAP_NAMES;

  int camera_x = 0;
  int camera_y = 0;
  int camera_xv = 0;
  int camera_yv = 0;
  int camera_velocity = 5;
  int camera_cx = 0;
  int camera_cy = 0;
  int camera_cx_coord = 0;
  int camera_cy_coord = 0;
  int year = 3700;
  int month = 6;
  int day = 30;
  int temperature = 75;
  bool fahrenheit = true;

  SDL_Surface* surface_tiles = SDL_CreateRGBSurface( SDL_HWSURFACE, 
						     utils::SCREEN_WIDTH * 3, utils::SCREEN_HEIGHT * 3,
						     32, 0x000000FF, 0x0000FF00, 0x00FF0000,
						     0xFF000000 );

  SDL_Surface* surface_tiles_storage = SDL_CreateRGBSurface( SDL_HWSURFACE, 
							     utils::SCREEN_WIDTH * 3, utils::SCREEN_HEIGHT * 3,
							     32, 0x000000FF, 0x0000FF00, 0x00FF0000,
							     0xFF000000 );

  SDL_Surface* surface_one = SDL_CreateRGBSurface( SDL_HWSURFACE, 
						   utils::SCREEN_WIDTH * 3, utils::SCREEN_HEIGHT * 3,
						   32, 0x000000FF, 0x0000FF00, 0x00FF0000,
						   0xFF000000 );

  SDL_Surface* surface_two = SDL_CreateRGBSurface( SDL_HWSURFACE, 
						   utils::SCREEN_WIDTH * 3, utils::SCREEN_HEIGHT * 3,
						   32, 0x000000FF, 0x0000FF00, 0x00FF0000,
						   0xFF000000 );

  SDL_Surface* surface_characters = SDL_CreateRGBSurface( SDL_HWSURFACE, 
						   utils::SCREEN_WIDTH * 3, utils::SCREEN_HEIGHT * 3,
						   32, 0x000000FF, 0x0000FF00, 0x00FF0000,
						   0xFF000000 );

  std::string array_tiles[32][20];
  std::string array_one[32][20];
  std::string array_two[32][20];
  std::string array_climate[32][20];
  
  std::map<std::string, SDL_Surface*> imported_tiles;
  
  void init( )
  {
    load_plugins( );
    SDL_FillRect( surface_tiles, NULL, SDL_MapRGBA( surface_tiles->format, 0, 0, 0, 0 ) );
    SDL_FillRect( surface_tiles_storage, NULL, SDL_MapRGBA( surface_tiles_storage->format, 0, 0, 0, 0 ) );
    SDL_FillRect( surface_one, NULL, SDL_MapRGBA( surface_one->format, 0, 0, 0, 0 ) );
    SDL_FillRect( surface_two, NULL, SDL_MapRGBA( surface_two->format, 0, 0, 0, 0 ) );
    SDL_FillRect( surface_characters, NULL, SDL_MapRGBA( surface_characters->format, 0, 0, 0, 0 ) );
  /* Be sure to set the alpha of source surfaces when blitting onto floor
     Use this:
     SDL_SetAlpha( source, 0, SDL_ALPHA_OPAQUE );
  */
    /* Partial thanks to stackoverflow */
    DIR *dir;
    struct dirent *ent;
    if ( (dir = opendir("data/images/tiles")) != NULL )
    {
      while( (ent = readdir( dir )) != NULL )
      {
	std::string name = ent->d_name;
	if( name.length() > 4 )
	{
	  if( name.substr( name.length() - 4, 4 ).compare( ".png" ) == 0 )
	  {
	    imported_tiles[ name ] = utils::load_image( "data/images/tiles/" 
							+ name );
	    SDL_SetAlpha( imported_tiles[ name ], 0, SDL_ALPHA_OPAQUE );
	  }
	}
      }
      closedir( dir );
    }
    else
    {
      std::cout << "ERROR: Folder \"data/images/tiles\" could not be explored." << std::endl;
      utils::quit = true;
    }
    load_chunk( 0, 0 );
    //
    load_chunk( -1, -1 );
    load_chunk( 0, -1 );
    load_chunk( 1, -1 );
    load_chunk( -1, 0 );
    load_chunk( 1, 0 );
    load_chunk( -1, 1 );
    load_chunk( 0, 1 );
    load_chunk( 1, 1 );
    //
  }

  void load_plugins( )
  {
    std::string line;
    std::ifstream plugins_file( "plugins.options" );
    if( plugins_file.is_open() )
    {
      std::cout << "\nPlugins List:" << std::endl;
      while( std::getline( plugins_file, line ) )
      {
	std::cout << line << std::endl;
	MAP_NAMES.push_back( line.substr( 0, line.length() - 4 ) );
      }
      plugins_file.close();
    }
    else
    {
      std::cout << "Unable to open file \"plugins.options\"" << std::endl;
      utils::quit = true;
    }
  }

  void load_chunk( int x, int y )
  {
    std::string x_flag, y_flag;
    if( x < 0 )
    {
      x_flag = "xa";
    }
    else
    {
      x_flag = "x";
    }
    if( y < 0 )
    {
      y_flag = "ya";
    }
    else
    {
      y_flag = "y";
    }
    std::string string_x = x_flag + std::to_string( std::abs( x ) );
    std::string string_y = y_flag + std::to_string( std::abs( y ) );
    bool chunk_found = false;
    for( int i = 0; i < MAP_NAMES.size(); i++ )
    {
      std::string map_name = MAP_NAMES[i];
      std::string line;
      std::ifstream chunk_file( "data/maps/" + map_name + "/" + string_x + string_y + ".chunk" );
      if( chunk_file.is_open() )
      {
	chunk_found = true;
	std::map<std::string, std::string> definitions;
	bool scanning = true;
	int line_counter = 0, mode = 0; // modes { 0 : Tiles, 1 : One, 2 : Two, 3 : Climate }
	while( std::getline( chunk_file, line ) )
	{
	  if( scanning )
	  {
	    if( line.substr( 0, 6 ).compare( "define" ) == 0 )
	    {
	      std::string source = line.substr( 7 );
	      int source_length = 1;
	      while( source.at( source_length ) != ' ' )
	      {
		source_length++;
	      }
	      std::string key = source.substr( source_length + 4 );
	      source = source.substr( 0, source_length );
	      definitions[ key ] = source;
	    }
	    else if( line.substr( 0, 6 ).compare( "Tiles:" ) == 0 )
	    {
	      line_counter = 0;
	      mode = 0;
	      scanning = false;
	    }
	  }
	  else
	  {
	    if( line_counter < utils::SCREEN_HEIGHT / 32 )
	    {
		std::istringstream buffer( line );
		std::istream_iterator< std::string > beginning( buffer ), end;
		std::vector< std::string > properties( beginning, end );
		if( mode == 0 ) // tiles
		{
		  for( int i = 0; i < properties.size(); i++ )
		  {
		    array_tiles[ i ][ line_counter ] = properties[ i ];
		    utils::apply_surface( utils::SCREEN_WIDTH * ( x + 1 ) - camera_x + i * 32,
					  utils::SCREEN_HEIGHT * ( y + 1 ) - camera_y + line_counter * 32,
					  imported_tiles[ definitions[ properties[ i ] ] ],
					  surface_tiles );
		  }
		}
		else if( mode == 3 ) // climate
		{
		  for( int i = 0; i < properties.size(); i++ )
		  {
		    array_climate[ i ][ line_counter ] = properties[ i ];
		  }
		}
		line_counter++;
	    }
	    else
	    {
	      scanning = true;
	    }
	  }
	}
	break;
      }
      else
      {
	// chunk not found within this plugin
      }
    }
    if( !chunk_found ) // chunk not found within any plugin
    {

    }
  }

  void free_chunks( )
  {
    utils::clear( surface_tiles );
    utils::clear( surface_one );
    utils::clear( surface_two );
  }
  
  void update_map( )
  {
    Uint8 *keystates = SDL_GetKeyState( NULL );
    if( keystates[ SDLK_w ] )
    {
      camera_yv = -1 * camera_velocity;
    }
    if( keystates[ SDLK_s ] )
    {
      camera_yv = camera_velocity;
    }
    if( keystates[ SDLK_d ] )
    {
      camera_xv = camera_velocity;
    }
    if( keystates[ SDLK_a ] )
    {
      camera_xv = -1 * camera_velocity;
    }
    if( not keystates[ SDLK_w ] and not keystates[ SDLK_s ] )
    {
      camera_yv = 0;
    }
    if( not keystates[ SDLK_d ] and not keystates[ SDLK_a ] )
    {
      camera_xv = 0;
    }

    camera_x += camera_xv;
    camera_y += camera_yv;

    int x_modifier = 0, y_modifier = 0;
    if( camera_x + utils::SCREEN_WIDTH / 2 < 0 )
    {
      x_modifier = -1;
    }
    if( camera_y + utils::SCREEN_HEIGHT / 2 < 0 )
    {
      y_modifier = -1;
    }
    int x_coord = ( camera_x + utils::SCREEN_WIDTH / 2 ) / utils::SCREEN_WIDTH + x_modifier;
    int y_coord = ( camera_y + utils::SCREEN_HEIGHT / 2 ) / utils::SCREEN_HEIGHT + y_modifier;

    if( camera_cx_coord != x_coord or camera_cy_coord != y_coord )
    {
      free_chunks( );
      load_chunk( x_coord, y_coord );
      load_chunk( x_coord - 1, y_coord - 1 );
      load_chunk( x_coord, y_coord - 1 );
      load_chunk( x_coord + 1, y_coord - 1 );
      load_chunk( x_coord + 1, y_coord );
      load_chunk( x_coord + 1, y_coord + 1 );
      load_chunk( x_coord, y_coord + 1 );
      load_chunk( x_coord - 1, y_coord + 1 );
      load_chunk( x_coord - 1, y_coord );
      camera_cx = camera_x;
      camera_cy = camera_y;
      camera_cx_coord = x_coord;
      camera_cy_coord = y_coord;
    }
    else
    {
      
    }
  }
  
}
