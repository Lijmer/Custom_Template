#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <vector>

namespace game
{
  class GameObject;
  struct GameImpl;
  class Game
  {
  public:
    Game();
    ~Game();
    void Update();
    void FixedUpdate();
  private:
    std::vector<GameObject*> m_objects;

  };
}

#endif
