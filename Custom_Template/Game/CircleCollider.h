#ifndef INCLUDED_CIRCLE_COLLIDER_H
#define INCLUDED_CIRCLE_COLLIDER_H

#include "Collider.h"

class CircleCollider : public Collider
{
public:
  CircleCollider(engine::Transform &, game::GameObject &);

  virtual void Update();

  virtual Collision CheckCollision(BoxCollider&) final;
  virtual Collision CheckCollision(CapsuleCollider&) final;
  virtual Collision CheckCollision(CircleCollider&) final;

  void SetRadius(float r) { m_radius = r; }
  float GetRadius() const { return m_radius; }
private:
  float m_radius;
};

#endif//INCLUDED_CIRCLE_COLLIDER_H
