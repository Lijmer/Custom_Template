// Template by Max Oomen - 2014
// Based on the template by Jacco Bikker - 2006-2014
#include <SDL_main.h>
#include "../Renderer/Window.h"
#include "Constants.h"
#include "../Renderer/Bitmap.h"
#include "TimeImpl.h"
#include "../Input/EventHandler.h"
#include "../Game/Game.h"
#include "../Renderer/Renderer.h"
#include "../Input/InputImpl.h"
#include "CollisionHandler.h"
#include "../Game/test.h"

using namespace engine;

static game::Game* g_game = nullptr;
static bool g_running = true;

void Exit() { g_running = false; }

#ifdef __cplusplus
extern "C"
#endif
int main(int, char**)
{
  Window window(SCRWIDTH, SCRHEIGHT, "Custom_Template");

  time::impl::Init();
  time::impl::SetFixedUpdateCallback([](){g_game->FixedUpdate(); });

  event_handler::SetWindowCloseCallback(&Exit);
  event_handler::SetKeyDownCallback(&input::impl::OnKeyDown);
  event_handler::SetKeyUpCallback(&input::impl::OnKeyUp);
  event_handler::SetMouseMotionCallback(&input::impl::OnMouseMotion);
  event_handler::SetMouseButtonDownCallback(&input::impl::OnMouseButtonDown);
  event_handler::SetMouseButtonUpCallback(&input::impl::OnMouseButtonUp);
  Test();
  game::Game game;
  g_game = &game;

  while(g_running)
  {
    input::impl::OnUpdate();
    event_handler::Update();
    time::impl::Update();
    game.Update();
    collision_handler::Update();
    window.Draw(&renderer::Render);
  }

  return (int)(g_game = nullptr);
}
