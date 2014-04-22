#ifndef INCLUDED_PIXEL_H
#define INCLUDED_PIXEL_H

#include "API.h"

#pragma warning(disable : 4201) //turn off warning about nameless struct
namespace engine
{

  typedef unsigned char byte;
  union Pixel
  {
    RENDERER_API Pixel(unsigned long c) :pixel(c) {}

    RENDERER_API void AddBlend(Pixel color);
    RENDERER_API void Sublend(Pixel color);

    unsigned long pixel;
    struct { byte b, g, r, a; };
  };

}

#endif//INCLUDED_PIXEL_H