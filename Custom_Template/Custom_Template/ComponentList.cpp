#include "ComponentList.h"
#include "ComponentFactory.h"
#include "BaseComponent.h"
#include <cassert>

ComponentList::ComponentList()
{

}
ComponentList::~ComponentList()
{
  for(auto &i : m_components)
    delete i.second;
}

BaseComponent* ComponentList::AddComponent(COMPONENT_ID ID,
                                           engine::Transform &t,
                                           game::GameObject &g)
{
  assert(ID >= 0 && ID < COMPONENT_ID_LIST_SIZE && "Not a valid componentID");
  //assert(ID >= 0 && ID < COMPONENT_ID_LIST_SIZE, "banana");
  if(m_components[ID] != nullptr)
    RemoveComponent(ID);
  return (m_components[ID] = component_factory::CreateComponent(ID, t, g));
}

BaseComponent* ComponentList::AddComponent(BaseComponent* c)
{
  if(m_components[c->GetID()] != nullptr)
    RemoveComponent(c->GetID());
  return (m_components[c->GetID()] = c);
}

void ComponentList::RemoveComponent(COMPONENT_ID ID)
{
  component_factory::DeleteComponent(m_components[ID]);
  m_components.erase(ID);
}

BaseComponent* ComponentList::GetComponent(COMPONENT_ID ID)
{
  assert(m_components[ID] != nullptr && "Can't get a non existing component.");
  return m_components[ID];
}

void ComponentList::Update()
{
  for(auto &i : m_components)
    i.second->Update();
}

void ComponentList::FixedUpdate()
{
  for(auto &i : m_components)
    i.second->FixedUpdate();
}
