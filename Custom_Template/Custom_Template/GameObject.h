#ifndef INCLUDED_GAME_OBJECT_H
#define INCLUDED_GAME_OBJECT_H

#include "Transform.h"
#include "ComponentList.h"

namespace game
{
  class GameObject
  {
  public:
    GameObject() : m_name(nullptr) {}
    ~GameObject();
    void Update() { m_components.Update(); }
    void FixedUpdate() { m_components.FixedUpdate(); }
    BaseComponent* AddComponent(COMPONENT_ID ID) { return m_components.AddComponent(ID, m_transform, *this); }
    BaseComponent* GetComponent(COMPONENT_ID ID) { return m_components.GetComponent(ID); }

    const engine::Transform& GetTransform() const { return m_transform; }
    engine::Transform& GetTransform() { return m_transform; }

    void SetName(const char* name);
    const char* GetName() const { return m_name; }
  private:
    char* m_name;
    engine::Transform m_transform;
    ComponentList m_components;
  };
}

#endif//INCLUDED_GAME_OBJECT_H
