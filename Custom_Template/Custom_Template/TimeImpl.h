#ifndef INCLUDED_TIME_IMPL_H
#define INCLUDED_TIME_IMPL_H

namespace time
{
  namespace impl
  {
    void Init();
    void Update();

    void SetFixedUpdateCallback(void(*f)());
  }
}

#endif//INCLUDED_TIME_IMPL_H
