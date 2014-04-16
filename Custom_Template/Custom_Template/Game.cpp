#include "Game.h"
#include "Bitmap.h"
#include "CycleTimer.h"
#include "Time.h"
#include "Types.h"
#include "Input.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SpriteRenderer.h"

#include <cstdio>
#include <cstdlib>

#include <string>


namespace game
{
  Game::Game(void(*ExitGame)()) :
    m_fps(0.0f),
    ExitGame(ExitGame)
  {
    GameObject* go = new GameObject;
    SpriteRenderer* spr = (SpriteRenderer*)go->AddComponent(SPRITE_RENDERER);
    spr->SetSprite(engine::SPR::TEST);
    go->AddComponent(RIGIDBODY);
    go->SetName("PIE!");
    m_objects.push_back(go);

    go = new GameObject;
    go->AddComponent(TEXT_RENDERER);
    go->AddComponent(MOVE_COMPONENT);
    spr = (SpriteRenderer*)go->AddComponent(SPRITE_RENDERER);
    spr->SetSprite(engine::SPR::MISSING);
    m_objects.push_back(go);
  }

  Game::~Game()
  {
    for(auto &i : m_objects)
      delete i;
  }

  void Game::Update()
  {
    if(input::GetKeyDown(SDLK_ESCAPE))
      ExitGame();

    for(auto &i : m_objects)
      i->Update();

    m_fps = .99f * m_fps + .01f / time::GetDeltaTime();
  }

  void Game::Draw(engine::Bitmap &screen)
  {
    static ull average = 0;
    static int counter = 0;
    CycleTimer timer;
    timer.Start();
    screen.Clear(0);
    average += timer.End();
    counter++;


    char str[128];
    sprintf_s(str, 128, "FPS: %f", m_fps);
    screen.Print(str, 10, 10, 0xffff00);
    sprintf_s(str, 128, "clearing screen: %llu cycles", average / counter);
    screen.Print(str, 10, 20, 0xffff00);

    static int index = 0;
    if(++index >= screen.GetWidth() * screen.GetHeight())
      index = 0;

    screen.GetBuffer()[index].pixel = 0xffffff;
  }


}