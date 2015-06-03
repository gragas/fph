#include "SDL/SDL.h"
#include <string>
#include "text.h"

#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

class Text_Input : public Text
{
private:
  int width, height;
public:
  Text_Input( );
  void init( std::string text, int size, int color, int x, int y, int max_chars );
  void append( int mod, int value );
  bool within( int x, int y );
};

#endif
