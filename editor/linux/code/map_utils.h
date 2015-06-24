#include "SDL/SDL.h"
#include <vector>
#include <string>

#ifndef MAP_UTILS_H
#define MAP_UTILS_H

namespace map_utils
{
  extern std::vector<std::string> MAP_NAMES;
  
  extern int camera_x, camera_y; // camera offset in pixels
  extern int camera_xv, camera_yv;
  extern int camera_cx, camera_cy;
  extern int camera_x_trans, camera_y_trans;
  extern int camera_cx_coord, camera_cy_coord;
  extern int camera_velocity;

  extern int year, month, day;
  extern int temperature;
  extern bool fahrenheit;

  extern SDL_Surface* surface_tiles;
  extern SDL_Surface* surface_tiles_storage;
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
  void load_chunk( int x, int y, int x_offset, int y_offset ); // x and y chunk coordinates
  void free_chunks( );
  void update_map( );
  void update_camera( );
}

#endif