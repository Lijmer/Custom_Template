#ifndef INCLUDED_BITMAP_H
#define INCLUDED_BITMAP_H

#include "Pixel.h"
namespace engine
{
  class Bitmap
  {
  public:
    //constructors
    Bitmap(const char *filepath);
    Bitmap(int width, int height);
    Bitmap(int width, int height, int pitch, Pixel *buffer);

    //getters
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    int GetPitch() const { return m_pitch; }
    const Pixel* GetBuffer() const { return m_buffer; }
    Pixel* GetBuffer() { return m_buffer; }

    //setters
    void SetWidth(int w) { m_width = w; }
    void SetHeight(int h) { m_height = h; }
    void SetPitch(int p) { m_pitch = p; }
    void SetBuffer(Pixel* b) { m_buffer = b; }

    //Drawing on other 
    void Draw(Bitmap* target, int x, int y) const;

    //Drawing on this
    void Line(int x1, int y1, int x2, int y2, Pixel color);
    void Clear(Pixel color);
    void Print(const char* string, int x, int y, Pixel color);




  private:
    int m_width, m_height, m_pitch;
    Pixel* m_buffer;


    // Static attributes for the buildin font
    static char s_font[51][5][5];
    static int s_transl[256];
    static bool InitCharset();
    static void SetChar(int c, char* c1, char* c2, char *c3, char *c4, char *c5);
  };

}

#endif//INCLUDED_BITMAP_H
