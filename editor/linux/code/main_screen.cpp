#include "SDL/SDL.h"
#include <dirent.h>
#include <string>
#include <map>
#include <iostream>
#include "text.h"
#include "utils.h"
#include "text_utils.h"
#include "main_screen.h"

SDL_Surface *Main_Screen::i_background = NULL;
Text Main_Screen::t_filename_label;
Text Main_Screen::t_filename;
std::string Main_Screen::s_filename;
Text Main_Screen::t_tile_label;
Text Main_Screen::t_tile;
std::string Main_Screen::s_tile;
std::map<std::string, SDL_Surface*> Main_Screen::imported_tiles;

bool Main_Screen::load()
{
  Main_Screen::i_background = utils::load_image( "data/images/main_screen/background.png" );
  Main_Screen::t_filename_label.init( "Filename:", 0, 0, 715, 5 );
  Main_Screen::t_filename.init( "Unspecified", 0, 1, 795, 5 );
  Main_Screen::s_filename = "Unspecified";
  Main_Screen::t_tile_label.init( "Tile:", 0, 0, 715, 25 );
  Main_Screen::t_tile.init( "grass.png", 0, 1, 760, 25 );
  Main_Screen::s_tile = "grass.png";
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
	  Main_Screen::imported_tiles[ name ] = utils::load_image( "data/images/tiles/" 
								   + name );
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
  return true;
}

bool Main_Screen::free()
{
  SDL_FreeSurface( Main_Screen::i_background );
  Main_Screen::t_filename_label.free();
  Main_Screen::t_filename.free();
  Main_Screen::t_tile_label.free();
  Main_Screen::t_tile.free();
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
	
      }
    }
    else if( event.type == SDL_KEYDOWN )
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

void Main_Screen::blit( SDL_Surface* screen )
{
  utils::apply_surface( 0, 0, Main_Screen::i_background, screen );
  Main_Screen::t_filename_label.blit( screen );
  Main_Screen::t_filename.blit( screen );
  Main_Screen::t_tile_label.blit( screen );
  Main_Screen::t_tile.blit( screen );
}
