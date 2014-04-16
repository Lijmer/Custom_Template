#ifndef INCLUDED_TEST_COMPONENT_H
#define INCLUDED_TEST_COMPONENT_H

#include "BaseComponent.h"

class TestComponent : public BaseComponent
{
public:
  TestComponent(engine::Transform &t, game::GameObject &g) : BaseComponent(TEST, t, g) {}
  virtual ~TestComponent() {}
  virtual void Update();
private:
  int test1, test2, test3;
};


#endif//INCLUDED_TEST_COMPONENT_H
