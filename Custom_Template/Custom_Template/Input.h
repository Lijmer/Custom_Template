#ifndef INCLUDED_INPUT
#define INCLUDED_INPUT
#include <SDL_keysym.h>
namespace input
{
  bool GetKey(SDLKey);
  bool GetKeyDown(SDLKey);
  bool GetKeyUp(SDLKey);

  bool GetMouseButton(int);
  bool GetMouseButtonDown(int);
  bool GetMouseButtonUp(int);
}

#endif
