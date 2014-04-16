#ifndef INCLUDED_GAME_OBJECT_FACTORY_H
#define INCLUDED_GAME_OBJECT_FACTORY_H

namespace game { class GameObject; }
enum COMPONENT_ID;
namespace game_object_factory
{
  game::GameObject* CreateGameObject(const char *filePath);
  game::GameObject* CreateGameObject(COMPONENT_ID *ComponentIDList, int size);
}

#endif//INCLUDED_GAME_OBJECT_FACTORY_H
