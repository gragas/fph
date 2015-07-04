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
  int camera_x_trans = 0;
  int camera_y_trans = 0;
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

  SDL_Surface* surface_climate = SDL_CreateRGBSurface( SDL_HWSURFACE, 
						       utils::SCREEN_WIDTH * 3, utils::SCREEN_HEIGHT * 3,
						       32, 0x000000FF, 0x0000FF00, 0x00FF0000,
						       0xFF000000 );

  bool blit_climate_surface = false;

  std::string array_tiles[ 32 * 3 ][ 20 * 3 ];
  std::string array_one[ 32 * 3 ][ 20 * 3 ];
  std::string array_two[ 32 * 3 ][ 20 * 3 ];
  std::string array_climate[ 32 * 3 ][ 20 * 3 ];
  
  std::map<std::string, SDL_Surface*> imported_tiles;
  
  void init( )
  {
    load_plugins( );
    SDL_FillRect( surface_tiles, NULL, SDL_MapRGBA( surface_tiles->format, 0, 0, 0, 0 ) );
    SDL_FillRect( surface_tiles_storage, NULL, SDL_MapRGBA( surface_tiles_storage->format, 0, 0, 0, 0 ) );
    SDL_FillRect( surface_one, NULL, SDL_MapRGBA( surface_one->format, 0, 0, 0, 0 ) );
    SDL_FillRect( surface_two, NULL, SDL_MapRGBA( surface_two->format, 0, 0, 0, 0 ) );
    SDL_FillRect( surface_characters, NULL, SDL_MapRGBA( surface_characters->format, 0, 0, 0, 0 ) );
    SDL_FillRect( surface_climate, NULL, SDL_MapRGBA( surface_climate->format, 0, 0, 0, 0 ) );
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
    load_chunk( 0, 0, 0, 0 );
    //
    load_chunk( -1, -1, -1, -1 );
    load_chunk( 0, -1, 0, -1 );
    load_chunk( 1, -1, 1, -1 );
    load_chunk( -1, 0, -1, 0 );
    load_chunk( 1, 0, 1, 0 );
    load_chunk( -1, 1, -1, 1 );
    load_chunk( 0, 1, 0, 1 );
    load_chunk( 1, 1, 1, 1 );
    //
  }

  void load_plugins( )
  {
    std::string line;
    std::ifstream plugins_file( "plugins.options" );
    if( plugins_file.is_open() )
    {
      while( std::getline( plugins_file, line ) )
      {
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

  void load_chunk( int x, int y, int x_offset, int y_offset )
  {
    /* clear the chunk right off */
    for( int tx = 0; tx < 32; tx++ )
    {
      for( int ty = 0; ty < 20; ty++ )
      {
	array_tiles[ tx + 32 * ( x_offset + 1 ) ][ ty + 20 * ( y_offset + 1 ) ] = "-";
	array_climate[ tx + 32 * ( x_offset + 1 ) ][ ty + 20 * ( y_offset + 1 ) ] = "-";
	array_one[ tx + 32 * ( x_offset + 1 ) ][ ty + 20 * ( y_offset + 1 ) ] = "-";
	array_two[ tx + 32 * ( x_offset + 1 ) ][ ty + 20 * ( y_offset + 1 ) ] = "-";
      }
    }
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
	    else if( line.substr( 0, 4 ).compare( "One:" ) == 0 )
	    {
	      line_counter = 0;
	      mode = 1;
	      scanning = false;
	    }
	    else if( line.substr( 0, 4 ).compare( "Two:" ) == 0 )
	    {
	      line_counter = 0;
	      mode = 2;
	      scanning = false;
	    }
	    else if( line.substr( 0, 8 ).compare( "Climate:" ) == 0 )
	    {
	      line_counter = 0;
	      mode = 3;
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
		    std::string key = definitions.count( properties[ i ] ) > 0 ? definitions[ properties[ i ] ] : properties[ i ];
		    array_tiles[ i + 32 * ( x_offset + 1 ) ][ line_counter + 20 * (y_offset + 1 ) ] = key;
		    utils::apply_surface( utils::SCREEN_WIDTH * ( x_offset + 1 ) + i * 32,
					  utils::SCREEN_HEIGHT * ( y_offset + 1 ) + line_counter * 32,
					  imported_tiles[ key ],
					  surface_tiles );
		  }
		}
		else if( mode == 1 ) // one
		{
		  for( int i = 0; i < properties.size(); i++ )
		  {
		    std::string key = definitions.count( properties[ i ] ) > 0 ? definitions[ properties[ i ] ] : properties[ i ];
		    array_one[ i + 32 * ( x_offset + 1 ) ][ line_counter + 20 * (y_offset + 1 ) ] = key;
		    utils::apply_surface( utils::SCREEN_WIDTH * ( x_offset + 1 ) + i * 32,
					  utils::SCREEN_HEIGHT * ( y_offset + 1 ) + line_counter * 32,
					  imported_tiles[ key ],
					  surface_one );
		  }
		}
		else if( mode == 2 ) // two
		{
		  for( int i = 0; i < properties.size(); i++ )
		  {
		    std::string key = definitions.count( properties[ i ] ) > 0 ? definitions[ properties[ i ] ] : properties[ i ];
		    array_two[ i + 32 * ( x_offset + 1 ) ][ line_counter + 20 * (y_offset + 1 ) ] = key;
		    utils::apply_surface( utils::SCREEN_WIDTH * ( x_offset + 1 ) + i * 32,
					  utils::SCREEN_HEIGHT * ( y_offset + 1 ) + line_counter * 32,
					  imported_tiles[ key ],
					  surface_two );
		  }		  
		}
		else if( mode == 3 ) // climate
		{
		  for( int i = 0; i < properties.size(); i++ )
		  {
		    std::string key = definitions.count( properties[ i ] ) > 0 ? definitions[ properties[ i ] ] : properties[ i ];
		    array_climate[ i + 32 * ( x_offset + 1 ) ][ line_counter + 20 * ( y_offset + 1 ) ] = properties[ i ];
		    utils::apply_surface( utils::SCREEN_WIDTH * ( x_offset + 1 ) + i * 32,
					  utils::SCREEN_HEIGHT * ( y_offset + 1 ) + line_counter * 32,
					  imported_tiles[ key ],
					  surface_climate );
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
    utils::clearA( surface_tiles );
    utils::clearA( surface_one );
    utils::clearA( surface_two );
  }
  
  void update_map( std::string map_name, bool should_save_static )
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
      save_area( camera_cx_coord, camera_cy_coord, map_name, should_save_static );
      free_chunks( );
      load_area( x_coord, y_coord );
      camera_x_trans = camera_x - x_coord * utils::SCREEN_WIDTH;
      camera_y_trans = camera_y - y_coord * utils::SCREEN_HEIGHT;
      camera_cx = camera_x;
      camera_cy = camera_y;
      camera_cx_coord = x_coord;
      camera_cy_coord = y_coord;
    }
    else
    {
      
    }
  }
  
  void load_area( int x_coord, int y_coord )
  {
      load_chunk( x_coord, y_coord, 0, 0 );
      load_chunk( x_coord - 1, y_coord - 1, -1, -1 );
      load_chunk( x_coord, y_coord - 1, 0, -1 );
      load_chunk( x_coord + 1, y_coord - 1, 1, -1 );
      load_chunk( x_coord + 1, y_coord, 1, 0 );
      load_chunk( x_coord + 1, y_coord + 1, 1, 1 );
      load_chunk( x_coord, y_coord + 1, 0, 1 );
      load_chunk( x_coord - 1, y_coord + 1, -1, 1 );
      load_chunk( x_coord - 1, y_coord, -1, 0 );
  }

  void save_chunk( int x, int y, int x_offset, int y_offset, std::string map_name, bool should_save_static )
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
    std::ofstream chunk_file( "data/maps/" + map_name + "/" + string_x + string_y + ".chunk" );
    if( chunk_file.is_open( ) )
    {
      std::map<std::string, std::string> definitions; // add definitions feature to save function sometime
      
      /* Save dynamic parts of the map */
      
      /* Then save the static parts of the map if necessary */
      if( should_save_static )
      {
	chunk_file << "Tiles:\n";
	for( int ty = 0; ty < 20; ty++ )
	{
	  for( int tx = 0; tx < 32; tx++ )
	  {
	    chunk_file << ( array_tiles[ tx + 32 * ( x_offset + 1 )][ ty + 20 * ( y_offset + 1 ) ] ) << " ";
	  }
	  chunk_file << "\n";
	}
	chunk_file << "\n";
	
	chunk_file << "One:\n";
	for( int ty = 0; ty < 20; ty++ )
	{
	  for( int tx = 0; tx < 32; tx++ )
	  {
	    chunk_file << ( array_one[ tx + 32 * ( x_offset + 1 )][ ty + 20 * ( y_offset + 1 ) ] ) << " ";
	  }
	  chunk_file << "\n";
	}
	chunk_file << "\n";

	chunk_file << "Two:\n";
	for( int ty = 0; ty < 20; ty++ )
	{
	  for( int tx = 0; tx < 32; tx++ )
	  {
	    chunk_file << ( array_two[ tx + 32 * ( x_offset + 1 )][ ty + 20 * ( y_offset + 1 ) ] ) << " ";
	  }
	  chunk_file << "\n";
	}
	chunk_file << "\n";

	chunk_file << "Climate:\n";
	for( int ty = 0; ty < 20; ty++ )
	{
	  for( int tx = 0; tx < 32; tx++ )
	  {
	    chunk_file << array_climate[ tx + 32 * ( x_offset + 1 )][ ty + 20 * ( y_offset + 1 ) ] << " ";
	  }
	  chunk_file << "\n";
	}
	chunk_file << "\n";
	

	/* save the other static layers too */
	
	chunk_file.close();
      }
    }
    else
    {
      // The chunk failed to open
      std::cout << "Could not open file \"" << ("data/maps/" + map_name + "/" + string_x + string_y + ".chunk") << "\"." << std::endl;
    }
  }
  
  void save_area( int x_coord, int y_coord, std::string map_name, bool should_save_static )
  {
    save_chunk( x_coord, y_coord, 0, 0, map_name, should_save_static );
    save_chunk( x_coord - 1, y_coord - 1, -1, -1, map_name, should_save_static );
    save_chunk( x_coord, y_coord - 1, 0, -1, map_name, should_save_static );
    save_chunk( x_coord + 1, y_coord - 1, 1, -1, map_name, should_save_static );
    save_chunk( x_coord + 1, y_coord, 1, 0, map_name, should_save_static );
    save_chunk( x_coord + 1, y_coord + 1, 1, 1, map_name, should_save_static );
    save_chunk( x_coord, y_coord + 1, 0, 1, map_name, should_save_static );
    save_chunk( x_coord - 1, y_coord + 1, -1, 1, map_name, should_save_static );
    save_chunk( x_coord - 1, y_coord, -1, 0, map_name, should_save_static );
  }
}
