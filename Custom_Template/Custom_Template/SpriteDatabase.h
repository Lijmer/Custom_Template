#ifndef INCLUDED_SPRITE_DATABASE
#define INCLUDED_SPRITE_DATABASE

#include "SpriteID.h"

namespace engine
{
  class Sprite;
  namespace sprite_database
  {
    void LoadSprite(SPR::SpriteID);
    void DeleteSprite(SPR::SpriteID);
    Sprite& GetSprite(SPR::SpriteID);
  }
}

#endif//INCLUDED_SPRITE_DATABASE
