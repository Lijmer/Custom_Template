#ifndef INCLUDED_TEST_COMPONENT_H
#define INCLUDED_TEST_COMPONENT_H

#include <Windows.h>

#include "BaseComponent.h"

class TestComponent : public BaseComponent
{
public:
  TestComponent(engine::Transform &t, game::GameObject &g) :
    BaseComponent(TEST, t, g)
  {
    QueryPerformanceFrequency(&m_ticksPS);
  }
  virtual ~TestComponent() {}
  virtual void Update();
  virtual void FixedUpdate();
private:
  LARGE_INTEGER m_lastUpdate;
  LARGE_INTEGER m_ticksPS;
};


#endif//INCLUDED_TEST_COMPONENT_H
