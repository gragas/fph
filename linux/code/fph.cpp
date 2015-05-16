// This file borrows heavily from http://lazyfoo.net/SDL_tutorials/
// Author: Thomas Fischer, and the author of that site^

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 55;

SDL_Surface *screen = NULL;
SDL_Surface *i_splash_background = NULL;
SDL_Surface *i_splash_title = NULL;

SDL_Event event;

SDL_Surface *load_image( std::string filename )
{
  SDL_Surface* loadedImage = NULL;
  
  SDL_Surface* optimizedImage = NULL;
  
  loadedImage = IMG_Load( filename.c_str() );
  
  if( loadedImage != NULL )
  {
    optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
    SDL_FreeSurface( loadedImage );
  }
  
  return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
  SDL_Rect offset; 
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface( source, NULL, destination, &offset );
}

bool init()
{
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
  {
    return 1;
  }
  
  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
  
  // If there was an error while setting up the screen
  if( screen == NULL )
  {
    return 1;
  }
  
  SDL_WM_SetCaption( "Filius Philosophorum", NULL );
  
  // If everything initialized fine
  return true;
}

bool load_files()
{
  i_splash_background = load_image( "data/images/splash/background.png" );
  i_splash_title = load_image( "data/images/splash/title.png" );
  
  if( i_splash_background == NULL ||
      i_splash_title == NULL)
  {
    return false;
  }
  
  // If everything loaded fine
  return true;
}

void clean_up()
{
  // Free the images
  SDL_FreeSurface( i_splash_background );
  SDL_FreeSurface( i_splash_title );
  
  SDL_Quit();
}

int main( int argc, char* args [] )
{    
  bool quit = false;

  if( init() == false )
  {
    return 1;
  }
  
  if( load_files() == false)
  {
    return 1;
  }
  
  apply_surface( 0, 0, i_splash_background, screen );  
  apply_surface( 0, SCREEN_HEIGHT / 3 - i_splash_title->h / 2, i_splash_title, screen );
  
  // Update the screen
  if( SDL_Flip( screen ) == -1 )
  {
    return 1;
  }
  
  while( quit == false )
  {
    while( SDL_PollEvent( &event ) )
    {
      if( event.type == SDL_QUIT )
      {
	quit = true;
      }
    }
  }

  // Free the surfaces and quit SDL
  clean_up();
  
  return 0;
}
