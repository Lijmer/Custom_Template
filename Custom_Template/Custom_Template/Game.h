#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H
#include <vector>
namespace engine { class Bitmap; }
namespace game
{
  class GameObject;
  class Game
  {
  public:
    Game(void(*ExitGame)());
    ~Game();

    void Update();
    void Draw(engine::Bitmap &screen);

  private:
    std::vector<GameObject*> m_objects;
    float m_fps;
    void(*ExitGame)();
  };
}

#endif
