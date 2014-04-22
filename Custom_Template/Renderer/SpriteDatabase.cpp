#include "SpriteDatabase.h"
#include "Sprite.h"
#include <map>

namespace engine
{
  namespace sprite_database
  {
    const char* GetSpriteFilePath(SPR::SpriteID ID)
    {
      switch(ID)
      {
      case SPR::TEST:
        return "assets/test.png";
      case SPR::MISSING:
      default:
        return "assets/missing.png";
      }
    }
    int GetNumFrames(SPR::SpriteID ID)
    {
      switch(ID)
      {
      case SPR::TEST: return 1;
      default: return 1;
      }
    }


    static std::map<SPR::SpriteID, Sprite*> sprites;

    void LoadSprite(SPR::SpriteID ID)
    {
      if(sprites[ID] == nullptr)
        sprites[ID] = new Sprite(GetSpriteFilePath(ID), GetNumFrames(ID));
    }

    void DeleteSprite(SPR::SpriteID ID)
    {
      if(sprites[ID] != nullptr)
        delete sprites[ID];
      sprites.erase(ID);
    }

    Sprite& GetSprite(SPR::SpriteID ID)
    {
      if(sprites[ID] == nullptr)
        LoadSprite(ID);
      return *sprites[ID];
    }
  }
}
