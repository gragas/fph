#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "text_utils.h"
#include "utils.h"
#include <array>

std::array<SDL_Surface*, 62> text_utils::chars; // numeric, lower, upper

void text_utils::init()
{
  std::string base_path = "data/images/fonts/liberation-mono-24-16/";
  /* Load the numeric charcters */
  for(char i = 0; i <= 9; i++)
  {
    text_utils::chars[i] = utils::load_image( base_path + "numeric/"
					      + char(i + char(48)) + ".png" );
    SDL_SetAlpha( text_utils::chars[i], 0, SDL_ALPHA_OPAQUE );
  }
  /* Load the lower characters */
  for(char i = 0; i < 26; i++)
  {
    text_utils::chars[10 + i] = utils::load_image( base_path + "lower/"
						   + char(i + char(97)) + ".png" );
    SDL_SetAlpha( text_utils::chars[10 + i], 0, SDL_ALPHA_OPAQUE );
  }
  /* Load the upper characters */
  for(char i = 0; i < 26; i++)
  {
    text_utils::chars[36 + i] = utils::load_image( base_path + "upper/"
						   + char(i + char(65)) + ".png" );
    SDL_SetAlpha( text_utils::chars[36 + i], 0, SDL_ALPHA_OPAQUE );
  }
}
