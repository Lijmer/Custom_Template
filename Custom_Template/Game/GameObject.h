#ifndef INCLUDED_GAME_OBJECT_H
#define INCLUDED_GAME_OBJECT_H
#include "API.h"
#include "../Custom_Template/Transform.h"
#include "../Components/ComponentList.h"

namespace game
{
  class GameObject
  {
  public:
    GAME_API GameObject() : m_name(nullptr) {}
    GAME_API ~GameObject();
    GAME_API void Update() { m_components.Update(); }
    GAME_API void FixedUpdate() { m_components.FixedUpdate(); }
    GAME_API BaseComponent* AddComponent(COMPONENT_ID ID) { return m_components.AddComponent(ID, m_transform, *this); }
    GAME_API BaseComponent* AddComponent(BaseComponent* c) { return m_components.AddComponent(c); }
    GAME_API BaseComponent* GetComponent(COMPONENT_ID ID) { return m_components.GetComponent(ID); }

    GAME_API const engine::Transform& GetTransform() const { return m_transform; }
    GAME_API engine::Transform& GetTransform() { return m_transform; }

    GAME_API void SetName(const char* name);
    GAME_API const char* GetName() const { return m_name; }
  private:
    char* m_name;
    engine::Transform m_transform;
    ComponentList m_components;
  };
}

#endif//INCLUDED_GAME_OBJECT_H
