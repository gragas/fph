#include "SDL/SDL.h"
#include <string>
#include <iostream>
#include "text.h"
#include "text_input.h"

Text_Input::Text_Input( ) : Text( ){}

void Text_Input::init( std::string text, int size, int color, int x, int y, int max_chars )
{
  Text::init( text, size, color, x, y );
  int width, height;
  this->max_chars = max_chars;
  switch( size )
  {
  case 0:
    width = 9;
    height = 18;
  case 1:
    width = 13;
    height = 27;
  case 2:
    width = 19;
    height = 39;
  }
  this->width = max_chars * width;
  this->height = height;
}

void Text_Input::append( int mod, int value )
{
  std::string text = "";
  if( mod & KMOD_SHIFT)
  {
    if( value <= 122 and value >= 97 )
    {
      text += char( value - 32 );
    }
    else if( value == 59 )
    {
      text += char( 58 );
    }
  }
  else if( (value <= 59 and value >= 48) or (value == 46) or (value <= 122 and value >= 97) )
  {
    text += char( value );
  }
  if( text.compare("") != 0 )
  {
    Text::set_text( Text::get_text() + text );
    Text::init( Text::get_text(), Text::get_size(), Text::get_color(), Text::get_x(), Text::get_y() );
  }
  else if( value == int( SDLK_BACKSPACE ) and Text::get_text().length() > 0 )
  {
    Text::set_text( Text::get_text().substr(0, Text::get_text().length() - 1 ) );
    Text::init( Text::get_text(), Text::get_size(), Text::get_color(), Text::get_x(), Text::get_y() );
  }
  if( value != int( SDLK_RETURN ) )
  {
    init( get_text(), get_size(), 0, get_x(), get_y(), max_chars );
  }
}

bool Text_Input::within( int x, int y )
{
  return x >= Text::get_x() and x <= Text::get_x() + width and
    y >= Text::get_y() and y <= Text::get_y() + height;
}

int Text_Input::get_max_chars( )
{
  return max_chars;
}

void Text_Input::set_max_chars( int max_chars )
{
  this->max_chars = max_chars;
}
