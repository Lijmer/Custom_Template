#ifndef INCLUDED_TRANSFORM_H
#define INCLUDED_TRANSFORM_H


#include "Types.h"
#include "float2.h"

namespace engine
{
  struct Transform
  {
  public:
    float2 position;
    float2 scale;
    float2 center;
    float rotation;
    int z;
  };
}

#endif//INCLUDED_TRANSFORM_H
