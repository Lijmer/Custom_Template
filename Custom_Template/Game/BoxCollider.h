#ifndef INCLUDED_BOX_COLLIDER_H
#define INCLUDED_BOX_COLLIDER_H

#include "Collider.h"

class BoxCollider : public Collider
{
public:
  BoxCollider(engine::Transform&, game::GameObject&);
  virtual ~BoxCollider();
private:
  float m_width, height;
  
};

#endif//INCLUDED_BOX_COLLIDER_H
