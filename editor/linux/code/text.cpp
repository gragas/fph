#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "text.h"
#include "utils.h"
#include "text_utils.h"
#include <string>
#include <iostream>

Text::Text(){}

void Text::init( std::string text, int x, int y )
{
  this->text = text;
  i_text = SDL_CreateRGBSurface( SDL_HWSURFACE, 9 * text.length(), 18,
				 32, 0x000000FF, 0x0000FF00, 0x00FF0000,
				 0xFF000000 );
  SDL_FillRect( i_text, NULL, SDL_MapRGBA(i_text->format, 0, 0, 0, 0) );
  this->x = x;
  this->y = y;

  for( int i = 0; i < text.length(); i++ )
  {
    int index = 0;
    if( text[i] >= 48 && text[i] <= 57 )
    {
      index = int(text[i] - char(48));
    }
    else if( text[i] >= 65 && text[i] <= 90)
    {
      index = int(text[i] - char(29)); // - 65 + 36
    }
    else if( text[i] >= 97 && text[i] <= 122 )
    {
      index = int(text[i] - char(87)); // - 97 + 10
    }
    else
    {
      std::cout << "Invalid Text std::string " << text << std::endl;
      utils::quit = true;
    }
    utils::apply_surface( i * 9, 0, text_utils::chars[index], i_text );
  }
}

std::string Text::get_text()
{
  return text;
}

void Text::free()
{
  SDL_FreeSurface( i_text );
}

void Text::blit( SDL_Surface* screen )
{
  utils::apply_surface( x, y, i_text, screen );
}
