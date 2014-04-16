#include "ComponentFactory.h"

#include "Rigidbody.h"

#include "CapsuleCollider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"

#include "SpriteRenderer.h"
#include "TextRenderer.h"

#include "TestComponent.h"
#include "MoveComponent.h"

namespace component_factory
{
  BaseComponent* CreateComponent(COMPONENT_ID ID,
                                 engine::Transform &t,
                                 game::GameObject &g)
  {
    switch(ID)
    {
    case RIGIDBODY:       return new Rigidbody(t, g);

    //case CAPSULE_COLLIDER: return new CapsuleCollider(t, g);
    //case CIRCLE_COLLIDER:  return new CircleCollider(t, g);
    //case BOX_COLLIDER:     return new BoxCollider(t, g);

    case SPRITE_RENDERER: return new SpriteRenderer(t, g);
    case TEXT_RENDERER:   return new TextRenderer(t, g);
      
    case TEST:            return new TestComponent(t, g);
    case MOVE_COMPONENT:  return new MoveComponent(t, g);

    default:              return nullptr;
    }
  }

  void DeleteComponent(BaseComponent* c)
  {
    if(c != nullptr)
      delete c;
  }
}
