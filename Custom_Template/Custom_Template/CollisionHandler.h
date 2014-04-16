#ifndef INCLUDED_COLLISION_CHECKER_H
#define INLCUDED_COLLISION_CHECKER_H

class Collider;

namespace collision_handler
{
  void AddCollider(Collider*);
  void Update();
}

#endif//INCLUDED_COLLISION_CHECKER_H
