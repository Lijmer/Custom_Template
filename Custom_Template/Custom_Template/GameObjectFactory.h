#ifndef INCLUDED_GAME_OBJECT_FACTORY_H
#define INCLUDED_GAME_OBJECT_FACTORY_H

namespace game { class GameObject; }
enum COMPONENT_ID;
namespace game_object_factory
{
  game::GameObject* CreateGameObject(const char *filepath);
  game::GameObject* CreateGameObject(COMPONENT_ID *ComponentIDList, int size);

  void DeleteGameObject(game::GameObject* go);
}

#endif//INCLUDED_GAME_OBJECT_FACTORY_H
