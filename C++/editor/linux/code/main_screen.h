#include "SDL/SDL.h"
#include <string>
#include <map>
#include <vector>
#include "text.h"
#include "text_input.h"
#include "button.h"

#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

class Main_Screen
{
 private:
  static SDL_Surface *i_background;
  static Text t_filename_label;
  static Text_Input ti_filename;
  static std::string s_filename;
  static Text t_tile_label;
  static Text_Input ti_tile;
  static Text_Input *ptr_ti_selected_text_input;
  static std::string s_selected_tile;
  static std::vector<Text_Input*> text_inputs;
  static Button save_button;
  static Button tiles_button;
  static Button one_button;
  static Button two_button;
  static Button climate_button;
  static SDL_Surface **ptr_selected_surface;
  static std::string ( *ptr_selected_array )[32 * 3][20 * 3];
  
 public:
  static bool load();
  static bool free();
  static void logic( SDL_Event& event );
  static void blit( SDL_Surface* screen );
};

#endif
