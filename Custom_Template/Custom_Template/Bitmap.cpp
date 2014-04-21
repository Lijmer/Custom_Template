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
    static bool runOnce = InitCharset();
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

  bool Bitmap::InitCharset()
  {
    SetChar(0, ":ooo:", "o:::o", "ooooo", "o:::o", "o:::o"); // A
    SetChar(1, "oooo:", "o:::o", "oooo:", "o:::o", "oooo:"); // B
    SetChar(2, ":oooo", "o::::", "o::::", "o::::", ":oooo"); // C
    SetChar(3, "oooo:", "o:::o", "o:::o", "o:::o", "oooo:"); // D
    SetChar(4, "ooooo", "o::::", "oooo:", "o::::", "ooooo"); // E
    SetChar(5, "ooooo", "o::::", "ooo::", "o::::", "o::::"); // F
    SetChar(6, ":oooo", "o::::", "o:ooo", "o:::o", ":ooo:"); // G
    SetChar(7, "o:::o", "o:::o", "ooooo", "o:::o", "o:::o"); // H
    SetChar(8, "::o::", "::o::", "::o::", "::o::", "::o::"); // I
    SetChar(9, ":::o:", ":::o:", ":::o:", ":::o:", "ooo::"); // J
    SetChar(10, "o::o:", "o:o::", "oo:::", "o:o::", "o::o:");// K
    SetChar(11, "o::::", "o::::", "o::::", "o::::", "ooooo");// L
    SetChar(12, "oo:o:", "o:o:o", "o:o:o", "o:::o", "o:::o");// M
    SetChar(13, "o:::o", "oo::o", "o:o:o", "o::oo", "o:::o");// N
    SetChar(14, ":ooo:", "o:::o", "o:::o", "o:::o", ":ooo:");// O
    SetChar(15, "oooo:", "o:::o", "oooo:", "o::::", "o::::");// P
    SetChar(16, ":ooo:", "o:::o", "o:::o", "o::oo", ":oooo");// Q
    SetChar(17, "oooo:", "o:::o", "oooo:", "o:o::", "o::o:");// R
    SetChar(18, ":oooo", "o::::", ":ooo:", "::::o", "oooo:");// S
    SetChar(19, "ooooo", "::o::", "::o::", "::o::", "::o::");// T
    SetChar(20, "o:::o", "o:::o", "o:::o", "o:::o", ":oooo");// U
    SetChar(21, "o:::o", "o:::o", ":o:o:", ":o:o:", "::o::");// V
    SetChar(22, "o:::o", "o:::o", "o:o:o", "o:o:o", ":o:o:");// W
    SetChar(23, "o:::o", ":o:o:", "::o::", ":o:o:", "o:::o");// X
    SetChar(24, "o:::o", "o:::o", ":oooo", "::::o", ":ooo:");// Y
    SetChar(25, "ooooo", ":::o:", "::o::", ":o:::", "ooooo");// Z
    SetChar(26, ":ooo:", "o::oo", "o:o:o", "oo::o", ":ooo:");// 0
    SetChar(27, "::o::", ":oo::", "::o::", "::o::", ":ooo:");// 1
    SetChar(28, ":ooo:", "o:::o", "::oo:", ":o:::", "ooooo");// 2
    SetChar(29, "oooo:", "::::o", "::oo:", "::::o", "oooo:");// 3
    SetChar(30, "o::::", "o::o:", "ooooo", ":::o:", ":::o:");// 4
    SetChar(31, "ooooo", "o::::", "oooo:", "::::o", "oooo:");// 5
    SetChar(32, ":oooo", "o::::", "oooo:", "o:::o", ":ooo:");// 6
    SetChar(33, "ooooo", "::::o", ":::o:", "::o::", "::o::");// 7
    SetChar(34, ":ooo:", "o:::o", ":ooo:", "o:::o", ":ooo:");// 8
    SetChar(35, ":ooo:", "o:::o", ":oooo", "::::o", ":ooo:");// 9
    SetChar(36, "::o::", "::o::", "::o::", ":::::", "::o::");// !
    SetChar(37, ":ooo:", "::::o", ":::o:", ":::::", "::o::");// ?
    SetChar(38, ":::::", ":::::", "::o::", ":::::", "::o::");// :
    SetChar(39, ":::::", ":::::", ":ooo:", ":::::", ":ooo:");// =
    SetChar(40, ":::::", ":::::", ":::::", ":::o:", "::o::");// ,
    SetChar(41, ":::::", ":::::", ":::::", ":::::", "::o::");// .
    SetChar(42, ":::::", ":::::", ":ooo:", ":::::", ":::::");// -
    SetChar(43, ":::o:", "::o::", "::o::", "::o::", ":::o:");// (
    SetChar(44, "::o::", ":::o:", ":::o:", ":::o:", "::o::");// )
    SetChar(45, ":::::", ":::::", ":::::", ":::::", ":::::");//  
    SetChar(46, ":o:o:", "ooooo", ":o:o:", "ooooo", ":o:o:");// # //fixed it :D
    SetChar(47, "::o::", "::o::", ":::::", ":::::", ":::::");// ' Tnx Ferry
    SetChar(48, "o:o:o", ":ooo:", "ooooo", ":ooo:", "o:o:o");// *
    SetChar(49, "::::o", ":::o:", "::o::", ":o:::", "o::::");// /
    char c[] = "abcdefghijklmnopqrstuvwxyz0123456789!?:=,.-() #'*/";
    int i;
    for(i = 0; i < 256; i++) s_transl[i] = 45;
    for(i = 0; i < 50; i++) s_transl[(unsigned char)c[i]] = i;
    return true;
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