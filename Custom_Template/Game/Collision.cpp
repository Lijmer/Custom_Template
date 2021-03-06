#include "Collision.h"

#include "CircleCollider.h"

#include "../Utilities/Constants.h"
#include "../Utilities/Transform.h"
#include "../Game/GameObject.h"
#include "Rigidbody.h"
#include "Time.h"

void ResolveCircleCircle(CircleCollider *col1, CircleCollider *col2)
{
  Rigidbody *rb1 = col1->GetRigidbody(); //col1 is guarenteed to have a rigidbody.
  Rigidbody *rb2 = col2->GetRigidbody();
  engine::Transform& tr1 = col1->GetTransform();
  engine::Transform& tr2 = col2->GetTransform();

  //const float dt = time::GetDeltaTime();
  float2 deltaPos = tr2.position - tr1.position;

  float totalRadius = col1->GetRadius() + col2->GetRadius();
  float distance = deltaPos.Magnitude();

  float factor = (distance - totalRadius) / distance;

  if(rb2)
  {
    rb1->GetVelocity() += deltaPos * factor * .5f;
    rb2->GetVelocity() -= deltaPos * factor * .5f;
  }
  else
    tr1.position += deltaPos * factor;
}

void Collision::Resolve()
{
  if(m_collider1->GetType() == Collider::CIRCLE)
  {
    if(m_collider2->GetType() == Collider::CIRCLE)
      ResolveCircleCircle(
      (CircleCollider*)m_collider1,
      (CircleCollider*)m_collider2
      );
  }
}
