#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "text_utils.h"
#include "utils.h"
#include <array>

std::array<SDL_Surface*, 65> text_utils::chars; // numeric, lower, upper

void text_utils::init()
{
  int counter = 0;
  std::string base_path = "data/images/fonts/inconsolata-18-9/";
  /* Load the numeric charcters */
  for(char i = 0; i <= 9; i++)
  {
    text_utils::chars[i] = utils::load_image( base_path + "numeric/"
					      + char(i + char(48)) + ".png" );
    SDL_SetAlpha( text_utils::chars[i], 0, SDL_ALPHA_OPAQUE );
    counter++;
  }
  int stop_counter = counter;
  /* Load the lower characters */
  for(char i = 0; i < 26; i++)
  {
    text_utils::chars[stop_counter + i] = utils::load_image( base_path + "lower/"
							+ char(i + char(97)) + ".png" );
    SDL_SetAlpha( text_utils::chars[stop_counter + i], 0, SDL_ALPHA_OPAQUE );
    counter++;
  }
  stop_counter = counter;
  /* Load the upper characters */
  for(char i = 0; i < 26; i++)
  {
    text_utils::chars[stop_counter + i] = utils::load_image( base_path + "upper/"
							+ char(i + char(65)) + ".png" );
    SDL_SetAlpha( text_utils::chars[stop_counter + i], 0, SDL_ALPHA_OPAQUE );
    counter++;
  }
  /* Load the special characters */
  text_utils::chars[counter] = utils::load_image( base_path + "special/"
						    + "colon.png" );
  SDL_SetAlpha( text_utils::chars[counter++], 0, SDL_ALPHA_OPAQUE );
  text_utils::chars[counter] = utils::load_image( base_path + "special/"
						    + "period.png" );
  SDL_SetAlpha( text_utils::chars[counter++], 0, SDL_ALPHA_OPAQUE );
  text_utils::chars[counter] = utils::load_image( base_path + "special/"
						    + "semicolon.png" );
  SDL_SetAlpha( text_utils::chars[counter++], 0, SDL_ALPHA_OPAQUE );
  
}
