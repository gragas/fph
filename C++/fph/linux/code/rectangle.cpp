#include "SDL/SDL.h"
#include "utils.h"
#include "rectangle.h"

Rectangle::Rectangle( int x, int y, int w, int h, 
		      Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
  this->surface = SDL_CreateRGBSurface( 
    SDL_HWSURFACE,
    w, h,
    32,
    0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000 );
  this->render();
}

void Rectangle::render()
{
  SDL_FillRect( surface, &surface->clip_rect,
		SDL_MapRGBA( surface->format, r, g, b, a ) );
}

void Rectangle::overlay(
  int x, int y,
  int w, int h,
  Uint8 r, Uint8 g, Uint8 b, Uint8 a )
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  offset.w = w;
  offset.h = h;
  SDL_FillRect( surface, &offset,
		SDL_MapRGBA( surface->format, r, g, b, a ) );
}

void Rectangle::blit( SDL_Surface * destination )
{
  utils::apply_surface( x, y, surface, destination );
}

void Rectangle::blit( SDL_Surface * destination, int x, int y )
{
  utils::apply_surface( x, y, surface, destination );
}
