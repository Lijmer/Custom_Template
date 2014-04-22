#ifndef INCLUDED_COMPONENT_LIST_H
#define INCLUDED_COMPONENT_LIST_H

#include <map>
#include "ComponentID.h"
class BaseComponent;
namespace engine { struct Transform; }
namespace game { class GameObject; }
class ComponentList
{
public:
  ComponentList();
  ~ComponentList();
  BaseComponent* AddComponent(COMPONENT_ID, engine::Transform&, game::GameObject&);
  BaseComponent* AddComponent(BaseComponent*);
  void RemoveComponent(COMPONENT_ID);
  BaseComponent* GetComponent(COMPONENT_ID);

  void Update();
  void FixedUpdate();

private:
  std::map<COMPONENT_ID, BaseComponent*> m_components;
};

#endif//  INCLUDED_COMPONENT_LIST_H
