#include "SDL/SDL.h"
#include <string>

#include "map_utils.h"
#include "utils.h"
#include "player.h"

int Player::x = utils::SCREEN_WIDTH / 2;
int Player::y = utils::SCREEN_HEIGHT / 2;
int Player::health_current = 10;
int Player::health_maximum = 10;
int Player::health_shield = 0;
int Player::speed_walk = 2;
int Player::speed_run = 3;

void Player::load( std::string character_name )
{

  // Load the character file for character_name

  map_utils::camera_speed = Player::speed_walk;
}

void Player::update()
{
  
}

void Player::blit()
{
  
}
