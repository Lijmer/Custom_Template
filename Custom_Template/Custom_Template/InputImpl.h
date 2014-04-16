#ifndef INCLUDED_INPUT_IMPL_H
#define INCLUDED_INPUT_IMPL_H

#include "Types.h"

namespace input
{
  namespace impl
  {
    void OnKeyDown(SDLKey);
    void OnKeyUp(SDLKey);
    void OnMouseMotion(int x, int y);
    void OnMouseButtonDown(uint8);
    void OnMouseButtonUp(uint8);

    void OnUpdate();
  }
}

#endif//INCLUDED_INPUT_IMPL_H