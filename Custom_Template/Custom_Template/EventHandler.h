#ifndef INCLUDED_EVENT_HANDLER_H
#define INCLUDED_EVENT_HANDLER_H
#include <SDL_keysym.h>
namespace engine
{
  namespace event_handler
  {
    void SetWindowCloseCallback(void(*Functor)());
    void SetKeyDownCallback(void(*Functor)(SDLKey));
    void SetKeyUpCallback(void(*Functor)(SDLKey));
    void SetMouseMotionCallback(void(*Functor)(int x, int y));
    void SetMouseButtonDownCallback(void(*Functor)(unsigned char));
    void SetMouseButtonUpCallback(void(*Functor)(unsigned char));


    void Update();
  };
}

#endif//INCLUDED_EVENT_HANDLER_H