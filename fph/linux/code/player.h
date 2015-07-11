#include <string>
#include "SDL/SDL.h"
#include "rectangle.h"

class Player
{
private:
  static int x, y;
  static int health_current, health_maximum;
  static int health_shield;
  static int speed_walk, speed_run;
  static Rectangle rectangle_health;

public:
  static void load( std::string character_name );
  static void update();
  static void blit( SDL_Surface * destination );
};
