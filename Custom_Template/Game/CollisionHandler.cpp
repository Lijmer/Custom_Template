#include "CollisionHandler.h" 
#include "../Game/Collider.h"
#include "../Game/Collision.h"
#include <vector>

namespace collision_handler
{
  static std::vector<Collider*> colliders;
  static std::vector<Collider*> collidersWithRigidbodies;

  void AddCollider(Collider* c)
  {
    if(c->GetRigidbody())
      collidersWithRigidbodies.push_back(c);
    else
      colliders.push_back(c);
  }
  void Update()
  {
    for(auto i = colliders.begin(), end = colliders.end(); i != end; ++i)
    {
      for(auto j = i + 1; j != end; ++j)
      {
        Collision col = (*i)->CheckCollision(**j);
        if(col.DidCollide())
          col.Resolve();
      }
      for(auto &j : collidersWithRigidbodies)
      {
        Collision col = (*i)->CheckCollision(*j);
        if(col.DidCollide())
          col.Resolve();
      }
    }
    colliders.clear();
    collidersWithRigidbodies.clear();
  }
}
