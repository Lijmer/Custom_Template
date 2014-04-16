#include "Sprite.h"
#include "Bitmap.h"
#include <cstdlib>
#include <cstring>

namespace engine
{
  Sprite::Sprite(const char* filePath, int numFrames)
  {
    Bitmap src(filePath);
    m_bmps = (Bitmap*)_aligned_malloc(sizeof(Bitmap)* numFrames, 64);
    int frameWidth = src.GetWidth() / numFrames;
    int frameHeight = src.GetHeight();
    int srcPitch = src.GetPitch();
    int dstPitch = frameWidth;
    for(int i = 0; i < numFrames; ++i)
    {
      Pixel* buffer = (Pixel*)_aligned_malloc(frameWidth * frameHeight * sizeof(Pixel),64); 
      m_bmps[i].SetBuffer(buffer);
      m_bmps[i].SetWidth(frameWidth);
      m_bmps[i].SetPitch(frameWidth);
      m_bmps[i].SetHeight(frameHeight);
      Pixel* psrc = src.GetBuffer() + i * frameWidth;
      Pixel* pdst = buffer;
      for(int y = 0; y < frameHeight; ++y, psrc += srcPitch, pdst += dstPitch)
        memcpy(pdst, psrc, frameWidth * sizeof(Pixel));
    }
  }
  Sprite::~Sprite()
  {
    for(int i = 0; i < m_frameCount; ++i)
      _aligned_free(m_bmps[i].GetBuffer());
    _aligned_free(m_bmps);
  }


  void Sprite::Draw(Bitmap* target, int x, int y, int frame) const
  {
    m_bmps[frame].Draw(target, x, y);
  }
}