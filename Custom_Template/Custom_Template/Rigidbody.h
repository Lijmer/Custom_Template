#ifndef INCLUDED_RIGIDBODY_H
#define INCLUDED_RIGIDBODY_H

#include "BaseComponent.h"
#include "float2.h"

class Rigidbody : public BaseComponent
{
public:
  Rigidbody(engine::Transform&, game::GameObject&);
  ~Rigidbody();
  virtual void Update();
private:
  float2 m_prevPos;
  float m_mass;
  float m_drag;
  bool m_useGravity;
  bool m_isKinematic;
  bool m_freezePositionX;
  bool m_freezePositionY;
};

#endif//INCLUDED_RIGIDBODY_H
