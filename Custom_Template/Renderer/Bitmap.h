#ifndef INCLUDED_BITMAP_H
#define INCLUDED_BITMAP_H

#include "Pixel.h"
namespace engine
{
  class Bitmap
  {
  public:
    //constructors
    RENDERER_API Bitmap(const char *filepath);
    RENDERER_API Bitmap(int width, int height);
    RENDERER_API Bitmap(int width, int height, int pitch, Pixel *buffer);

    //getters
    RENDERER_API int GetWidth() const { return m_width; }
    RENDERER_API int GetHeight() const { return m_height; }
    RENDERER_API int GetPitch() const { return m_pitch; }
    RENDERER_API const Pixel*  GetBuffer() const { return m_buffer; }
    RENDERER_API Pixel*  GetBuffer() { return m_buffer; }

    //setters
    RENDERER_API void SetWidth(int w) { m_width = w; }
    RENDERER_API void SetHeight(int h) { m_height = h; }
    RENDERER_API void SetPitch(int p) { m_pitch = p; }
    RENDERER_API void SetBuffer(Pixel* b) { m_buffer = b; }

    //Drawing on other 
    RENDERER_API void Draw(Bitmap* target, int x, int y) const;

    //Drawing on this
    RENDERER_API void Line(int x1, int y1, int x2, int y2, Pixel color);
    RENDERER_API void Clear(Pixel color);
    RENDERER_API void Print(const char* string, int x, int y, Pixel color);




  private:
    int m_width, m_height, m_pitch;
    Pixel* m_buffer;


    // Static attributes for the buildin font
    static char s_font[51][5][5];
    static int s_transl[256];
    RENDERER_API static bool InitCharset();
    RENDERER_API static void SetChar(int c, char* c1, char* c2, char *c3, char *c4, char *c5);
  };

}

#endif//INCLUDED_BITMAP_H
