#include "BaseComponent.h"


class MoveComponent : public BaseComponent
{
public:
  MoveComponent(engine::Transform &t, game::GameObject &g) :
    BaseComponent(MOVE_COMPONENT, t, g) {}
  ~MoveComponent() {}

  virtual void Update();
};
