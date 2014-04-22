#ifndef INCLUDED_COLLISION_CHECKER_H
#define INLCUDED_COLLISION_CHECKER_H
#include "API.h"
class Collider;

namespace collision_handler
{
  void AddCollider(Collider*);
  GAME_API void Update();
}

#endif//INCLUDED_COLLISION_CHECKER_H
