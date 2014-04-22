#include "CircleCollider.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "../Utilities/Transform.h"
#include "../Game/CollisionHandler.h"

CircleCollider::CircleCollider(engine::Transform &t, game::GameObject &g)
:Collider(CIRCLE_COLLIDER, t, g, CIRCLE)
{

}

void CircleCollider::Update()
{
  collision_handler::AddCollider(this);
}

Collision CircleCollider::CheckCollision(BoxCollider& other)
{
  return Collision(this, &other, float2(0, 0), false);
}

Collision CircleCollider::CheckCollision(CapsuleCollider& other)
{
  return Collision(this, &other, float2(0, 0), false);
}

Collision CircleCollider::CheckCollision(CircleCollider& other)
{
  float2 dist = other.m_transform.position - m_transform.position;
  float totalRadius = other.m_radius + m_radius;
  return Collision(
    this,
    &other,
    (other.m_transform.position + m_transform.position) / 2,
    dist.MagnitudeSqrd() > totalRadius * totalRadius
    );
}
