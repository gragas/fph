#include <string>
#include "SDL/SDL.h"
#include "rectangle.h"

class Player
{
private:
  static int x, y;
  static int disp_x, disp_y;
  static int health_current, health_maximum;
  static int health_shield;
  static int mana_current, mana_maximum;
  static int speed_walk, speed_run;
  static Rectangle rectangle_health;
  static Rectangle rectangle_mana;
  static Rectangle rectangle_player_placeholder;

public:
  static void load( std::string character_name );
  static void update();
  static void blit( SDL_Surface * destination );
};
