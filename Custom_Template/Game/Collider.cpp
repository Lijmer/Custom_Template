#include "Collider.h"
#include "../Game/GameObject.h"

void Collider::Update()
{
  m_rigidbody = (Rigidbody*)m_gameObject.GetComponent(RIGIDBODY);
}

Collision Collider::CheckCollision(Collider &other)
{
  switch(other.GetType())
  {
  case CAPSULE:
    return CheckCollision((CapsuleCollider&)other);
  case CIRCLE:
    return CheckCollision((CircleCollider&)other);
  case BOX:
    return CheckCollision((BoxCollider&)other);
  default:
    return Collision(nullptr, nullptr, float2(0, 0), false);
  }
}
