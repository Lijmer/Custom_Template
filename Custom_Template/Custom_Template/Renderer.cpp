#include "Renderer.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include <vector>

#include "Transform.h"
#include "Sprite.h"
#include "Bitmap.h"

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
        const Sprite& sprite = i->GetSprite();
        sprite.Draw(screen, (int)trans.position.x, (int)trans.position.y, 0);
      }
      spriteRenderElements.clear();

      for(auto &i : TextEenderElements)
      {
        const Transform& trans = i->GetTransform();
        const char* strings = i->GetString();
        screen->Print(strings, (int)trans.position.x, (int)trans.position.y, 0xff00ff);
      }
      TextEenderElements.clear();
    }
  }
}
