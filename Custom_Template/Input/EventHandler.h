#ifndef INCLUDED_EVENT_HANDLER_H
#define INCLUDED_EVENT_HANDLER_H
#include "API.h"
#include <SDL_keysym.h>
namespace engine
{
  namespace event_handler
  {
    INPUT_API void SetWindowCloseCallback(void(*Functor)());
    INPUT_API void SetKeyDownCallback(void(*Functor)(SDLKey));
    INPUT_API void SetKeyUpCallback(void(*Functor)(SDLKey));
    INPUT_API void SetMouseMotionCallback(void(*Functor)(int x, int y));
    INPUT_API void SetMouseButtonDownCallback(void(*Functor)(unsigned char));
    INPUT_API void SetMouseButtonUpCallback(void(*Functor)(unsigned char));


    void Update();
  };
}

#endif//INCLUDED_EVENT_HANDLER_H