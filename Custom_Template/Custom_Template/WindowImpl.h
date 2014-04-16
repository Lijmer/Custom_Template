#ifndef INCLUDED_WINDOW_IMPL
#define INCLUDED_WINDOW_IMPL

#define GLEW_STATIC
extern "C"
{
#include "glew.h" 
}

#include <SDL.h>
//#include <SDL_syswm.h>

#include <Windows.h>

namespace engine
{
  struct WindowImpl
  {
    WindowImpl() {}
    HWND m_windowHandle;

    SDL_Surface* m_SDLWindow;

    GLuint m_framebufferTexID[2];
    GLuint m_fbPBO[2];

    Bitmap *m_frameBuffer;

    int m_width, m_height;
  };

}

#endif//INCLUDED_WINDOW_IMPL
