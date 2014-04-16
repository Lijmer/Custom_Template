#ifndef INCLUDED_GAME_OBJECT_MANANER
#define INCLUDED_GAME_OBJECT_MANAGER

#include <vector>

namespace game
{
  class GameObject;
  class GameObjectManager
  {
  public:
  private:
    std::vector<GameObject*> m_objects;
  };
}

#endif//INCLUDED_GAME_OBJECT_MANAGER
