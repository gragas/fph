#include "SDL/SDL.h"
#include <string>

#include "map_utils.h"
#include "utils.h"
#include "rectangle.h"
#include "player.h"

int Player::x = utils::SCREEN_WIDTH / 2;
int Player::y = utils::SCREEN_HEIGHT / 2;
int Player::disp_x = x - 10;
int Player::disp_y = y - 20;
int Player::health_current = 10;
int Player::health_maximum = 10;
int Player::health_shield = 0;
int Player::mana_current = 20;
int Player::mana_maximum = 20;
int Player::speed_walk = 2;
int Player::speed_run = 3;

Rectangle Player::rectangle_health = Rectangle(
  5, 5,
  104, 24,
  0xFF, 0xFF, 0x00, 0xFF );

Rectangle Player::rectangle_mana = Rectangle(
  5, 34,
  104, 24,
  0xFF, 0xFF, 0x00, 0xFF );

Rectangle Player::rectangle_player_placeholder = Rectangle(
  Player::disp_x, Player::disp_y,
  20, 40,
  0x00, 0x00, 0xFF, 0xFF );

void Player::load( std::string character_name )
{

  // Load the character file for character_name

  map_utils::camera_speed = Player::speed_walk;

  Player::rectangle_health.overlay(
    2, 2,
    100, 20,
    0xFF, 0x00, 0x00, 0xFF );
  Player::rectangle_mana.overlay(
    2, 2,
    100, 20,
    0x00, 0x00, 0xFF, 0xFF );
}

void Player::update()
{
  
}

void Player::blit( SDL_Surface * destination )
{
  Player::rectangle_health.blit( destination );
  Player::rectangle_mana.blit( destination );
  Player::rectangle_player_placeholder.blit( destination );
}
