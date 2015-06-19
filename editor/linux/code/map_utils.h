#include "SDL/SDL.h"
#include <vector>
#include <string>

#ifndef MAP_UTILS_H
#define MAP_UTILS_H

namespace map_utils
{
  extern std::vector<std::string> MAP_NAMES;
  
  extern int camera_x, camera_y; // camera offset in pixels

  extern int year, month, day;
  extern int temperature;
  extern bool fahrenheit;
  extern bool load_left, load_right, load_up, load_down;

  extern SDL_Surface* surface_tiles;
  extern SDL_Surface* surface_one;
  extern SDL_Surface* surface_two;
  extern SDL_Surface* surface_characters;
  
  extern std::string array_tiles[32][20];
  extern std::string array_one[32][20];
  extern std::string array_two[32][20];
  extern std::string array_climate[32][20];

  extern std::map<std::string, SDL_Surface*> imported_tiles;

  void init( );
  void load_plugins( );
  void load_chunk( int x, int y ); // x and y chunk coordinates
  void free_chunks( );
  void update_map( );
}

#endif
