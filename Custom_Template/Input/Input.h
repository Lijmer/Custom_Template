#ifndef INCLUDED_INPUT
#define INCLUDED_INPUT
#include "API.h"
#include <SDL_keysym.h>
namespace input
{
  INPUT_API bool GetKey(SDLKey);
  INPUT_API bool GetKeyDown(SDLKey);
  INPUT_API bool GetKeyUp(SDLKey);

  INPUT_API bool GetMouseButton(int);
  INPUT_API bool GetMouseButtonDown(int);
  INPUT_API bool GetMouseButtonUp(int);
}

#endif
