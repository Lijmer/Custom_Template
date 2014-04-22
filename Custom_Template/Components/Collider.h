#ifndef INCLUDED_COLLIDER_H
#define INCLUDED_COLLIDER_H

#include "BaseComponent.h"
#include "Collision.h"

class BoxCollider;
class CircleCollider;
class CapsuleCollider;
class Rigidbody;

class Collider : public BaseComponent
{
public:

  enum ColliderType
  {
    BOX,
    CIRCLE,
    CAPSULE
  };

  Collider(COMPONENT_ID ID, engine::Transform &t, game::GameObject &g, ColliderType ct) :
    BaseComponent(ID, t, g),
    m_colliderType(ct)
  {}
  virtual ~Collider() {}

  Collision CheckCollision(Collider&);
  virtual Collision CheckCollision(BoxCollider&) = 0;
  virtual Collision CheckCollision(CapsuleCollider&) = 0;
  virtual Collision CheckCollision(CircleCollider&) = 0;

  virtual void Update();

  Rigidbody* GetRigidbody() { return m_rigidbody; }

  ColliderType GetType() const { return m_colliderType; }

protected:
  const ColliderType m_colliderType;
  Rigidbody* m_rigidbody;
};

#endif//INCLUDED_COLLIDER_H