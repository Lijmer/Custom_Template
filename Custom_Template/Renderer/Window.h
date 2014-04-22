#ifndef INCLUDED_WINDOW_H
#define INCLUDED_WINDOH_H
#include "API.h"
namespace engine
{
  struct WindowImpl;
  class Bitmap;
  class Window
  {
  public:
    RENDERER_API Window(int width, int height, const char* caption);
    RENDERER_API ~Window();

    RENDERER_API Bitmap* GetFrameBuffer();

    RENDERER_API void Draw(void(*RenderFunc)(Bitmap*));
    RENDERER_API void SetCaption(const char* caption);
    RENDERER_API void ShowMessageBox(const char* message, const char* title);

    const WindowImpl* GetImplementation() const { return p; }
  private:
    WindowImpl *p;
  };
}

#endif//INCLUDED_WINDOW_H