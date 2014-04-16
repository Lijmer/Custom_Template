#include "ComponentList.h"
#include "TestComponent.h"
#include "SpriteRenderer.h"
#include "MoveComponent.h"
#include "TextRenderer.h"
#include "Rigidbody.h"
#include <cassert>

BaseComponent* CreateComponent(COMPONENT_ID ID, engine::Transform &t, game::GameObject &g)
{
  switch(ID)
  {
  case RIGIDBODY: return new Rigidbody(t, g);
  case SPRITE_RENDERER:
    return new SpriteRenderer(t, g);
  case TEXT_RENDERER:
    return new TextRenderer(t, g);
  case MOVE_COMPONENT:
    return new MoveComponent(t, g);
  case TEST:
    return new TestComponent(t, g);
  default:
    return nullptr;
  }
}

ComponentList::ComponentList()
{

}
ComponentList::~ComponentList()
{
  for(auto &i : m_components)
    delete i.second;
}

BaseComponent* ComponentList::AddComponent(COMPONENT_ID ID, engine::Transform &t, game::GameObject &g)
{
  if(m_components[ID] != nullptr)
    RemoveComponent(ID);
  return (m_components[ID] = CreateComponent(ID, t ,g));
}

void ComponentList::RemoveComponent(COMPONENT_ID ID)
{
  if(m_components[ID] != nullptr)
    delete m_components[ID];
  m_components.erase(ID);
}

BaseComponent* ComponentList::GetComponent(COMPONENT_ID ID)
{
  assert(m_components[ID] != nullptr);
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
