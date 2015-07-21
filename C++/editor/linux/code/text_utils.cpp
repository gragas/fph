#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "text_utils.h"
#include "utils.h"
#include <array>
#include <string>
#include <iostream>

std::array<SDL_Surface*, 780> text_utils::chars; // numeric, lower, upper
int text_utils::counter = 0;

void text_utils::load( std::string path )
{
  int stop_counter = text_utils::counter;
  std::string base_path = "data/images/fonts/inconsolata/" + path + "/";
  /* Load the numeric charcters */
  for(char i = 0; i <= 9; i++)
  {
    text_utils::chars[text_utils::counter + i] = utils::load_image( base_path + "numeric/"
					      + char(i + char(48)) + ".png" );
    SDL_SetAlpha( text_utils::chars[text_utils::counter + i], 0, SDL_ALPHA_OPAQUE );
    text_utils::counter++;
  }
  stop_counter = text_utils::counter;
  /* Load the lower characters */
  for(char i = 0; i < 26; i++)
  {
    text_utils::chars[stop_counter + i] = utils::load_image( base_path + "lower/"
							+ char(i + char(97)) + ".png" );
    SDL_SetAlpha( text_utils::chars[stop_counter + i], 0, SDL_ALPHA_OPAQUE );
    text_utils::counter++;
  }
  stop_counter = text_utils::counter;
  /* Load the upper characters */
  for(char i = 0; i < 26; i++)
  {
    text_utils::chars[stop_counter + i] = utils::load_image( base_path + "upper/"
							+ char(i + char(65)) + ".png" );
    SDL_SetAlpha( text_utils::chars[stop_counter + i], 0, SDL_ALPHA_OPAQUE );
    text_utils::counter++;
  }
  /* Load the special characters */
  text_utils::chars[text_utils::counter] = utils::load_image( base_path + "special/"
						    + "colon.png" );
  SDL_SetAlpha( text_utils::chars[text_utils::counter++], 0, SDL_ALPHA_OPAQUE );
  text_utils::chars[text_utils::counter] = utils::load_image( base_path + "special/"
						    + "semicolon.png" );
  SDL_SetAlpha( text_utils::chars[text_utils::counter++], 0, SDL_ALPHA_OPAQUE );
  text_utils::chars[text_utils::counter] = utils::load_image( base_path + "special/"
						    + "period.png" );
  SDL_SetAlpha( text_utils::chars[text_utils::counter++], 0, SDL_ALPHA_OPAQUE );
}

void text_utils::init()
{
  text_utils::load("black/small");
  text_utils::load("black/medium");  
  text_utils::load("black/large");  
  text_utils::load("cornflower/small");  
  text_utils::load("cornflower/medium");  
  text_utils::load("cornflower/large");
  text_utils::load("green/small");
  text_utils::load("green/medium");
  text_utils::load("green/large");
  text_utils::load("red/small");
  text_utils::load("red/medium");
  text_utils::load("red/large");
}
