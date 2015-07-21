#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "text.h"
#include "utils.h"
#include "text_utils.h"
#include <string>
#include <iostream>

Text::Text(){}

void Text::init( std::string text, int size, int color, int x, int y )
{
  this->text = text;
  this->x = x;
  this->y = y;
  this->color = color;
  this->size = size;
  
  int offset = 0, width = 9, height = 18;
  switch( size )
  {
  case 0:
    offset = 0;
    width = 9;
    height = 18;
    break;
  case 1:
    offset = 65;
    width = 13;
    height = 27;
    break;
  case 2:
    offset = 130;
    width = 19;
    height = 39;
    break;
  default:
    std::cout << "Invalid size for Text object '" << text << "'." << std::endl;
    break;
  }
  switch( color )
  {
  case 0:
    offset += 0;
    break;
  case 1:
    offset += 195;
    break;
  case 2:
    offset += 390;
    break;
  case 3:
    offset += 585;
    break;
  default:
    std::cout << "Invalid color for Text object '" << text << "'." << std::endl;
    utils::quit = true;
    break;
  }

  free();
  i_text = SDL_CreateRGBSurface( SDL_HWSURFACE, width * text.length(), height,
				 32, 0x000000FF, 0x0000FF00, 0x00FF0000,
				 0xFF000000 );
  SDL_FillRect( i_text, NULL, SDL_MapRGBA( i_text->format, 0, 0, 0, 0 ) );


  for( int i = 0; i < text.length(); i++ )
  {
    int index;
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
    else if( text[i] == 58 )
    {
      index = int(text[i] + char(4)); // - 58 + 62
    }
    else if( text[i] == 59 )
    {
      index = int(text[i] + char(4)); // - 59 + 63
    }
    else if( text[i] == 46 )
    {
      index = int(text[i] + char(18)); // - 46 + 64
    }
    else
    {
      std::cout << "Invalid Text std::string " << text << std::endl;
      utils::quit = true;
    }
    utils::apply_surface( i * width, 0, text_utils::chars[index + offset], i_text );
  }
}

std::string Text::get_text()
{
  return text;
}

void Text::set_text( std::string text )
{
  this->text = text;
}

int Text::get_size()
{
  return size;
}

int Text::get_color()
{
  return color;
}

int Text::get_x()
{
  return x;
}

int Text::get_y()
{
  return y;
}

void Text::free()
{
  SDL_FreeSurface( i_text );
}

void Text::blit( SDL_Surface* screen )
{
  utils::apply_surface( x, y, i_text, screen );
}
