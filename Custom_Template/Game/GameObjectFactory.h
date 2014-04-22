#ifndef INCLUDED_GAME_OBJECT_FACTORY_H
#define INCLUDED_GAME_OBJECT_FACTORY_H
#include "API.h"
namespace game { class GameObject; }
enum COMPONENT_ID;
namespace gof
{
  GAME_API game::GameObject* CreateGameObject(const char *filepath);
  GAME_API game::GameObject* CreateGameObject(COMPONENT_ID *ComponentIDList, int size);

  GAME_API void DeleteGameObject(game::GameObject* go);
}

#endif//INCLUDED_GAME_OBJECT_FACTORY_H
