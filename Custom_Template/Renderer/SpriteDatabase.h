#ifndef INCLUDED_SPRITE_DATABASE
#define INCLUDED_SPRITE_DATABASE
#include "API.h"
#include "SpriteID.h"

namespace engine
{
  class Sprite;
  namespace sprite_database
  {
    RENDERER_API void LoadSprite(SPR::SpriteID);
    RENDERER_API void DeleteSprite(SPR::SpriteID);
    RENDERER_API Sprite& GetSprite(SPR::SpriteID);
  }
}

#endif//INCLUDED_SPRITE_DATABASE
