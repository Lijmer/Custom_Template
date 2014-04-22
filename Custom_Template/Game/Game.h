#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H
#include "API.h"
#include <vector>

namespace game
{
  class GameObject;
  struct GameImpl;
  class Game
  {
  public:
    GAME_API Game();
    GAME_API ~Game();
    GAME_API void Update();
    GAME_API void FixedUpdate();
  private:
    std::vector<GameObject*> m_objects;

  };
}

#endif
