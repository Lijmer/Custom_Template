#include "Bitmap.h"
#include <cstdlib>
#include <algorithm>
#include <FreeImage.h>

namespace engine
{
  char Bitmap::s_font[51][5][5];
  int Bitmap::s_transl[256];

  Bitmap::Bitmap(const char *filepath)
  {
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    fif = FreeImage_GetFileType(filepath, 0);
    if(fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(filepath);
    FIBITMAP* tmp = FreeImage_Load(fif, filepath);
    FIBITMAP* dib = FreeImage_ConvertTo32Bits(tmp);
    FreeImage_Unload(tmp);
    m_width = m_pitch = FreeImage_GetWidth(dib);
    m_height = FreeImage_GetHeight(dib);
    m_buffer = (Pixel*)_aligned_malloc(m_width * m_height * sizeof(Pixel), 64);
    for(int y = 0; y < m_height; y++)
    {
      unsigned char* line = FreeImage_GetScanLine(dib, m_height - 1 - y);
      memcpy(m_buffer + y * m_pitch, line, m_width * sizeof(Pixel));
    }
    FreeImage_Unload(dib);
  }
  Bitmap::Bitmap(int width, int height) :
    m_width(width),
    m_height(height),
    m_pitch(width),
    m_buffer((Pixel*)_aligned_malloc(m_width * m_height * sizeof(Pixel), 64))
  {}

  Bitmap::Bitmap(int width, int height, int pitch, Pixel *buffer) :
    m_width(width),
    m_height(height),
    m_pitch(pitch),
    m_buffer(buffer)
  {}

  void Bitmap::Clear(Pixel color)
  {
    int size = (m_width * m_height) >> 3;
    Pixel* buffer = m_buffer;
    for(int i = 0; i < size; ++i)
    {
      *buffer++ = color, *buffer++ = color, *buffer++ = color, *buffer++ = color;
      *buffer++ = color, *buffer++ = color, *buffer++ = color, *buffer++ = color;
    }
  }

  void Bitmap::Print(const char* string, int x, int y, Pixel color)
  {
    Pixel* t = m_buffer + x + y * m_pitch;
    for(unsigned i = 0, len = strlen(string); i < len; ++i)
    {
      int pos;
      if((string[i] >= 'A') && (string[i] <= 'Z'))
        pos = s_transl[(string[i] - ('A' - 'a'))];
      else
        pos = s_transl[string[i]];

      Pixel* a = t;
      char* c = (char*)s_font[pos];
      for(int y = 0; y < 5; y++, a += m_pitch)
      {
        for(int x = 0; x < 5; x++)
          if(*c++ == 'o') a[x] = color, a[x + m_pitch] = 0;
      }
      t += 6;
    }
  }


  void Bitmap::SetChar(int c, char* c1, char* c2, char *c3, char *c4, char *c5)
  {
    memcpy(s_font[c][0], c1, 5);
    memcpy(s_font[c][1], c2, 5);
    memcpy(s_font[c][2], c3, 5);
    memcpy(s_font[c][3], c4, 5);
    memcpy(s_font[c][4], c5, 5);
  }

  void Bitmap::InitCharset()
  {
    SetChar(0, ":ooo:", "o:::o", "ooooo", "o:::o", "o:::o");
    SetChar(1, "oooo:", "o:::o", "oooo:", "o:::o", "oooo:");
    SetChar(2, ":oooo", "o::::", "o::::", "o::::", ":oooo");
    SetChar(3, "oooo:", "o:::o", "o:::o", "o:::o", "oooo:");
    SetChar(4, "ooooo", "o::::", "oooo:", "o::::", "ooooo");
    SetChar(5, "ooooo", "o::::", "ooo::", "o::::", "o::::");
    SetChar(6, ":oooo", "o::::", "o:ooo", "o:::o", ":ooo:");
    SetChar(7, "o:::o", "o:::o", "ooooo", "o:::o", "o:::o");
    SetChar(8, "::o::", "::o::", "::o::", "::o::", "::o::");
    SetChar(9, ":::o:", ":::o:", ":::o:", ":::o:", "ooo::");
    SetChar(10, "o::o:", "o:o::", "oo:::", "o:o::", "o::o:");
    SetChar(11, "o::::", "o::::", "o::::", "o::::", "ooooo");
    SetChar(12, "oo:o:", "o:o:o", "o:o:o", "o:::o", "o:::o");
    SetChar(13, "o:::o", "oo::o", "o:o:o", "o::oo", "o:::o");
    SetChar(14, ":ooo:", "o:::o", "o:::o", "o:::o", ":ooo:");
    SetChar(15, "oooo:", "o:::o", "oooo:", "o::::", "o::::");
    SetChar(16, ":ooo:", "o:::o", "o:::o", "o::oo", ":oooo");
    SetChar(17, "oooo:", "o:::o", "oooo:", "o:o::", "o::o:");
    SetChar(18, ":oooo", "o::::", ":ooo:", "::::o", "oooo:");
    SetChar(19, "ooooo", "::o::", "::o::", "::o::", "::o::");
    SetChar(20, "o:::o", "o:::o", "o:::o", "o:::o", ":oooo");
    SetChar(21, "o:::o", "o:::o", ":o:o:", ":o:o:", "::o::");
    SetChar(22, "o:::o", "o:::o", "o:o:o", "o:o:o", ":o:o:");
    SetChar(23, "o:::o", ":o:o:", "::o::", ":o:o:", "o:::o");
    SetChar(24, "o:::o", "o:::o", ":oooo", "::::o", ":ooo:");
    SetChar(25, "ooooo", ":::o:", "::o::", ":o:::", "ooooo");
    SetChar(26, ":ooo:", "o::oo", "o:o:o", "oo::o", ":ooo:");
    SetChar(27, "::o::", ":oo::", "::o::", "::o::", ":ooo:");
    SetChar(28, ":ooo:", "o:::o", "::oo:", ":o:::", "ooooo");
    SetChar(29, "oooo:", "::::o", "::oo:", "::::o", "oooo:");
    SetChar(30, "o::::", "o::o:", "ooooo", ":::o:", ":::o:");
    SetChar(31, "ooooo", "o::::", "oooo:", "::::o", "oooo:");
    SetChar(32, ":oooo", "o::::", "oooo:", "o:::o", ":ooo:");
    SetChar(33, "ooooo", "::::o", ":::o:", "::o::", "::o::");
    SetChar(34, ":ooo:", "o:::o", ":ooo:", "o:::o", ":ooo:");
    SetChar(35, ":ooo:", "o:::o", ":oooo", "::::o", ":ooo:");
    SetChar(36, "::o::", "::o::", "::o::", ":::::", "::o::");
    SetChar(37, ":ooo:", "::::o", ":::o:", ":::::", "::o::");
    SetChar(38, ":::::", ":::::", "::o::", ":::::", "::o::");
    SetChar(39, ":::::", ":::::", ":ooo:", ":::::", ":ooo:");
    SetChar(40, ":::::", ":::::", ":::::", ":::o:", "::o::");
    SetChar(41, ":::::", ":::::", ":::::", ":::::", "::o::");
    SetChar(42, ":::::", ":::::", ":ooo:", ":::::", ":::::");
    SetChar(43, ":::o:", "::o::", "::o::", "::o::", ":::o:");
    SetChar(44, "::o::", ":::o:", ":::o:", ":::o:", "::o::");
    SetChar(45, ":::::", ":::::", ":::::", ":::::", ":::::");
    SetChar(46, "ooooo", "ooooo", "ooooo", "ooooo", "ooooo");
    SetChar(47, "::o::", "::o::", ":::::", ":::::", ":::::"); // Tnx Ferry
    SetChar(48, "o:o:o", ":ooo:", "ooooo", ":ooo:", "o:o:o");
    SetChar(49, "::::o", ":::o:", "::o::", ":o:::", "o::::");
    char c[] = "abcdefghijklmnopqrstuvwxyz0123456789!?:=,.-() #'*/";
    int i;
    for(i = 0; i < 256; i++) s_transl[i] = 45;
    for(i = 0; i < 50; i++) s_transl[(unsigned char)c[i]] = i;
  }

  void Bitmap::Draw(Bitmap *target, int ax, int ay) const
  {
    Pixel* src = m_buffer;
    Pixel* dst = target->GetBuffer();

    int srcWidth = m_width;
    int srcHeight = m_height;
    const int srcPitch = m_pitch;
    const int dstWidth = target->GetWidth();
    const int dstHeight = target->GetHeight();
    const int dstPitch = target->GetPitch();

    if((srcWidth + ax) > dstWidth) srcWidth = dstWidth - ax;
    if((srcHeight + ay) > dstHeight) srcHeight = dstHeight - ay;
    if(ax < 0) src -= ax, srcWidth += ax, ax = 0;
    if(ay < 0) src -= ay * srcPitch, srcHeight += ay, ay = 0;

    dst += ay * dstPitch + ax;

    for(int y = 0; y < srcHeight; ++y, dst += dstPitch, src += srcPitch)
    {
      memcpy(dst, src, srcWidth * sizeof(Pixel));
      //for(int x = 0; x < srcWidth; ++x)
        //if(src[x].pixel & 0xffffff)
         // dst[x] = src[x];
    }
      //memcpy(dst, src, srcWidth * sizeof(Pixel));
  }

}