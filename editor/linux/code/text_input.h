#include "SDL/SDL.h"
#include <string>
#include "text.h"

#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

class Text_Input : public Text
{
private:
  int width, height, max_chars;
public:
  Text_Input( );
  void init( std::string text, int size, int color, int x, int y, int max_chars );
  void append( int mod, int value );
  bool within( int x, int y );
  int get_max_chars( );
  void set_max_chars( int max_chars );
};

#endif
