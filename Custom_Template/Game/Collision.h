#ifndef INCLUDED_COLLISION_H
#define INCLUDED_COLLISION_H

#include "../Utilities/float2.h"
class Collider;

class Collision
{
public:
  Collision(Collider *col1, Collider *col2,
            const float2 & collisionPoint, bool collided) :
            m_collider1(col1),
            m_collider2(col2),
            m_collisionPoint(collisionPoint),
            m_collided(collided)
  {}

  Collider & Mask1()          const { return *m_collider1; }
  Collider & Mask2()          const { return *m_collider2; }
  const float2   & CollisionPoint() const { return m_collisionPoint; }

  void Resolve();
  bool DidCollide() const { return m_collided; }

private:
  float2 m_collisionPoint;
  Collider *m_collider1, *m_collider2;
  bool m_collided;
};

#endif//INCLUDED_COLLISION_H
