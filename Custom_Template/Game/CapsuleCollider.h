#ifndef INCLUDED_CAPSULE_COLLIDER_H
#define INCLUDED_CAPSULE_COLLIDER_H

#include "Collider.h"

class CapsuleCollider : public Collider
{
  CapsuleCollider(engine::Transform &t, game::GameObject &g) :
    Collider(CAPSULE_COLLIDER, t, g, CAPSULE)
  {}
};

#endif//INCLUDED_CAPSULE_COLLIDER_H