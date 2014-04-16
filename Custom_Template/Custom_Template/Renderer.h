#ifndef INCLUDED_RENDERER_H
#define INCLUDED_RENDERER_H

class SpriteRenderer;
class TextRenderer;

namespace engine
{
  class Bitmap;
  namespace renderer
  {
    void AddRenderElement(const SpriteRenderer*);
    void AddRenderElement(const TextRenderer*);
    void Render(Bitmap*);
  }
}

#endif//INCLUDED_RENDERER_H