#include "Renderer.h"
#include "../Components/SpriteRenderer.h"
#include "../Components/TextRenderer.h"
#include <vector>

#include "../Custom_Template/Transform.h"
#include "Sprite.h"
#include "Bitmap.h"
#include "SpriteDatabase.h"

namespace engine
{
  namespace renderer
  {
    static std::vector<const SpriteRenderer*> spriteRenderElements;
    static std::vector<const TextRenderer*> TextEenderElements;
    //std::multimap<int, const SpriteRenderer*> renderElements;
    void AddRenderElement(const SpriteRenderer* sprite)
    {
      spriteRenderElements.push_back(sprite);
    }
    void AddRenderElement(const TextRenderer* sprite)
    {
      TextEenderElements.push_back(sprite);
    }
    void Render(Bitmap* screen)
    {
      screen->Clear(0x000000);
      for(auto &i : spriteRenderElements)
      {
        const Transform& trans = i->GetTransform();
        const SPR::SpriteID& spriteID = i->GetSpriteID();
        Sprite& sprite = sprite_database::GetSprite(spriteID);
        sprite.Draw(screen, (int)trans.position.x, (int)trans.position.y, 0);
      }
      spriteRenderElements.clear();

      for(auto &i : TextEenderElements)
      {
        const char* string = i->GetString();
        if(string == nullptr)
          continue;
        const Transform& trans = i->GetTransform();
        screen->Print(string, (int)trans.position.x, (int)trans.position.y, 0xff00ff);
      }
      TextEenderElements.clear();
    }
  }
}
