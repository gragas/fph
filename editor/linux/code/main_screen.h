#include "SDL/SDL.h"
#include <string>
#include <map>
#include "text.h"

#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

class Main_Screen
{
 private:
  static SDL_Surface *i_background;
  static Text t_filename_label;
  static Text t_filename;
  static std::string s_filename;
  static Text t_tile_label;
  static Text t_tile;
  static std::string s_tile;
  static std::map<std::string, SDL_Surface*> imported_tiles;
  static SDL_Surface *floor;
  static int camera_x, camera_y;
  
 public:
  static bool load();
  static bool free();
  static void logic( SDL_Event& event );
  static void blit( SDL_Surface* screen );
};

#endif
