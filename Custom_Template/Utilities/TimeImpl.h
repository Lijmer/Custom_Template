#ifndef INCLUDED_TIME_IMPL_H
#define INCLUDED_TIME_IMPL_H
#include "API.h"
namespace time
{
  namespace impl
  {
    UTILITIES_API void Init();
    UTILITIES_API void Update();

    UTILITIES_API void SetFixedUpdateCallback(void(*f)());
  }
}

#endif//INCLUDED_TIME_IMPL_H
