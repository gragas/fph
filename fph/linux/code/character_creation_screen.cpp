#include "SDL/SDL.h"
#include <string>

#include "utils.h"
#include "character_creation_screen.h"

SDL_Surface *CharacterCreationScreen::i_background = NULL;

bool CharacterCreationScreen::load()
{
  // CharacterCreationScreen::i_background = utils::load_image( "data/images/character_creation_screen/background.png" );
  return true;
}

bool CharacterCreationScreen::free()
{
  SDL_FreeSurface( CharacterCreationScreen::i_background );
  return true;
}

void CharacterCreationScreen::logic( SDL_Event& event )
{
  while( SDL_PollEvent( &event ) )
  {
    if( event.type == SDL_QUIT )
    {
      utils::quit = true;
    }
  }
}

void CharacterCreationScreen::blit( SDL_Surface* screen )
{
  // utils::apply_surface( 0, 0, CharacterCreationScreen::i_background, screen );
}
