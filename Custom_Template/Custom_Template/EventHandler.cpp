#include "EventHandler.h"
#include <SDL.h>
namespace engine
{
  namespace event_handler
  {
    static void(*WindowCloseCallback)() = nullptr;
    static void(*KeyDownCallback)(SDLKey) = nullptr;
    static void(*KeyUpCallback)(SDLKey) = nullptr;
    static void(*MouseMotionCallback)(int x, int y) = nullptr;
    static void(*MouseButtonDownCallback)(unsigned char) = nullptr;
    static void(*MouseButtonUpCallback)(unsigned char) = nullptr;

    void SetWindowCloseCallback(void(*Functor)())
    {
      WindowCloseCallback = Functor;
    }
    void SetKeyDownCallback(void(*Functor)(SDLKey))
    {
      KeyDownCallback = Functor;
    }
    void SetKeyUpCallback(void(*Functor)(SDLKey))
    {
      KeyUpCallback = Functor;
    }
    void SetMouseMotionCallback(void(*Functor)(int x, int y))
    {
      MouseMotionCallback = Functor;
    }
    void SetMouseButtonDownCallback(void(*Functor)(unsigned char))
    {
      MouseButtonDownCallback = Functor;
    }
    void SetMouseButtonUpCallback(void(*Functor)(unsigned char))
    {
      MouseButtonUpCallback = Functor;
    }


    void Update()
    {
      SDL_Event event;
      while(SDL_PollEvent(&event))
      {
        switch(event.type)
        {
        case SDL_QUIT:
          if(WindowCloseCallback)
            WindowCloseCallback();
          break;
        case SDL_KEYDOWN:
          if(KeyDownCallback)
            KeyDownCallback(event.key.keysym.sym);
          break;
        case SDL_KEYUP:
          if(KeyUpCallback)
            KeyUpCallback(event.key.keysym.sym);
          break;
        case SDL_MOUSEMOTION:
          if(MouseMotionCallback)
            MouseMotionCallback(event.motion.x, event.motion.y);
          break;
        case SDL_MOUSEBUTTONDOWN:
          if(MouseButtonDownCallback)
            MouseButtonDownCallback(event.button.button);
          break;
        case SDL_MOUSEBUTTONUP:
          if(MouseButtonUpCallback)
            MouseButtonUpCallback(event.button.button);
          break;
        default:
          // more info on events in SDL: http://sdl.beuc.net/sdl.wiki/SDL_Event
          break;
        }
      }
    }
  }
}
