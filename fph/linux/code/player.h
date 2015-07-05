#include "SDL/SDL.h"
#include <string>

class Player
{
private:
  static int x, y;
  static int health_current, health_maximum;
  static int health_shield;
  static int speed_walk, speed_run;

public:
  static void load( std::string character_name );
  static void update();
  static void blit();
};
