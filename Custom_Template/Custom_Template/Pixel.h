#ifndef INCLUDED_PIXEL_H
#define INCLUDED_PIXEL_H

#pragma warning(disable : 4201) //turn off warning about nameless struct
namespace engine
{

  typedef unsigned char byte;
  union Pixel
  {
    Pixel(unsigned long c) :pixel(c) {}

    void AddBlend(Pixel color);
    void Sublend(Pixel color);

    unsigned long pixel;
    struct { byte b, g, r, a; };
  };

}

#endif//INCLUDED_PIXEL_H