#ifndef INCLUDED_RENDERER_H
#define INCLUDED_RENDERER_H
#include "API.h"

class SpriteRenderer;
class TextRenderer;

namespace engine
{
  class Bitmap;
  namespace renderer
  {
    RENDERER_API void AddRenderElement(const SpriteRenderer*);
    RENDERER_API void AddRenderElement(const TextRenderer*);
    RENDERER_API void Render(Bitmap*);
  }
}

#endif//INCLUDED_RENDERER_H