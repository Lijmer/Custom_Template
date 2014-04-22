#include "GameObjectFactory.h"
#include "../Components/BaseComponent.h"

#include "GameObject.h"

#include "../Input/XMLReader.h"

#include "../Components/ComponentFactory.h"

#include <map>

namespace gof
{
  std::map<std::string, COMPONENT_ID> stringToComponentID;

  bool Init()
  {
    stringToComponentID["RIGIDBODY"] = RIGIDBODY;
    stringToComponentID["CAPSULE_COLLIDER"] = CAPSULE_COLLIDER;
    stringToComponentID["CIRCLE_COLLIDER"] = CIRCLE_COLLIDER;
    stringToComponentID["BOX_COLLIDER"] = BOX_COLLIDER;
    stringToComponentID["SPRITE_RENDERER"] = SPRITE_RENDERER;
    stringToComponentID["TEXT_RENDERER"] = TEXT_RENDERER;
    stringToComponentID["TEST"] = TEST;
    stringToComponentID["MOVE_COMPONENT"] = MOVE_COMPONENT;
    return true;
  }

  game::GameObject*  CreateGameObject(const char* filepath)
  {
  
    static const bool inited = Init();
    ff::XMLTree xmlTree(filepath);
    if(xmlTree.m_root->m_name != "GameObject")
    {
      printf("Not a valid GameObject file\n");
      return nullptr;
    }
    game::GameObject *retVal = new game::GameObject();
    std::vector<ff::XMLTree::Node*> &childeren = xmlTree.m_root->m_childeren;
    for(auto &i : childeren)
    {
      BaseComponent* component = component_factory::CreateComponent(
        stringToComponentID[i->m_name],
        retVal->GetTransform(),
        *retVal
        );
      retVal->AddComponent(stringToComponentID[i->m_name]);
      component->Start();
    }
    return retVal;
  }

  game::GameObject* CreateGameObject(COMPONENT_ID* components, int size)
  {
    game::GameObject *retVal = new game::GameObject();
    for(int i = 0; i < size; ++i)
      retVal->AddComponent(components[i]);
    return retVal;
  }

  void DeleteGameObject(game::GameObject* go)
  {
    delete go;
  }
}
