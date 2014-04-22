#include "Game.h"
#include "../Renderer/Bitmap.h"
#include "../Custom_Template/CycleTimer.h"
#include "Time.h"
#include "../Custom_Template/Types.h"
#include "../Input/Input.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "../Components/SpriteRenderer.h"
#include "GameObjectFactory.h"

#include "../Custom_Template/main.h"

#include <cstdio>
#include <cstdlib>


namespace game
{
  Game::Game()
  {
    for(int i = 0; i < 5; ++i)
    {
      GameObject* go = gof::CreateGameObject("assets/myGameObject.go");
      SpriteRenderer* spr = (SpriteRenderer*)go->GetComponent(SPRITE_RENDERER);
      spr->SetSprite(engine::SPR::TEST);
      go->SetName("PIE!");
      go->GetTransform().position = float2(rand() % 100, rand() % 100);
      m_objects.push_back(go);
    }

    COMPONENT_ID list[] = {TEXT_RENDERER, MOVE_COMPONENT};
    const int sizeList = sizeof(list) / sizeof(COMPONENT_ID);
    GameObject* go = gof::CreateGameObject(list, sizeList);
    go->SetName("FPS Counter");
    m_objects.push_back(go);

    COMPONENT_ID list2[] = {TEXT_RENDERER, TEST};
    const int sizeList2 = sizeof(list2) / sizeof(COMPONENT_ID);
    go = gof::CreateGameObject(list2, sizeList2);
    go->GetTransform().position = float2(0.0f, 10.0f);
    go->SetName("FUPS Counter");
    m_objects.push_back(go);
  }

  Game::~Game()
  {
    for(auto &i : m_objects)
      gof::DeleteGameObject(i);
  }

  void Game::Update()
  {
    if(input::GetKeyDown(SDLK_ESCAPE))
      Exit();

    for(auto &i : m_objects)
      i->Update();
  }
  void Game::FixedUpdate()
  {
    for(auto &i : m_objects)
      i->FixedUpdate();
  }
}
