#ifndef INCLUDED_COMPONENT_FACTORY_H
#define INCLUDED_COMPONENT_FACTORY_H

#include "ComponentID.h"

namespace engine { struct Transform; }
namespace game   { class GameObject; }
class BaseComponent;

namespace component_factory
{
  BaseComponent* CreateComponent(COMPONENT_ID,
                                 engine::Transform&,
                                 game::GameObject&);
  void DeleteComponent(BaseComponent*);
}

#endif//INCLUDED_COMPONENT_FACTORY_H
