#ifndef INCLUDED_BASE_COMPONENT_H
#define INCLUDED_BASE_COMPONENT_H

#include "ComponentID.h"

namespace engine { struct Transform; }
namespace game { class GameObject; }


class BaseComponent
{
public:
  BaseComponent(COMPONENT_ID ID, engine::Transform& t, game::GameObject& g) :
    m_ID(ID), m_transform(t), m_gameObject(g)
  {}
  virtual ~BaseComponent() {}

  virtual void Update() {}
  virtual void FixedUpdate() {}

  const engine::Transform& GetTransform() const { return m_transform; }
  engine::Transform& GetTransform() { return m_transform; }
  const game::GameObject& GetGameObject() const { return m_gameObject; }
  game::GameObject& GetGameObject() { return m_gameObject; }

protected:
  engine::Transform &m_transform;
  game::GameObject& m_gameObject;
private:
  COMPONENT_ID m_ID;

  //disable these
  void operator=(BaseComponent&);
  BaseComponent(BaseComponent&);
};


#endif//INCLUDED_BASE_COMPONENT_H
