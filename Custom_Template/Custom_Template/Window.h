#ifndef INCLUDED_WINDOW_H
#define INCLUDED_WINDOH_H
namespace engine
{
  struct WindowImpl;
  class Bitmap;
  class Window
  {
  public:
    Window(int width, int height, const char* caption);
    ~Window();

    Bitmap* GetFrameBuffer();

    void Draw(void (*RenderFunc)(Bitmap*));
    void SetCaption(const char* caption);
    void ShowMessageBox(const char* message, const char* title);

    const WindowImpl* GetImplementation() const { return p; }
  private:
    WindowImpl *p;
  };
}

#endif//INCLUDED_WINDOW_H