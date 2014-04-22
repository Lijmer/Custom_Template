#ifndef INCLUDED_INPUT_IMPL_H
#define INCLUDED_INPUT_IMPL_H
#include "API.h"
#include "Types.h"

namespace input
{
  namespace impl
  {
    INPUT_API void OnKeyDown(SDLKey);
    INPUT_API void OnKeyUp(SDLKey);
    INPUT_API void OnMouseMotion(int x, int y);
    INPUT_API void OnMouseButtonDown(uint8);
    INPUT_API void OnMouseButtonUp(uint8);

    INPUT_API void OnUpdate();
  }
}

#endif//INCLUDED_INPUT_IMPL_H