#ifndef INCLUDED_SPRITE_H
#define INCLUDED_SPRITE_H

namespace engine
{
  class Bitmap;
  class Sprite
  {
  public:
    Sprite(const char* filePath, int numFrames);
    ~Sprite();

    void Draw(Bitmap* target, int x, int y, int frame) const;
  private:
    Bitmap* m_bmps;
    int m_frameCount;

    //disable these
    Sprite(Sprite&);
    void operator=(Sprite&);
  };
}

#endif//INCLUDED_SPRITE_H
