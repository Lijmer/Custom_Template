#include "Game.h"
#include "Bitmap.h"
#include "CycleTimer.h"
#include "Time.h"
#include "Types.h"
#include "Input.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SpriteRenderer.h"
#include "GameObjectFactory.h"

#include <cstdio>
#include <cstdlib>

#include <string>


namespace game
{
  Game::Game(void(*ExitGame)()) :
    m_fps(0.0f),
    ExitGame(ExitGame)
  {
    COMPONENT_ID list1[] = {SPRITE_RENDERER, RIGIDBODY};
    COMPONENT_ID list2[] = {TEXT_RENDERER, MOVE_COMPONENT, SPRITE_RENDERER};

    for(int i = 0; i < 100; ++i)
    {
      GameObject* go = game_object_factory::CreateGameObject("assets/myGameObject.go");
      ((SpriteRenderer*)(go->GetComponent(SPRITE_RENDERER)))->SetSprite(engine::SPR::TEST);
      go->SetName("PIE!");
      go->GetTransform().position = float2(rand() % 100, rand() % 100);
      m_objects.push_back(go);
    }

    m_objects.push_back(game_object_factory::CreateGameObject(list2, 3));
  }

  Game::~Game()
  {
    for(auto &i : m_objects)
      game_object_factory::DeleteGameObject(i);
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